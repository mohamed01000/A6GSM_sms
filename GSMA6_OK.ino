#include <SoftwareSerial.h>


//Create software serial object to communicate with A6
// Créer un second port virtuel série pour attaquer le module Gsm  
SoftwareSerial A6GSM(2, 3); //A6 Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  delay(10000);

  
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and A6
  A6GSM.begin(9600);

  Serial.println("Initialisation du module A6 ..."); 
  Serial.println("La com avec le PC est OK ... ") ; 
  delay(1000);

  Serial.println("Test commande AT ... "); 
 
  A6GSM.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  delay(1000);

  A6GSM.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();

  Serial.println("\n"); 
  A6GSM.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  
  A6GSM.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
    
  Serial.println("envoi de la commande : AT+CPIN=\"0000\"");
  A6GSM.print("AT+CPIN=\"0000\"\r");
  delay(1000);
 
  Serial.println("Passage en Mode Text"); 
 
  A6GSM.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  delay(3000);
  Serial.println("Saisie du numéro de Téléphone "); 
  //Serial.println("AT+CMGS=\"+33612542988\"");
  A6GSM.println("AT+CMGS=\"+336xxxxxxxx\"");//change ZZ with country code and xx xx xx xx xxx with phone number to sms
 A6GSM.println("AT+CMGS=\"+336xxxxxxxx\"");//change ZZ with country code and xx xx xx xx xxx with phone number to sms
  updateSerial();
    delay(1000);
  Serial.println("envoie du message");
  A6GSM.print("Envoie de message Arduino A6"); //text content
  updateSerial();
  Serial.println("\n Message envoyé");
  
  
  A6GSM.write(26);
}

void loop()
{
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    A6GSM.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  
  while(A6GSM.available()) 
  {
    
    Serial.write(A6GSM.read());//Forward what Software Serial received to Serial Port
  }
}
