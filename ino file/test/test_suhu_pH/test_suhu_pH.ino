// inisialisasi variabel untuk sensor pH
int Nilai_Sensor_pH;
double Tegangan_Sensor_pH;
double pH_Step;
double Nilai_pH;
double Tegangan_pH_4 = 3.036;
double Tegangan_pH_7 = 2.63;

// include library sensor suhu
#include <OneWire.h>
#include <DallasTemperature.h>

// mendefinisikan pada pin berapa sensor digunakan
#define ONE_WIRE_BUS 11

// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);

void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
  Serial.println("Welcome Test stage start...");
  // Start up the library:
  sensors.begin();
}

void loop() {
  // Send the command for all devices on the bus to perform a temperature conversion:
  sensors.requestTemperatures();

  // Fetch the temperature in degrees Celsius for device index:
  float tempC = sensors.getTempCByIndex(0); // the index 0 refers to the first device
  // membaca Nilai Sensor pH
  Nilai_Sensor_pH = analogRead(A0);
  Tegangan_Sensor_pH = Nilai_Sensor_pH * (5 / 1023.0) ;
  pH_Step = (Tegangan_pH_4 - Tegangan_pH_7) / 3;
  Nilai_pH = 7 + ((Tegangan_pH_7 - Tegangan_Sensor_pH) / pH_Step);


  // Print the temperature in Celsius in the Serial Monitor:
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.print("C | ");

  // mencetak hasil baca sensor pada serial monitor
  Serial.print("Nilai Sensor pH : ");
  Serial.print(Nilai_Sensor_pH);
  Serial.print(" | Nilai Tegangan Sensor pH : ");
  Serial.print(Tegangan_Sensor_pH);
  Serial.print(" | Nilai pH Air : ");
  Serial.println(Nilai_pH);

  
  // Wait 1 second:
  delay(360000);
}
