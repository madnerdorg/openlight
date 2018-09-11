//Openlight : Milight Serial Gateway
//Based on https://hackaday.io/project/5888-reverse-engineering-the-milight-on-air-protocol
// Remi Sarrailh madnerd.org : MIT https://github.com/madnerdorg/openlight
// Henryk Plötz : GPLv3 : https://github.com/henryk/openmili

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "PL1167_nRF24.h"
#include "MiLightRadio.h"
#include "secrets.h"

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

const String usb_name = "madnerd/openlight/salon";

//Serial string buffer
String readString;

// Serial

//When application asked if this is the correct arduino
void serialCheck() {
  if (readString == "/info") {
    Serial.println(usb_name);
  } else {
    //Serial.println(readString);
    int code[7];
    code[0] = hexToDec(getValue(readString, ',', 0));
    code[1] = hexToDec(getValue(readString, ',', 1));
    code[2] = hexToDec(getValue(readString, ',', 2));
    code[3] = hexToDec(getValue(readString, ',', 3));
    code[4] = hexToDec(getValue(readString, ',', 4));
    code[5] = hexToDec(getValue(readString, ',', 5));
    code[6] = 0x01;
    radioSend(code);
  }
}

//Convert characters sent by serial to string
void serialManager() {
  //Get Serial as a string
  while (Serial.available()) {
    delay(3); // Wait for data

    //Convert to String
    if (Serial.available() > 0) {
      char c = Serial.read();
      readString += c;
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello World");
  pinMode(OnPin, INPUT_PULLUP);
  pinMode(OffPin, INPUT_PULLUP);
  mlr.begin();
}

void loop()
{
  radioReceive();
  serialManager();

  //If string received
  if (readString.length() > 0) {
    serialCheck();
  }

  //We clean the serial buffer
  readString = "";

  //If ON button pressed send on
  if (!digitalRead(OnPin)) {
    radioSend(on);
  }

  //If OFF button pressed send off
  if (!digitalRead(OffPin)) {
    radioSend(off);
  }

}


void radioReceive() {
  if (mlr.available()) {
    uint8_t packet[7];
    size_t packet_length = sizeof(packet);
    mlr.read(packet, packet_length);

    for (int i = 0; i < packet_length; i++) {
      if (packet[i] < 10) {
        Serial.print("0x0");
      } else {
        Serial.print("0x");
      }
      Serial.print(packet[i], HEX);

      if (i != (packet_length - 1)) {
        Serial.print(",");
      }
    }
    Serial.println();
  }
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


//Equivalent of explode in PHP (use for serial commands parsing)
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

//https://github.com/benrugg/Arduino-Hex-Decimal-Conversion/blob/master/hex_dec.ino
unsigned int hexToDec(String hexString) {

  unsigned int decValue = 0;
  int nextInt;

  for (int i = 2; i < hexString.length(); i++) {

    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);

    decValue = (decValue * 16) + nextInt;
  }

  return decValue;
}
