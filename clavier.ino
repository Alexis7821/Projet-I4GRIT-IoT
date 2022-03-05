#include <Keypad.h>//https://github.com/Chris--A/Keypad

char returnMDP[5] = "MDPOK";

//Constants
#define ROWS 4
#define COLS 4

//Parameters
const char kp4x4Keys[ROWS][COLS]  = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
byte rowKp4x4Pin [4] = {2, 3, 4, 5};
byte colKp4x4Pin [4] = {6, 7, 8, 9};

int i = 0;
//Variables
Keypad kp4x4  = Keypad(makeKeymap(kp4x4Keys), rowKp4x4Pin, colKp4x4Pin, ROWS, COLS);

uint8_t KeyPad_MDP[] =
{

};

char mdp[4];

char Valid_MDP[4] = {'1', '2', '3', '4'};

char mystr[10];

int z = 0;

int check = 0;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);   //it was missing
}

void loop()
{
  char customKey = kp4x4.getKey();
  byte n = Serial1.available();
  if (n != 0)
  {
    byte m = Serial1.readBytes(mystr, 10); //blocking code
    mystr[m] = '\0';      //you need to place null character at the end of char array
    Serial.println(mystr);
    String temp(mystr);
    Serial.println(temp);
    if (temp = "hello") {
      do {
        char customKey = kp4x4.getKey();
        if (customKey) {
          Serial.println("////////");
          mdp[z] = customKey;
          Serial.println(z);
          Serial.println(customKey);
          Serial.println(z);
          Serial.println(mdp[z]);
          Serial.println(z);
          Serial.println("////////");
          z++;
        }
        if (z == 4) {
          Serial.println("dans la boule");
          for (z = 0; z < 4; z++) {
            if (z == 0) {
              Serial.println("// MDP //");
            }
            Serial.println(mdp[z]);
            if (z == 3) {
              Serial.println("// END //");
            }
          }
          for (byte z = 0; z < 4; z++) {
            if (z == 0) {
              Serial.println();
            }
            Serial.println(Valid_MDP[z]);
            if (z == 3) {
              Serial.println();
            }
          }
          int y = 0;
          for (int z = 0; z < 4; z++) {
            Serial.println(mdp[z]);
            Serial.println(Valid_MDP[z]);
            Serial.println();
            if (mdp[z] == Valid_MDP[z]) {
              y++;
            }
          }
          if (y == 4) {
            
            Serial.write(returnMDP, 5);
            Serial1.write(returnMDP, 5);

            check = 1;
            z = 0;
          }
        }
      } while (check < 1);
    }
  }
}
