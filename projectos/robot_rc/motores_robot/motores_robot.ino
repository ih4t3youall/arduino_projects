#include <RH_ASK.h>
#include <SPI.h>

String steering = "520";
String dir = "st";
//float steerRatio = 0.49;
float steerRatio = 0.70;

RH_ASK rf_driver;

const int AIA = 3;
const int AIB = 4;
const int BIA = 5;            // If you have the dual driver remove
const int BIB = 6;            // the comments and enable the other engine
byte speedDer = 255;
byte speedIzq = 100;
byte speed = 255;

void setup() 
{
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

  rf_driver.init();

  Serial.begin(9600);
}

void loop() 
{
  receiveMessage();
  direction(dir);
  steer(steering);

}

void steer(String dir){
  //Serial.println(dir);
}


void direction(String movent)
{
 // Serial.println("movent: "+movent);
  if (movent == "fw"){
    forward();
  }
  if (movent == "bk"){
    backward();
  }
  if (movent == "st"){
    stop_motion();
  }
}

void decodeMessage(String message)
{

  //Serial.println(message);
  String messageLenght = message.substring(0,1);
  String messageType = message.substring(1,2);
  String receivedMessage = message.substring(2, messageLenght.toInt()+1);
  Serial.println(message);
  if (messageType == "x"){
    steering = receivedMessage;
    calculateSteering(receivedMessage.toInt());
  }
  if (messageType == "d"){
    dir = receivedMessage;
  }
}

void calculateSteering(int amount){
  Serial.println("*************************");
 // Serial.println("saywaaaaa");
 // Serial.println("amount: "+String(amount));

  if ( 527 < amount < 501){
   // Serial.println("dead zone");
    speedIzq = 255;
    speedDer = 255;
  }

  if ( 530 < amount ){
   // Serial.println("mayor de 530");
   // Serial.println((amount - 500) * steerRatio);
    speedDer = (amount - 500) * steerRatio;
    speedIzq = 255;
  }

  if (amount < 500 ){
   // Serial.println("menos de 530");
   // Serial.println(amount * steerRatio);
    speedIzq = amount * steerRatio;
    speedDer = 255;
  }

  Serial.println("speedIzq: "+ String(speedIzq));
  Serial.println("speedDer: "+ String(speedDer));

  Serial.println("*************************");
  
}

void receiveMessage()
{
  uint8_t buf[6];
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen))
  {
    String receivedMessage = String((char*)buf);
    decodeMessage(receivedMessage);
    //Serial.println(receivedMessage);
  }
}

void backward()
{
  //Serial.println("backwards");
  analogWrite(AIA, 0);          // Simply reverse the logic ;-)
  analogWrite(AIB, speed);      // Watch the video to grab the knowledge!
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}

void stop_motion()
{
  //Serial.println("stop");
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);      
  analogWrite(BIA, 0);
  analogWrite(BIB, 0);
}

void forward()
{
  //Serial.println("forward");
  analogWrite(AIA, speedIzq);
  analogWrite(AIB, 0);
  analogWrite(BIA, speedDer);
  analogWrite(BIB, 0);
}
