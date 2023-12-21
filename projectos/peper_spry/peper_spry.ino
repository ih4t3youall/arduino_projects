/*
  Creado: Luis del Valle (ldelvalleh@programarfacil.com)
  https://programarfacil.com
*/

// Incluímos la librería para poder controlar el servo
#include <Servo.h>

// Declaramos la variable para controlar el servo
Servo servoMotor;

const int button=11;

void setup() {
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);
  pinMode(button, INPUT);

  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(9);
  servoMotor.write(0);
  servoMotor.write(90);
  delay(2000);
  servoMotor.write(0);
}

void loop() {
  
  // Desplazamos a la posición 0º
  if (digitalRead(button) == HIGH){
    servoMotor.write(90);
  }else {
    servoMotor.write(0);
  }
  
}
