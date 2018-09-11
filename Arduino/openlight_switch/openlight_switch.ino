//Openlight 
//Based on https://hackaday.io/project/5888-reverse-engineering-the-milight-on-air-protocol
// Remi Sarrailh madnerd.org : MIT https://github.com/madnerdorg/openlight
// Henryk Plötz : GPLv3 : https://github.com/henryk/openmili

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "PL1167_nRF24.h"
#include "MiLightRadio.h"

#include <LowPower.h>
//Radio
#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);
PL1167_nRF24 prf(radio);
MiLightRadio mlr(prf);
int sequence = 0x01;

//Buttons pinOut
const int OnPin = 2;
const int OffPin = 3;
const int repeat = 10;

void setup(){
  pinMode(OnPin, INPUT_PULLUP);
  pinMode(OffPin, INPUT_PULLUP);
  attachInterrupt(0, ron, CHANGE);
  attachInterrupt(1, roff, CHANGE);
  mlr.begin();
}

void loop(){
   radio.powerDown();
   LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}

void ron(){
  radio.powerUp();
  radioSend(on);
}

void roff(){
  radio.powerUp();
  radioSend(off);
}

void radioSend(int code [7] ) {
  //Prepare message
  uint8_t outgoingPacket_tmp [7] ;
  for (int i = 0; i < 6; i++)
  {
    outgoingPacket_tmp[i] = (uint8_t)code[i];

    if (code[i] < 10) {
      Serial.print("0x0");
    } else {
      Serial.print("0x");
    }
    Serial.print(code[i], HEX);
    Serial.print(",");
  }

  uint8_t sequence_tmp = (uint8_t)sequence;

  if (sequence_tmp < 10) {
    Serial.print("0x0");
  } else {
    Serial.print("0x");
  }
  Serial.print(sequence_tmp, HEX);
  Serial.println();
  outgoingPacket_tmp[6] = sequence_tmp;

  //Send message
  for (int i = 0; i < repeat; i++) {
    mlr.write(outgoingPacket_tmp, sizeof(outgoingPacket_tmp));
    delay(20);
    sequence++;
    outgoingPacket_tmp[6] = (uint8_t)sequence;
  }
}
