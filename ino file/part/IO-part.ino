// setup untuk perangkat onewire (sensor DS18B20)
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Variabel untuk menampung nilai suhu yang didapat
float Nilai_Suhu;

//variable untuk menyimpan nilai sensor pH
int Nilai_Sensor_pH;
float Tegangan_Sensor_pH;
float pH_Step;
float Nilai_pH;
float Tegangan_pH_4 = 3.16;
float Tegangan_pH_7 = 2.68;

//output relay pada GPIO 2,0,14,12,13
const int relay_temp = 0;
const int relay_suhu_up = 2;
const int relay_suhu_down = 14;
const int relay_PH_UP = 12;
const int relay_PH_DOWN = 13;

// variable yang akan digunakan untuk proses fuzzyfikasi
float suhu, pH;
float A, B;

