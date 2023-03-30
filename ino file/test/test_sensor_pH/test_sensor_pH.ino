// inisialisasi variabel untuk sensor pH
int Nilai_Sensor_pH;
double Tegangan_Sensor_pH;
double pH_Step;
double Nilai_pH;
double Tegangan_pH_4 = 3.036;
double Tegangan_pH_7 = 2.63;

void setup()
{
  Serial.begin(9600);
  Serial.println("Welcome Test stage start...");
}

void getDataPh()
{
  // membaca Nilai Sensor pH
  Nilai_Sensor_pH = analogRead(A0);
  Tegangan_Sensor_pH = Nilai_Sensor_pH * (5 / 1023.0) ;
  pH_Step = (Tegangan_pH_4 - Tegangan_pH_7) / 3;
  Nilai_pH = 7 + ((Tegangan_pH_7 - Tegangan_Sensor_pH) / pH_Step);

  // mencetak hasil baca sensor pada serial monitor
  Serial.print("Nilai Sensor pH : ");
  Serial.print(Nilai_Sensor_pH);
  Serial.print(" | Nilai Tegangan Sensor pH : ");
  Serial.print(Tegangan_Sensor_pH);
  Serial.print(" | Nilai pH Air : ");
  Serial.println(Nilai_pH);
  
}

void loop()
{
  getDataPh();

  // Delay 1 menit
  delay(60000);
}
