// inisialisasi variabel untuk sensor pH
int Nilai_Sensor_pH;
double Tegangan_Sensor_pH;
const int sensorPin  = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  Serial.println("Welcome");
}

void loop() {
  // membaca Nilai Sensor pH
  Nilai_Sensor_pH = analogRead(sensorPin);
  Tegangan_Sensor_pH = 5 / 1024.0 * Nilai_Sensor_pH;
  Serial.print("Nilai Sensor pH : ");
  Serial.print(Nilai_Sensor_pH);
  Serial.print(" | Nilai Tegangan Sensor pH : ");
  Serial.println(Tegangan_Sensor_pH);
  
  delay(1000);
}
