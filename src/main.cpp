#include <Arduino.h>

/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*//* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {6, 11, 10, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 5, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define led_pin 4
int led_state = 0;
#define horn_pin 12

void setup(){
  Serial.begin(9600);
  Serial.println("hi");
  pinMode(led_pin,OUTPUT);
  pinMode(horn_pin,INPUT_PULLUP);
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
  }
  // delay(1000);
  // digitalWrite(led_pin,led_state);
  // led_state=!led_state;
  // if(digitalRead(horn_pin))
  // {
  //   Serial.println("Horn is up");
  // }
  // else{
  //   Serial.println("Horn is down");
  // }
  // delay(1000);
}