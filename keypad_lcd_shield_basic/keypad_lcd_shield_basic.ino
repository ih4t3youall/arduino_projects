#include <LiquidCrystal.h>

//a test pin to check is the board works.
#define TEST_PIN 2
// Initialize the LCD with the pins connected to your Arduino
// Change the pin numbers according to your connections
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  pinMode(TEST_PIN, OUTPUT);

  // Print a welcome message on the LCD
  lcd.print("LCD Keypad Shield");
  lcd.setCursor(0, 1);
  lcd.print("Basic Example");
  delay(2000);

  // Clear the LCD display
  lcd.clear();
}

void loop() {
  // Read the button state
  int buttonValue = analogRead(0);
  lcd.setCursor(0,0);
  lcd.print("arduino keypad1");

  // Check which button is pressed (adjust the values according to your keypad)
  if (buttonValue < 50) {
    lcd.setCursor(0, 1);
    lcd.print("Right Pressed ");
    digitalWrite(TEST_PIN, HIGH);
  } else if (buttonValue < 195) {
    lcd.setCursor(0, 1);
    lcd.print("Up Pressed    ");
  } else if (buttonValue < 380) {
    lcd.setCursor(0, 1);
    lcd.print("Down Pressed  ");
  } else if (buttonValue < 555) {
    lcd.setCursor(0, 1);
    lcd.print("Left Pressed  ");
  } else if (buttonValue < 790) {
    lcd.setCursor(0, 1);
    lcd.print("Select Pressed");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("                "); // Clear the line if no button is pressed
    digitalWrite(TEST_PIN, LOW);
  }

  // Add a slight delay to avoid button bounce
  delay(100);
}
