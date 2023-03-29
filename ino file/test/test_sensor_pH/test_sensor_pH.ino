// inisialisasi variabel untuk sensor pH
int Nilai_Sensor_pH;
float Tegangan_Sensor_pH;
float pH_Step;
float Nilai_pH;
float Tegangan_pH_4 = 3.16;
float Tegangan_pH_7 = 2.68;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // membaca Nilai Sensor pH
  Nilai_Sensor_pH = analogRead(A0);
  Tegangan_Sensor_pH = Nilai_Sensor_pH * (3.3 / 1023.0);
  pH_Step = (Tegangan_pH_4 - Tegangan_pH_7) / 3;
  Nilai_pH = 7 + (( Tegangan_pH_7 - Tegangan_Sensor_pH) / pH_Step);

}
