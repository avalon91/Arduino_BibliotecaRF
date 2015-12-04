#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"

RF24 radio(9,10);

const uint64_t pipes[2] = {0x78787878A3LL, 0x78787878E1LL};

boolean sucesso = false;
int array[4];
int canal = 120;
char papel = 'T'; //T = TX; R = RX

void setup() {
  radio.begin();
  radio.setChannel(canal);
  radio.setRetries(15,15);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setCRCLength(RF24_CRC_16);
  radio.setPayloadSize(16);
  if(papel == 'T'){
    radio.openReadingPipe(1,pipes[0]);
    radio.openWritingPipe(pipes[1]);
  }
  if(papel == 'R'){
    radio.openReadingPipe(1,pipes[1]);
    radio.openWritingPipe(pipes[0]);
  }
  radio.startListening();
  radio.printDetails();

}

void loop() {
  envio();

}

void envio(){
  radio.stopListening();
  sucesso = radio.write(&array, sizeof(array));
  if(sucesso == true){
    //Serial.print("Enviado com sucesso!");
  } else{
    //Serial.print("Falha no envio.");
  }
  radio.startListening();  
}
