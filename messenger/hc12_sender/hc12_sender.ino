#include <SoftwareSerial.h>

String msg;
int rxPin = 2;
int txPin = 3;
int setPin = 4;
SoftwareSerial hc12(rxPin , txPin);

void setup() {
  pinMode(setPin,OUTPUT);
  // passage en mode commande
  digitalWrite(setPin,LOW);
  Serial.begin(9600);
  hc12.begin(9600);
  // Passage du module sur le canal 1, en 9600bps et à 20dBm
  hc12.print(F("AT+C001+B57600+P20+FU4"));
  // Délais pour que le module traite la commande 
  delay(100);
  // passage en mode transparent
  digitalWrite(setPin,HIGH);
}

void loop() {

  //prints time since program started
  if(Serial.available()){
    msg = Serial.readString();
    Serial.print(F("SND : "));
    Serial.println(msg);
    hc12.print(msg);
  }
  if(hc12.available()){
    Serial.print(F("RCV : "));
    Serial.println(hc12.readString());
  }
}
