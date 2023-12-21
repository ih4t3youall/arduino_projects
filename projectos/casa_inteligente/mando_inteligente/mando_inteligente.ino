int FirstShotX , FirstShotY;

#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

void setup()
{
  rf_driver.init();

  pinMode(11, OUTPUT);
  for(int i=2; i<9; i++)
  {
    pinMode(i, INPUT);
    digitalWrite(i, 1);
  }
  Serial.begin(9600);
  FirstShotX = 0;
  FirstShotY = 0;
}

String addStringLenght(String message){
  String messageLenght = String(message.length());
  return messageLenght + message;
}

void sendMessage(String message){
  Serial.println(message);
  message = addStringLenght(message);
  Serial.println("Message: "+message);
  rf_driver.send((uint8_t *)message.c_str(), strlen(message.c_str()));
  rf_driver.waitPacketSent();
}

void loop()
{
  int i, someInt, flag = 0;
  for(i=2; i<9; i++)
  {
    someInt = digitalRead(i);
    if(someInt == 0)
    {
      flag =1;
      break;
    }
  }
  if(flag == 1)
  {
    switch(i)
    {
      case 2: sendMessage("lliv\0"); break;
      case 3: Serial.println("--------> Button B"); break;
      case 4: sendMessage("lpie\0"); break;
      case 5:  Serial.println("--------> Button abajo"); break;
      case 6: Serial.println("--------> Button E"); break;
      case 7: Serial.println("--------> Button F"); break;
      case 8: Serial.println("--------> Button KEY"); break;
      default: break;
    }
    flag=0;
  }
  int sensorValue = analogRead(A0);
  if(FirstShotX == 0)
  {
    FirstShotX = sensorValue;
  }

  sensorValue = analogRead(A1);
  if(FirstShotY == 0)
  {
    FirstShotY = sensorValue;
  }
  delay(200);
}
