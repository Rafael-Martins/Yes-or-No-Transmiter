#include <Arduino.h>
#include <IRremote.h>

IRsend irsend;

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

// Pin connected to infrared led positive
int infraredOut = 2;


int buttonOne = 5;
int buttonTwo = 6;


void writeOnLeds(int ledId) {
  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, ledId);
  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
  // pause before next value:
}

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(infraredOut, OUTPUT);
  
  pinMode(buttonOne, INPUT);
  pinMode(buttonTwo, INPUT);

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(buttonOne) == HIGH) {
    irsend.sendSony(0x68B92, 20);
    writeOnLeds(1);
    Serial.println("no");

  } else if (digitalRead(buttonTwo) == HIGH) {
    irsend.sendSony(0x68B92, 20);
    writeOnLeds(2);
    Serial.println("yes");
  }
  delay(50);



  // for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
  //   // take the latchPin low so
  //   // the LEDs don't change while you're sending in bits:
  //   digitalWrite(latchPin, LOW);
  //   // shift out the bits:
  //   shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);
  //
  //   //take the latch pin high so the LEDs will light up:
  //   digitalWrite(latchPin, HIGH);
  //   // pause before next value:
  //   delay(500);
  // }
}
