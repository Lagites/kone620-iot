/*
Ultrasonic Sensor HC-SR04 

*/
// pin numbers for Firebeetle 32
const int trigPin = 25; //orange D2
const int echoPin = 26; //white D3

// also connect 3.3V and GND to power the sensor

// defines variables
long duration;
int distance;

void ultrasonicSensorSetup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.println("Ultrasonic Sensor setup complete");
}

int ultrasonicSensor( ) {

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(40); // was 10
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Ultrasonic Distance [cm]: ");
  Serial.println(distance);
  if(distance > 10) //Door is open
    return 1;
  return 0; // Door is closed
  
  }
