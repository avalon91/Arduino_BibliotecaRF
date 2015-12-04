#include "Arduino.h"
#include "Radio.h"
#include "RF24.h"
#include "nRF24L01.h"
#include "printf.h"

Radio::Radio(int canal, char role){
	RF24 radio(9,10);
	const uint64_t pipes[2] = {0x78787878A3LL, 0x78787878E1LL};
	Serial.begin(57600);
  	printf_begin();
  	radio.begin();
  	if(role == 'R'){ //RX
  		radio.openReadingPipe(1,pipes[1]);
		radio.openWritingPipe(pipes[0]);
  	}
  	if(role == 'T'){ //TX
  		radio.openReadingPipe(1,pipes[0]);
  		radio.openWritingPipe(pipes[1]);
  	}
  	radio.setChannel(canal);
	radio.setRetries(15,15);
	radio.setPALevel(RF24_PA_MAX);
	radio.setDataRate(RF24_250KBPS);
	radio.setCRCLength(RF24_CRC_16);
	radio.setPayloadSize(16);
	radio.startListening();
	radio.printDetails();
}

void Radio::EnvieArray(int array[4]){
	boolean sucesso = false;
	radio.stopListening();
  	sucesso = radio.write(&array, sizeof(array));
  	if(sucesso == true){
    	Serial.print("Enviado com sucesso!");
  	} else{
    	Serial.print("Falha no envio.");
  	}
  	radio.startListening();
  
  	unsigned long esperando = millis();
  	boolean timeout = false;
  	while(!radio.available() && !timeout){
    	if(millis() - esperando > 250){
      		timeout = true;
    	}
  	}
  	if(timeout){
    	Serial.println(" Falha no retorno.");
  	} else{
    	Serial.println(" Sucesso no retorno!");
    	char peguei;
    	radio.read(&peguei, sizeof(char));
    	//Serial.println(peguei);
  	}
}

void Radio::RecebaArray(){
	int array[4];
  	char c = 'b';
	if(radio.available()){
		boolean concl = false;
		while(!concl){
			concl = radio.read(&array, sizeof(array));
			for(int i=0; i<4; i++){
				Serial.print(array[i]);
				Serial.println();
			}
			Serial.println();
		}
		radio.stopListening();
    	radio.write(&c, sizeof(char));
    	radio.startListening();
	}
}

void Radio::EnvieChars(char texto[10]){
	boolean sucesso = false;
	radio.stopListening();
  	sucesso = radio.write(&texto, sizeof(texto));
  	if(sucesso == true){
    	Serial.print("Enviado com sucesso!");
  	} else{
    	Serial.print("Falha no envio.");
  	}
  	radio.startListening();
  
  	unsigned long esperando = millis();
  	boolean timeout = false;
  	while(!radio.available() && !timeout){
    	if(millis() - esperando > 250){
      		timeout = true;
    	}
  	}
  	if(timeout){
    	Serial.println(" Falha no retorno.");
  	} else{
    	Serial.println(" Sucesso no retorno!");
    	char peguei;
    	radio.read(&peguei, sizeof(char));
    	//Serial.println(peguei);
  	}
}

void Radio::RecebaChars(){
	int texto[10];
  	char c = 'b';
	if(radio.available()){
		boolean concl = false;
		while(!concl){
			concl = radio.read(&texto, sizeof(texto));
			for(int i=0; i<11; i++){
				Serial.print(texto[i]);
			}
			Serial.println();
		}
		radio.stopListening();
    	radio.write(&c, sizeof(char));
    	radio.startListening();
	}
}