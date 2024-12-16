/* Smart bin
 *
 * Desc:
 * KONE.620-2024-2025-2 IoT assignment
 * Program monitors fill rate of a bin and transmits the fill level to 
 * Losant server through wifi network.
 *
 * Program author
 * Name: Jukka Välimäki
 * Student number: 153036662
 * UserID: qvk827
 * E-Mail: jukka.valimaki@tuni.fi
 *
 * */

//Define global variables here
int laserValue = 0; //Value read by laser sensor in cm
int sonicValue = 0; //Value read by sonic sensor, 0 = closed, 1 = open
int sonicValueToggle = 0; 
int sendDataTimer = 0; 
int sendDataMaxValue = 300; //Max timer Value when device sends it data losant if no other condition is triggered

void setup() {
  Serial.begin(115200); // Needed for serial print with serial monitor. Data rate is set to 115200 bits per second (baud)
  delay(50);
  laserSensorSetup();
  ultrasonicSensorSetup();
  Serial.println("");
  Serial.print("Application started");
  Serial.println("");

}

void loop() {        
  keepAlive();
  sonicValue = ultrasonicSensor();  // checks ultrasonicSensor if door is open
  //Sends data to losant if triggered by ultraSonicSensor or Timer is reached  
  if(sendDataTimer > sendDataMaxValue || sonicValue != sonicValueToggle){
    laserValue = laserSensor();  // read laser sensor value in cm
    sendData(laserValue, sonicValue); // calls function to send data
    sonicValueToggle = sonicValue;
    sendDataTimer = 0;
  }  
  delay(1000);
  sendDataTimer++;
}
