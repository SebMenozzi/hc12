//HC-12 Toggle button Receive
//Autor Tom Heylen tomtomheylen.com


#include <SoftwareSerial.h>
#include <Servo.h> 

SoftwareSerial hc12(2, 3); // RX, TX

int ledPin = 12;
int servoPin1 = 11;
int servoPin2 = 10;

int Motor_Pin1 = 5; // pin 2 on L293D
int Motor_Pin2 = 6; // pin 7 on L293D
int Enable = 7; // pin 1 on L293D

char byteIn;                                        // Temporary variable
String hc12ReadBuffer = "";  
boolean hc12End = false;

boolean isBackOn;
int lastX;

Servo servo1;
Servo servo2;

void setup() {
  Serial.begin(9600);
  hc12.begin(9600);
  
  pinMode(ledPin, OUTPUT);

  //Setting the motor pins and the enable pin as the output pin
  pinMode(Motor_Pin1, OUTPUT);
  pinMode(Motor_Pin2, OUTPUT);
  pinMode(Enable, OUTPUT);
  
  digitalWrite(Enable, HIGH);  //Making the enable pin high to run the motor

  // Setup servo1
  servo1.attach(servoPin1);
  servo1.write(0);
  delay(400);
  servo1.detach ();

  // Setup servo2
  servo2.attach(servoPin2);
  servo2.write(110);
  delay(400);
  //servo2.detach ();
  
  isBackOn = false;
}

void loop() {

  if (hc12.available()) {
    byteIn = hc12.read();
    if (byteIn == 'E') {
      hc12End = true;
    } else {
      hc12ReadBuffer += byteIn;
    }
  }

  if (hc12End) { // If HC12End flag is true
    if (hc12ReadBuffer[0] == 'R') {
      digitalWrite(Motor_Pin1, LOW);
      digitalWrite(Motor_Pin2, LOW);
      
      digitalWrite(ledPin, LOW);
    }
    if (hc12ReadBuffer[0] == 'Y') {
      
      char Y_ARRAY[6];
      (hc12ReadBuffer.substring(1)).toCharArray(Y_ARRAY, sizeof(Y_ARRAY));
      int Y = atoi(Y_ARRAY);

      if (Y == 127) {
        digitalWrite(Motor_Pin1, LOW);
        digitalWrite(Motor_Pin2, LOW);
        
        digitalWrite(ledPin, LOW);
      }

      if (Y > 127) {
        //Serial.println("avancer");
        
        digitalWrite(Motor_Pin1, LOW);
        digitalWrite(Motor_Pin2, HIGH);
      }

      if (Y < 127) {
        //Serial.println("reculer");
        
        digitalWrite(Motor_Pin1, HIGH);
        digitalWrite(Motor_Pin2, LOW);
      }
    }
    if (hc12ReadBuffer[0] == 'X') {
      char X_ARRAY[6];
      (hc12ReadBuffer.substring(1)).toCharArray(X_ARRAY, sizeof(X_ARRAY));
      int X = atoi(X_ARRAY);

      Serial.println(X);
      /*

      if (X == 124) {
        servo2.attach(servoPin2);
        servo2.write(110);
        delay(400);
        servo2.detach ();
      }
      else if (X >= 100 && X <= 150) {
        servo2.detach ();
      }
      else {
        
        X = map(X, 25, 227, 70, 150);

        servo2.attach(servoPin2);
        servo2.write(X);
        
        
        if (X > 150 && lastX < 150) {
          servo2.attach(servoPin2);
          servo2.write(150);
          delay(400);
        }
        if (X < 100 && lastX > 100) {
          servo2.attach(servoPin2);
          servo2.write(70);
          delay(400);
        }
        servo2.detach ();
        
      }
      */

      /*

      if (X > 200 && lastX <= 200) {
        servo2.attach(servoPin2);
        servo2.write(150);
        delay(400);
        servo2.detach ();
      }
      else if (X < 40 && lastX >= 40) {
        servo2.attach(servoPin2);
        servo2.write(40);
        delay(400);
        servo2.detach ();
      }
      else {
        if (lastX != 124) {
          servo2.attach(servoPin2);
          servo2.write(110);
          delay(400);
          servo2.detach ();
        }
      }
      */
      lastX = X;
    }
    if (hc12ReadBuffer[0] == 'C') {
      servo1.attach(servoPin1);
      
      if (isBackOn) {
        servo1.write(0);
      }
      else {
       servo1.write(90);
      }
      delay (300);
      servo1.detach ();
      isBackOn = !isBackOn;
    }
    hc12ReadBuffer = ""; // Empty Buffer
    hc12End = false; // Reset Flag
  }
}
