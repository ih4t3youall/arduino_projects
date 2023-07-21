// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 

#include <MFRC522.h>
// Create Amplitude Shift Keying Object
RH_ASK rf_driver(2000,7,8);
int number = 0;
char msg[20]; 

#define RST_PIN	9    //Pin 9 para el reset del RC522
#define SS_PIN	10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
 
void setup()
{
    // Initialize ASK Object
 
    rf_driver.init();
    SPI.begin();        //Iniciamos el Bus SPI
    mfrc522.PCD_Init(); // Iniciamos  el MFRC522
    Serial.begin(9600);
    Serial.println("Lectura del UID");
  

}
 
void sendMessage(String message){
    rf_driver.send((uint8_t *)message.c_str(), strlen(message.c_str()));
    rf_driver.waitPacketSent();
}

void loop()
{
  
    if ( mfrc522.PICC_IsNewCardPresent()) 
    {  
    	//Seleccionamos una tarjeta
        if ( mfrc522.PICC_ReadCardSerial()) 
        {
              // Enviamos serialemente su UID
              Serial.print("Card UID:");
              String lectura="";

              for (byte i = 0; i < mfrc522.uid.size; i++) {
                      lectura += String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ") + String(mfrc522.uid.uidByte[i], HEX);
                      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                      Serial.print(mfrc522.uid.uidByte[i], HEX);   
              } 
              Serial.println();
              Serial.println(lectura);
	      if (lectura.length() > 0){
		          sendMessage(lectura);
	      }
              // Terminamos la lectura de la tarjeta  actual
              mfrc522.PICC_HaltA();         
        }      
    }	
}
