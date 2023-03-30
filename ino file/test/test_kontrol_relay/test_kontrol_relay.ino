// add library for themp sensor

#include <OneWire.h>
#include <DallasTemperature.h>

// setup temp sensor
#define ONE_Wire_BUS 11
OneWire oneWire(ONE_Wire_BUS);
DallasTemperature sensor_suhu(&oneWire);
float Nilai_Suhu;

// setup pH sensor variabel
const int sensorPin = A0;
int Nilai_Sensor_pH;
float Tegangan_Sensor_pH;
float Tegangan_pH4 = 3.036;
float Tegangan_pH7 = 2.53;
float pH_Step = (Tegangan_pH4 - Tegangan_pH7) / 3;
float Nilai_pH;

// setup Output for Relay
const int relay_1 = 4;
const int relay_2 = 5;
const int relay_3 = 6;
const int relay_4 = 7;
const int relay_5 = 8;
const int relay_6 = 9;
const int relay_7 = 10;

void setup() {
  // setup serial monitor
  Serial.begin(9600);

  // setup I/O
  sensor_suhu.begin();
  pinMode(sensorPin, INPUT);
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);
  pinMode(relay_5, OUTPUT);
  pinMode(relay_6, OUTPUT);
  pinMode(relay_7, OUTPUT);

  // set relay to off
  digitalWrite(relay_1, HIGH);
  digitalWrite(relay_2, HIGH);
  digitalWrite(relay_3, HIGH);
  digitalWrite(relay_4, HIGH);
  digitalWrite(relay_5, HIGH);
  digitalWrite(relay_6, HIGH);
  digitalWrite(relay_7, HIGH);

  // print teks on serial monitor
  Serial.println("Testing in on going....");
}

void getDataSensor() {
  // get data sensor pH
  Nilai_Sensor_pH = analogRead(sensorPin);
  Tegangan_Sensor_pH = Nilai_Sensor_pH * (5 / 1023.0);
  Nilai_pH = 7 + ((Tegangan_pH7 - Tegangan_Sensor_pH) / pH_Step);

  // get data sensor temp
  sensor_suhu.requestTemperatures();
  Nilai_Suhu = sensor_suhu.getTempCByIndex(0);  // the index 0 refers to the first device
}

void loop() {
  // put your main code here, to run repeatedly:
  getDataSensor();

  // print nilai suhu dan pH pada serial monitor
  Serial.print("suhu : ");
  Serial.print(Nilai_Suhu);
  Serial.print(" | pH : ");
  Serial.println(Nilai_pH);

  // simple logic to turn relay 1 & 2 base on temp sensor
  if (Nilai_Suhu > 27 && Nilai_Suhu < 30) {
    digitalWrite(relay_1, LOW);
    delay(5000);
    digitalWrite(relay_1, HIGH);
  } else {
    digitalWrite(relay_2, LOW);
    delay(5000);
    digitalWrite(relay_2, HIGH);
  }

  // simple logic to turn relay 3 & 4 base on pH sensor
  if(Nilai_pH > 4 && Nilai_pH < 6){
    digitalWrite(relay_3, LOW);
    delay(5000);
    digitalWrite(relay_3, HIGH);
  } else {
    digitalWrite(relay_4, LOW);
    delay(5000);
    digitalWrite(relay_4,HIGH);
  }

  // delay 30 detik
  delay(30000);
}
