/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include "thingProperties.h"
#include "EmonLib.h"
EnergyMonitor emon1, emon2, emon3;
void setup() 
{
 // Initialize serial and wait for port to open:
 Serial.begin(9600);
 // This delay gives the chance to wait for a Serial Monitor without blocking if 
none is found
 delay(1500);
 // Defined in thingProperties.h
 initProperties();
 // Connect to Arduino IoT Cloud
 ArduinoCloud.begin(ArduinoIoTPreferredConnection);
 /*
 The following function allows you to obtain more information
 related to the state of network and IoT Cloud connection and errors
 the higher number the more granular information you’ll get.
 The default is 0 (only errors).
 Maximum is 4
 */
 setDebugMessageLevel(2);
 ArduinoCloud.printDebugInfo();
 emon2.current(35, 2.7);
 emon1.voltage(34, 222, 1.7);
 emon3.current(32, 2.7);
}
void loop()
{
 ArduinoCloud.update();
 // Your code here
 emon1.calcVI(20, 2000);
 float supplyVoltage = emon1.Vrms;
 float Irms1 = emon2.calcIrms(1480);
 float Irms2 = emon3.calcIrms(1480);
 Serial.print("V=");
 Serial.print(supplyVoltage);
 Serial.print(" I1=");
 Serial.print(Irms1);
 Serial.print(" I2=");
 Serial.println(Irms2);
 Serial.print("power1=");
 Serial.println(power1);
 Serial.print("power2=");
 Serial.println(power2);
 current1 = Irms1;
 current2 = Irms2;
 voltage = supplyVoltage;
 power1 = Irms1 * supplyVoltage;
 power2 = Irms2 * supplyVoltage;
}