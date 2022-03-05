#include <SPI.h>
#include <MFRC522.h>
#include <Sodaq_RN2483.h>
#include <Keypad.h>

const int broche2 = 2; // LED

#define debugSerial SerialUSB
#define loraSerial Serial2

#define RST_PIN 9
#define SS_PIN 10

MFRC522 rfid(SS_PIN, RST_PIN);  //Create MFRC522 instance

MFRC522::MIFARE_Key key;
byte nuidPICC[4];

const uint8_t devAddr[4] =
{
    0x26, 0x0B, 0x73, 0xA5
};

// USE YOUR OWN KEYS!
const uint8_t appSKey[16] =
{
 0x9A, 0xFE, 0x96, 0x7C, 0x7F, 0x86, 0x13, 0xCC, 0x43, 0x95, 0x5D, 0xEA, 0x2D, 0xB1, 0x7C, 0x93
};

// USE YOUR OWN KEYS! 0x9A, 0xFE, 0x96, 0x7C, 0x7F, 0x86, 0x13, 0xCC, 0x43, 0x95, 0x5D, 0xEA, 0x2D, 0xB1, 0x7C, 0x93
const uint8_t nwkSKey[16] =
{
  0xC1, 0xF2, 0x74, 0x89, 0xD4, 0xB2, 0x47, 0x10, 0xD3, 0xE2, 0xFD, 0xA7, 0x82, 0x1B, 0xC2, 0xD3
};

uint8_t testPayload[] =
{
  0x53, 0x4F, 0x44, 0x41, 0x51
};

char mystr[6] = "Hello";
char returnMDP[10];

void setup() {
  while ((!debugSerial) && (millis() < 10000));
 
  debugSerial.begin(57600);
  loraSerial.begin(LoRaBee.getDefaultBaudRate());
  
  LoRaBee.setDiag(debugSerial); // optional
  
  SerialUSB.begin(9600);
  Serial.begin(9600);  
  SPI.begin();
  rfid.PCD_Init();
  pinMode(broche2, OUTPUT);
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  SerialUSB.println(F("Scan du code UID de la carte "));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);

  if (LoRaBee.initABP(loraSerial, devAddr, appSKey, nwkSKey, false))
  {
    debugSerial.println("Connection to the network was successful.");
  }
  else
  {
    debugSerial.println("Connection to the network failed!");
  }
}

void loop() {
  int tempo = 0;

  if (! rfid.PICC_IsNewCardPresent())
    return;
  if (!rfid.PICC_ReadCardSerial())
    return;

  SerialUSB.print(F("PICC type : "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  SerialUSB.println(rfid.PICC_GetTypeName(piccType));

  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    SerialUSB.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
  //Check si on scan une nouvel carte
  if (rfid.uid.uidByte[0] != nuidPICC[0] ||
      rfid.uid.uidByte[1] != nuidPICC[1] ||
      rfid.uid.uidByte[2] != nuidPICC[2] ||
      rfid.uid.uidByte[3] != nuidPICC[3] ) {
    SerialUSB.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
    SerialUSB.println(F("Le tag UID de la carte scanner est :"));
    SerialUSB.print(F("En hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    SerialUSB.println();
    SerialUSB.print(F("En dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    SerialUSB.println();
    uint8_t testPayload[] =
    {
      rfid.uid.uidByte[0], rfid.uid.uidByte[1], rfid.uid.uidByte[2], rfid.uid.uidByte[3]
    };
    Serial.write(mystr, 5);

    Serial.readBytes(returnMDP, 5);
    SerialUSB.println(returnMDP);
    do {
      SerialUSB.println(tempo);
      SerialUSB.println("checkmdp");
      delay(1000);
      Serial.readBytes(returnMDP, 5);
      SerialUSB.println(returnMDP);
      String checkk(returnMDP);
      SerialUSB.println(checkk);
      if (checkk == "MDPOK" ) {
        SerialUSB.println("DANS LA BOUCLE");
        digitalWrite(broche2, HIGH);
        
        uint8_t i = 1;
        while (i > 0)
        {
          switch (LoRaBee.send(1, testPayload, 5))
          {
            case NoError:
              debugSerial.println("Successful transmission.");
              i--;
              break;
            case NoResponse:
              debugSerial.println("There was no response from the device.");
              break;
            case Timeout:
              debugSerial.println("Connection timed-out.");
              break;
            case PayloadSizeError:
              debugSerial.println("The size of the payload is greater than allowed. Transmission failed!");
              break;
            case InternalError:
              debugSerial.println("Oh No! This shouldn't happen. Something is really wrong! Try restarting the device!\r\nThe program will now halt.");
              while (1) {};
              break;
            case Busy:
              debugSerial.println("The device is busy.");
              break;
            case NetworkFatalError:
              debugSerial.println("There is a non-recoverable error with the network connection. You should re-connect.\r\nThe program will now halt.");
              while (1) {};
              break;
            case NotConnected:
              debugSerial.println("The device is not connected to the network. Please connect to the network before attempting to send data.\r\nThe program will now halt.");
              while (1) {};
              break;
            case NoAcknowledgment:
              debugSerial.println("There was no acknowledgment sent back!");
              break;
            default:
              break;
          }
          delay(600);
          SerialUSB.println("Boucle de tentative de transmission");
        }

        tempo = 100;
      }
      SerialUSB.println(tempo);
      tempo++;
    } while (tempo < 40);
  }
  else SerialUSB.println(F("Card read previously."));
  // Halt PICC
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
  SerialUSB.println("fin de code");
}

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    SerialUSB.print(buffer[i] < 0x10 ? " 0" : " ");
    SerialUSB.print(buffer[i], HEX);
  }
}

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    SerialUSB.print(buffer[i] < 0x10 ? " 0" : " ");
    SerialUSB.print(buffer[i], DEC);
  }
}
