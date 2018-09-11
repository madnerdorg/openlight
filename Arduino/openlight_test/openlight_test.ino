#include <SPI.h>
#include "nRF24L01.h"
#include <RF24.h>
#include "printf.h"

// SETTINGS
#define CE_PIN 9
#define CSN_PIN 10

RF24 radio(CE_PIN, CSN_PIN);

const int OnPin = 2;
const int OffPin = 3;

void setup()
{
  Serial.begin(57600); //Baudrate for 115200 (when i removed the voltage regulator, serial became unreadable otherwise)
  //Serial.begin(115200); 

  pinMode(OnPin, INPUT_PULLUP);
  pinMode(OffPin, INPUT_PULLUP);
  attachInterrupt(0, ron, CHANGE);
  attachInterrupt(1, roff, CHANGE);
  
  printf_begin();
  Serial.println("----- TEST ------");
  radio.begin();
  radio.printDetails();
  Serial.println("-----------------");
  Serial.println();
  Serial.println("----- RESULT EXAMPLE -----");
  Serial.println("STATUS     = 0x0e RX_DR=0 TX_DS=0 MAX_RT=0 RX_P_NO=7 TX_FULL=0");
  Serial.println("RX_ADDR_P0-1   = 0xe7e7e7e7e7 0xc2c2c2c2c2");
  Serial.println("RX_ADDR_P2-5   = 0xc3 0xc4 0xc5 0xc6");
  Serial.println("TX_ADDR    = 0xe7e7e7e7e7");
  Serial.println("RX_PW_P0-6   = 0x00 0x00 0x00 0x00 0x00 0x00");
  Serial.println("EN_AA    = 0x3f");
  Serial.println("EN_RXADDR  = 0x03");
  Serial.println("RF_CH    = 0x4c");
  Serial.println("RF_SETUP   = 0x07");
  Serial.println("NRF_CONFIG     = 0x0e");
  Serial.println("DYNPD/FEATURE  = 0x00 0x00");
  Serial.println("Data Rate  = 1MBPS");
  Serial.println("Model    = nRF24L01+");
  Serial.println("CRC Length   = 16 bits");
  Serial.println("PA Power   = PA_MAX");
   Serial.println("--------------------");

}

void ron(){
  Serial.println("BUTTON ON");
}

void roff(){
  Serial.println("BUTTON OFF");
}


void loop()
{
}
