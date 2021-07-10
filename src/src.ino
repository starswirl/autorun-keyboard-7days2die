#include "Keyboard.h"
#include <TimerOne.h>

volatile int onShift = 1;         // shiftが押されているか

const int KEY_W = 119;            // w key
const int buttonPin = 4;          // input pin for pushbutton

int previousButtonState = HIGH;   // for checking the state of a pushButton

void setShift() {
  Serial.println(onShift);
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    if ( onShift == 0 ) {
      Keyboard.press(KEY_LEFT_SHIFT);
    }
    else {
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    onShift = !onShift;
  }
}

void setup() {
  //  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  Keyboard.begin();
  Timer1.initialize(10000000); //10秒待機
  Timer1.attachInterrupt(setShift);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState != previousButtonState) {

    //  スイッチの状態が変わったら実行
    if  (buttonState == HIGH) {
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_W);
      previousButtonState = HIGH;
    }
    if (buttonState == LOW) {
      Keyboard.release(KEY_LEFT_SHIFT);
      Keyboard.release(KEY_W);
      previousButtonState = LOW;
    }

  }
}
