/*
 * Author: Sean Graff 
 * MMVI Micromouse Project
 * Sensors Demonstration 1
 * 
 * The micromouse uses sensors in order to determine distances from walls.
 * 
 * The is done using an ultrasonic transducer, the HC-SR04. This transducer works
 * by sending 8 short sonic pulses, and the duration it takes to recieve all 8
 * of those pulses is then multiplied by the speed of sound. 
 * 
 * Note, the duration is how long it takes for a pulse to hit a target, 
 * and then come back. Since we only want to 'hit' a target, 
 * the duration is divided by two. This gives us the distance to the target, rather than to the target and back.
 * 
 * It is impossible to "trigger" and recieve information from all sensors simultaneously.
 * This is because the sound waves interfere with eachother, and therefore the reading would
 * be wrong.
 * 
 * TODO: test if only using one trigger pin affects the accuracy of the measurements
 * TODO: make sensors an object
 * TODO: getWall function is dependant on the final design of the frame of the micromouse, and our desired distance from each wall.
 */

// SENSOR PINS
const int sensor_trigPin = 9;
const int sensorN_echoPin = 10; // North face Sensor
const int sensorW_echoPin = 11; // West face Sensor
const int sensorE_echoPin = 3; // East face Sensor

// SENSOR VARIABLES
float distance;

// SENSOR FUNCTION PROTOTYPES
void clearPins(const int pin);
void triggerSensors();
float getDistance(const int sensor);


void setup() {
  pinMode(sensor_trigPin, OUTPUT);
  pinMode(sensorN_echoPin, INPUT);
  pinMode(sensorW_echoPin, INPUT);
  pinMode(sensorE_echoPin, INPUT);
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  Serial.println("\n\n-------------------------");
  
  distance = getDistance(sensorN_echoPin);
  Serial.print("Distance for North Sensor: ");
  Serial.println(distance);

  delay(100);

  distance = getDistance(sensorW_echoPin);
  Serial.print("Distance for West Sensor: ");
  Serial.println(distance);

  delay(100);
  
  distance = getDistance(sensorE_echoPin);
  Serial.print("Distance for East Sensor: ");
  Serial.println(distance);
  
  Serial.println("-------------------------");

  delay(800);
}

// clears pin that is sent to it (set's it low)
void clearPins(const int pin){
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
}


// triggers the triggerPin for 10 us
void triggerSensors(){
  digitalWrite(sensor_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor_trigPin, LOW);
}

// return the distance from target in cm
float getDistance(const int sensor){
  clearPins(sensor_trigPin);
  triggerSensors();
  float duration = pulseIn(sensor, HIGH);
  float distance = duration * 0.0343 * 0.5;

  if(distance < 16)
    Serial.println("Wall detected");
  
  return distance;
}

