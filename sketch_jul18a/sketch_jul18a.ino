void setup() {
  pinMode(13, OUTPUT);  // Set pin 13 as an OUTPUT
}

void loop() {
  digitalWrite(13, HIGH);  // Turn ON the LED
  delay(1000);             // Wait for 1 second
  digitalWrite(13, LOW);   // Turn OFF the LED
  delay(1000);             // Wait for 1 second
}
