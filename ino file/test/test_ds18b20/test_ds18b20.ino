// include library sensor suhu
#include <OneWire.h>
#include <DallasTemperature.h>

// mendefinisikan pada pin berapa sensor digunakan
#define ONE_WIRE_BUS 11

// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);

void setup()
{
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
  // Start up the library:
  sensors.begin();
}

void loop()
{
  // Send the command for all devices on the bus to perform a temperature conversion:
  sensors.requestTemperatures();

  // Fetch the temperature in degrees Celsius for device index:
  float tempC = sensors.getTempCByIndex(0); // the index 0 refers to the first device
  // Fetch the temperature in degrees Fahrenheit for device index:
  // float tempF = sensors.getTempFByIndex(0);

  // Print the temperature in Celsius in the Serial Monitor:
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.println("C");

  // Wait 1 second:
  delay(1000);
}
