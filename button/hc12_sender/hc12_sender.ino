//HC-12 Toggle button Send
//Autor Tom Heylen tomtomheylen.com

#include <Wire.h>
#include "Nunchuk.h"
#include <SoftwareSerial.h>

SoftwareSerial hc12(2, 3); //RX, TX

int buttonPin = 8;
int lastButtonCState;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  hc12.begin(9600);

  Wire.begin();
  //nunchuk_init_power(); // A1 and A2 is power supply
  nunchuk_init();
}

void loop() {

  if (nunchuk_read()) {
    int buttonZState = nunchuk_buttonZ();
    int buttonCState = nunchuk_buttonC();

    if(buttonZState) {
      int Y = nunchuk_joystickY_raw();
      hc12.print('Y' + String(Y) + 'E');

      int X = nunchuk_joystickX_raw();
      hc12.print('X' + String(X) + 'E');
    }
    else if (buttonCState == 1 && lastButtonCState == 0) {
      hc12.print("CE");
    }
    else {
      hc12.print("RE");
    }
    
    lastButtonCState = buttonCState;
  }

  delay(20);
}
