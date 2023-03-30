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
  Tegangan_Sensor_pH = Nilai_Sensor_pH * (5 / 1023.0) ;
  Serial.print("Nilai Sensor pH : ");
  Serial.print(Nilai_Sensor_pH);
  Serial.print(" | Nilai Tegangan Sensor pH : ");
  Serial.println(Tegangan_Sensor_pH);
  
  // delay 1 menit
  delay(1000);
}

// note 
// jika menggunakan tegangan 5v
// nilai tegangan untuk pH 7  : 2.63 +- 0.01
// nilai untuk pH 7           : 519 +- 1
// nilai tegangan untuk pH 4  : 3.036 +- 0.04
// nilai untuk pH 4           : 621 +- 8