#include <Arduino.h>

#define PASSCODE_LENGTH 3
String PASSCODE = "100";

#include <Keypad.h>
#include <SoftwareSerial.h>

SoftwareSerial mySoftwareSerial(2, 3);
// Create the mp3 connection itself, notice how we give it the
//  serial object we want it to use to talk to the JQ8400 module.
// For example you might use mp3(Serial2) instead of a SoftwareSerial
#include <JQ8400_Serial.h>
JQ8400_Serial mp3(mySoftwareSerial);

const byte ROWS = 4; // four rows
const byte COLS = 3; // three columns
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
byte rowPins[ROWS] = {6, 11, 10, 8}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 5, 9};      // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

#define led_pin 4
int led_state = 0;
#define horn_pin 12

int collectedChars = 0;
String inputchars = "";
void resetInput()
{
  inputchars = "";
  collectedChars = 0;
}
void checkPassCode()
{
  if (inputchars.equals(PASSCODE))
  {
    Serial.println("Correct passcode");
    if (!mp3.busy())
    {
      // 1 is the FAT index number, that is the first file on the
      // device, 2 is the next file, 3 is the third file.

      // The FAT index has no relation to file name. Use a FAT sorting
      // tool, like, fatsort, to sort the FAT.

      // In this example we just play the first index, over and over again.
      mp3.playFileByIndexNumber(1);
    }
  }
  else
  {
    Serial.println("Invalid passcode");
    for (size_t i = 0; i < 10; i++)
    {
      led_state = !led_state;
      digitalWrite(led_pin, led_state);
      delay(500);
    }
    resetInput();
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.println("hi");
  pinMode(led_pin, OUTPUT);
  pinMode(horn_pin, INPUT_PULLUP);

  mySoftwareSerial.begin(9600);
  mp3.reset();
  mp3.setVolume(100);
  mp3.setLoopMode(MP3_LOOP_NONE);
}

void loop()
{
  if (digitalRead(horn_pin))
  {
    // Serial.println("Horn is down");
    mp3.reset();
    resetInput();
  }
  else
  {
    // Serial.println("Horn is up");

    char key = keypad.getKey();

    if (key)
    {
      Serial.println(key);
      if (collectedChars < PASSCODE_LENGTH)
      {
        inputchars = String(inputchars + key);
        collectedChars++;
        Serial.print("Collected characters:");
        Serial.println(collectedChars);
        if (collectedChars == PASSCODE_LENGTH)
        {
          checkPassCode();
        }
      }
      else
      {
        checkPassCode();
      }
    }
  }
  // delay(1000);
  /*
          case 'p': Serial.println("Play");   mp3.play();     return;
        case 'r': Serial.println("Restart"); mp3.restart(); return;
        case ' ': Serial.println("Pause"); mp3.pause();     return;
        case '>': Serial.println("Next");  mp3.next();      return;
        case '<': Serial.println("Prev");  mp3.prev();      return;

        case ']': Serial.println("Next Folder");  mp3.nextFolder(); return;
        case '[': Serial.println("Prev Folder");  mp3.prevFolder(); return;

        case '+': Serial.println("Vol +"); mp3.volumeUp(); return;
        case '-': Serial.println("Vol -"); mp3.volumeDn(); return;
        case 'm': Serial.println("Vol 0"); mp3.setVolume(0); return;*/
  //  if(!mp3.busy())
  // {
  //   // 1 is the FAT index number, that is the first file on the
  //   // device, 2 is the next file, 3 is the third file.

  //   // The FAT index has no relation to file name. Use a FAT sorting
  //   // tool, like, fatsort, to sort the FAT.

  //   // In this example we just play the first index, over and over again.
  //   mp3.playFileByIndexNumber(1);
  // }
}