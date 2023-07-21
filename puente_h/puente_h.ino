const int AIA = 3;
const int AIB = 4;
const int BIA = 5;            // If you have the dual driver remove
const int BIB = 6;            // the comments and enable the other engine
byte speed = 255;

void setup() {
  Serial.begin(9600);
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
}
void loop() {
  forward();                    // Forward and back forever!
  delay(4000);
  backward();
  delay(4000);

}
void backward()
{
  analogWrite(AIA, 0);          // Simply reverse the logic ;-)
  analogWrite(AIB, speed);      // Watch the video to grab the knowledge!
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}
void forward()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}