/*
 * This sketch shows an Arduino controlling a MCP4131 digital potentiometer
 * Sketch utilizes the MCP4131 library
 * https://www.arduino.cc/reference/en/libraries/mcp4131-library/
 * After initialization, serial monitor waits for input
 * User inputs a value between 0 and 256
 * Program sets potentiometer value to match input
 * and prints out nominal voltage
 * 
 * Minimum value to drive motors is: 16
 * Value to hit 100 percent: 220
 * March 2022
*/

//Make Sure to change the Serial Monitor to not send a \n character

#include <MCP4131.h>

const int chipSelect = 10;
const int relaySelect = 8;
unsigned int wiperValue;
String incomingString;
unsigned int wiperMax = 255;  //Change this value to change the maximum speed of the cart  **Absolute min is 16 - Absolute max is 255

// Create MCP4131 object nominating digital pin used for Chip Select
MCP4131 Potentiometer(chipSelect);

void setup() {
  // Reset wiper position to 0 Ohms
  wiperValue = 0;
  Potentiometer.writeWiper(wiperValue);

  //add indelay between digital pot start up and the relay
  delay(50);

  //set relay pin as output then set the pin to high to switch relay from default 5k ohms resistance to digital pot output
  pinMode(relaySelect, OUTPUT);
  digitalWrite(relaySelect, HIGH);

  // Begin Serial port and print out welcome message
  Serial.begin(9600);
  Serial.println("MCP4131 Digital Potentiometer Test");
}

void loop() {
  bool isInt;
  incomingString = "";
  // Wait for user input via serial monitor
  if (Serial.available() > 0){
     //Read the incoming string
     incomingString = Serial.readStringUntil('\n');
     //Error checking
     isInt = isDigit(incomingString);
     while(isInt == false){
       if (Serial.available() > 0){
       Serial.println("Error Invalid input: Value entered is not an Int");
       incomingString = Serial.readStringUntil('\n');
       isInt = isDigit(incomingString);
       }
     }

     //Convert to a integer
     wiperValue = incomingString.toInt();

     //limit cart to max power set in initialization value Int wiperMax
     wiperValue = maxPower(wiperValue);

     //Set Potentiomter to step value
     Potentiometer.writeWiper(wiperValue);
     // Print out user input and nominal voltage
     Serial.print(wiperValue);
     Serial.print('\t');
     Serial.print("Nominal Voltage: ");
     Serial.print((5.0 * wiperValue / 256.0) ,DEC);
     Serial.println();
  }

}

bool isDigit(String data) {
  for(int x = 0; x < data.length(); x++) {
    if(!(isDigit(data.charAt(x)))) {
      return false;
    }
  }
  return true;
}

int maxPower(unsigned int wiperValue){
   if(wiperValue > wiperMax){
        wiperValue = wiperMax;
    }
  return wiperValue;
}
