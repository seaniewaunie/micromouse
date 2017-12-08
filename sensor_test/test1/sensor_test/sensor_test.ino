/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* Crated by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int echoPin2 = 11;
const int echoPin3 = 3;


// defines variables
float duration;
float duration2;
float duration3;

float distance;
float distance2;
float distance3;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}


void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance ( Note speed of sound is 343 m/s, and the duration is the amount of time to hit the target and return to the reciever, thus divide by two )
  distance= duration*0.0343*0.5;

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2*0.0343*0.5;
 
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3*0.0343*0.5;
   
  // Prints the distance on the Serial Monitor
  Serial.print("Distance1: ");
  Serial.println(distance);
  Serial.print("Distance2: ");
  Serial.println(distance2);
  Serial.print("Distance3: ");
  Serial.println(distance3);
}
