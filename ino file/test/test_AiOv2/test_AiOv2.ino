// include library
#include <KRwifi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// setup untuk perangkat onewire (sensor DS18B20)
#define ONE_WIRE_BUS 12
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensorSuhu(&oneWire);

// variabel ssid dan password wifi dan web server
char *ssid = "Tuyul_plus";
char *pass = "1q2w3e4r5t";
char *server = "192.168.1.110";
const int port = 8080;
String url;

// variable idDevice 
// char idDevice = "PT001";

// inisialisasi variabel untuk sensor pH
int nilaiSensorPh;
double teganganSensorPh, phStep, nilaiPh;
double teganganPh4 = 3.036;
double teganganPh7 = 2.63;

// variabel Input Sensor
float suhu, pH;

// setup Output for Relay
const int relayPompaSuhuUp = 4;
const int relayPompaSuhuDown = 5;
const int relayPompaDrain = 6;
const int relayPompaFill = 7;
const int relayKipas = 8;
const int relayThermoelectric = 9;

// setup Output for LED Indicator
const int ledWifiConnection = 10;
const int ledServerConnection = 11;
const int ledLostConnection = 13;

// variable flag wifi & flag server connection
int flagWifi;
int flagServer;

// variabel hasil defuzzyfikasi
float nilaiOutputSuhuUp, nilaiOutputSuhuDown;
float nilaiOutputPhStabilizer;

// variabel Untuk Defuzzyfikasi
float nilaiPertama, nilaiKedua;
float nilaiSuhuUp, nilaiSuhuDown;
float nilaiPhStabilizer;

// variable aturan dan implikasi
float minimumNilaiR[9];
float aturan[9][3];

// variabel untuk nilai keanggotaan suhu
float fuzzyDingin[4]      = {0, 0, 26, 28};
float fuzzySuhuSedang[4]  = {26, 28, 30, 32};
float fuzzyPanas[4]       = {30, 32, 40, 40};

// vaiabel untuk nilai keanggotaan pH
float fuzzyRendah[4]      = {0, 0 , 5, 6};
float fuzzyPhSedang[4]    = {5, 6, 7, 7.5};
float fuzzyTinggi[4]      = {7, 7.5, 14, 14};

// variable output suhu Up
float tempOutUpKosong = 0;
float tempOutUpSedikit = 50;
float tempOutUpBanyak = 100;

// variable output suhu Down
float tempOutDownKosong = 0;
float tempOutDownSedikit = 50;
float tempOutDownBanyak = 100;

// variable output pompa pH Stabilizer
float phOutStabilizerKosong = 0;
float phOutStabilizerSedang = 50;
float phOutStabilizerBanyak = 100;

// fungsi untuk mengubah nilai input kedalam nilai keanggotaan suhu dingin
float fuzzifikasiSuhuDingin(){

  // if x < C 
  if (suhu < fuzzyDingin[2])
  {
    return 1;
  }

  // if x >= C && x <= D
  else if (suhu >= fuzzyDingin[2] && suhu <= fuzzyDingin[3])
  {
    return (fuzzyDingin[3] - suhu) / (fuzzyDingin[3] - fuzzyDingin[2]);
  }

  // if x >= D
  else if (suhu > fuzzyDingin[3])
  {
    return 0;
  }

  /*
  fungsi untuk merubah nilai input suhu 
  menjadi nilai keanggotaan fuzzy dingin

  jika nilai input suhu kurang dari nilai fuzzyDingin[2] = 26 
  maka nilai keanggotaan fuzzyDingin = 1

  jika nilai input suhu lebih dari atau sama dengan nilai fuzzyDingin[2] = 26 
  dan nilai suhu kurang dari atau sama dengan nilai fuzzyDingin [3] = 28
  maka nilai keanggotaan fuzzyDingin = (d - x) / (d - b)


  jika nilai input suhu lebih dari nilai fuzzyDingin[3] = 28 
  maka nilai keanggotaan fuzzyDingin = 0
  */
}

// fungsi untuk mengubah nilai input kedalam nilai keanggotaan suhu sedang
float fuzzifikasiSuhuSedang(){

  // if x < A
  if (suhu < fuzzySuhuSedang[0])
  {
    return 0;
  }

  // if x >= A && <= B
  else if (suhu >= fuzzySuhuSedang[0] && suhu <= fuzzySuhuSedang[1])
  {
    return ((suhu - fuzzySuhuSedang[1]) / (fuzzySuhuSedang[1] - fuzzySuhuSedang[0]));
  }

  // if x >= B && x <= C
  else if (suhu >= fuzzySuhuSedang[1] && suhu <= fuzzySuhuSedang[2])
  {
    return 1;
  }

  // if x >= C && x <= D
  else if (suhu >= fuzzySuhuSedang[2] && suhu <= fuzzySuhuSedang[3])
  {
    return ((fuzzySuhuSedang[3] - suhu) / (fuzzySuhuSedang[3] - fuzzySuhuSedang[2]));
  }
  
  // if x > D
  else if (suhu > fuzzySuhuSedang[3])
  {
    return 0;
  }

  /*
  fungsi untuk merubah nilai input suhu 
  menjadi nilai keanggotaan fuzzy dingin

  jika nilai input suhu kurang dari nilai fuzzySuhuSedang[0] = 26 
  maka nilai keanggotaan fuzzySuhuSedang = 0

  jika nilai input suhu lebih dari atau sama dengan nilai fuzzySuhuSedang[0] = 26 
  dan nilai suhu kurang dari atau sama dengan nilai fuzzySuhuSedang [1] = 28
  maka nilai keanggotaan fuzzySuhuSedang = (x - b) / (b - a)

  jika nilai input suhu lebih dari atau sama dengan nilai fuzzySuhuSedang[1] = 28 
  dan nilai suhu kurang dari atau sama dengan nilai fuzzySuhuSedang [2] = 30
  maka nilai keanggotaan fuzzySuhuSedang = 1

  jika nilai input suhu lebih dari atau sama dengan nilai fuzzySuhuSedang[2] = 30 
  dan nilai suhu kurang dari atau sama dengan nilai fuzzySuhuSedang [3] = 32
  maka nilai keanggotaan fuzzySuhuSedang = (d - x) / (d - b)


  jika nilai input suhu lebih dari nilai fuzzySuhuSedang[3] = 32
  maka nilai keanggotaan fuzzySuhuSedang = 0
  */
}

// fungsi untuk mengubah nilai input kedalam nilai keanggotaan suhu panas
float fuzzifikasiSuhuPanas(){

  // if x < A 
  if (suhu < fuzzyPanas[0])
  {
    return 0;
  }

  // if x >= A && x <= B
  else if (suhu >= fuzzyPanas[0] && suhu <= fuzzyPanas[1])
  {
    return (suhu - fuzzyPanas[1]) / (fuzzyPanas[1] - fuzzyPanas[0]);
  }

  // if x >= B
  else if (suhu > fuzzyPanas[1])
  {
    return 1;
  }

  /*
  fungsi untuk merubah nilai input suhu 
  menjadi nilai keanggotaan fuzzy Panas

  jika nilai input suhu kurang dari nilai fuzzyPanas[0] = 30 
  maka nilai keanggotaan fuzzyPanas = 0

  jika nilai input suhu lebih dari atau sama dengan nilai fuzzyPanas[0] = 30 
  dan nilai suhu kurang dari atau sama dengan nilai fuzzyPanas [1] = 32
  maka nilai keanggotaan fuzzyPanas = (x - b) / (b - a)

  jika nilai input suhu lebih dari nilai fuzzyPanas[1] = 32
  maka nilai keanggotaan fuzzyPanas = 1
  */
}

// fungsi untuk mengubah nilai input kedalam nilai keanggotaan ph rendah
float fuzzyfikasiPhRendah(){

  // if x < C
  if (pH < fuzzyRendah[2])
  {
    return 1;
  }
  
  // if x >= C && x <= D
  else if (pH >= fuzzyRendah[2] && pH <= fuzzyRendah[3])
  {
    return ((fuzzyRendah[3] - pH) / (fuzzyRendah[3] - fuzzyRendah[2]));
  }

  // if x > D
  else if (pH > fuzzyRendah[3])
  {
    return 0;
  }
  
  /*
  fungsi untuk merubah nilai input pH 
  menjadi nilai keanggotaan fuzzy rendah

  jika nilai input pH kurang dari nilai fuzzyRendah[2] = 5 
  maka nilai keanggotaan fuzzyRendah = 1

  jika nilai input pH lebih dari atau sama dengan nilai fuzzyRendah[2] = 5 
  dan nilai pH kurang dari atau sama dengan nilai fuzzyRendah [3] = 6
  maka nilai keanggotaan fuzzyRendah = (d - x) / (d - b)


  jika nilai input pH lebih dari nilai fuzzyRendah[3] = 6
  maka nilai keanggotaan fuzzyRendah = 0
  */

}

// fungsi untuk mengubah nilai input kedalam nilai keanggotaan ph sedang
float fuzzyfikasiPhSedang(){

  // if x < A
  if (pH < fuzzyPhSedang[0])
  {
    return 0;
  }
  
  // if x >= A && x <= B
  else if (pH >= fuzzyPhSedang[0] && pH <= fuzzyPhSedang[1])
  {
    return ((pH - fuzzyPhSedang[1]) / (fuzzyPhSedang[1] - fuzzyPhSedang[0]));
  }

  // if x >= B && x <= C
  else if (pH >= fuzzyPhSedang[1] && pH <= fuzzyPhSedang[2])
  {
    return 1;
  }

  // if x >= C && x <= D
  else if (pH >= fuzzyPhSedang[2] && pH <= fuzzyPhSedang[3])
  {
    return ((fuzzyPhSedang[3] - pH) / (fuzzyPhSedang[3] - fuzzyPhSedang[2]));
  }

  // if x > D
  else if (pH > fuzzyPhSedang[3])
  {
    return 0;
  }
  
  /*
  fungsi untuk merubah nilai input pH 
  menjadi nilai keanggotaan fuzzy Sedang

  jika nilai input pH kurang dari nilai fuzzyPhSedang[0] = 5
  maka nilai keanggotaan fuzzyPhSedang = 0

  jika nilai input pH lebih dari atau sama dengan nilai fuzzyPhSedang[0] = 5 
  dan nilai pH kurang dari atau sama dengan nilai fuzzyPhSedang [1] = 6
  maka nilai keanggotaan fuzzyPhSedang = (x - b) / (b - a)

  jika nilai input pH lebih dari atau sama dengan nilai fuzzyPhSedang[1] = 6 
  dan nilai pH kurang dari atau sama dengan nilai fuzzyPhSedang [2] = 7
  maka nilai keanggotaan fuzzyPhSedang = 1

  jika nilai input pH lebih dari atau sama dengan nilai fuzzyPhSedang[2] = 7 
  dan nilai pH kurang dari atau sama dengan nilai fuzzyPhSedang [3] = 7.5
  maka nilai keanggotaan fuzzyPhSedang = (d - x) / (d - b)


  jika nilai input pH lebih dari nilai fuzzyPhSedang[3] = 7.5
  maka nilai keanggotaan fuzzyPhSedang = 0
  */

}

// fungsi untuk mengubah nilai input kedalam nilai keanggotaan ph tinggi
float fuzzyfikasiPhTinggi(){

  // if x < A
  if (pH < fuzzyTinggi[0])
  {
    return 0;
  }
  
  // if x >= A && x <= B
  else if (pH >= fuzzyTinggi[0] && pH <= fuzzyTinggi[1])
  {
    return ((pH - fuzzyTinggi[1]) / (fuzzyTinggi[1] - fuzzyTinggi[0]));
  }

  // if x > D
  else if (pH > fuzzyTinggi[1])
  {
    return 1;
  }
  
  /*
  fungsi untuk merubah nilai input pH 
  menjadi nilai keanggotaan fuzzy Tinggi

  jika nilai input pH kurang dari nilai fuzzyTinggi[0] = 7 
  maka nilai keanggotaan fuzzyTinggi = 0

  jika nilai input pH lebih dari atau sama dengan nilai fuzzyTinggi[0] = 7 
  dan nilai pH kurang dari atau sama dengan nilai fuzzyTinggi [1] = 7.5
  maka nilai keanggotaan fuzzyTinggi = (d - x) / (d - b)


  jika nilai input pH lebih dari nilai fuzzyTinggi[1] = 7.5
  maka nilai keanggotaan fuzzyTinggi = 0
  */

}


// fungsi untuk mencari nilai minimum dari hasil fuzzyfikasi
float minimum(float nilai1, float nilai2){
  if (nilai1 < nilai2){
    return nilai1;
  }
  else if (nilai2 < nilai1){
    return nilai2;
  }
  else {
    return nilai1;
  }
}

// implikasi aturan
void implikasi(){
    
    // aturan untuk kondisi suhu dingin dan ph rendah
    minimumNilaiR[0] = minimum(fuzzifikasiSuhuDingin(), fuzzyfikasiPhRendah());
    aturan[0][0] = tempOutUpBanyak;
    aturan[0][1] = tempOutDownKosong;
    aturan[0][2] = phOutStabilizerBanyak;

    // aturan untuk kondisi suhu dingin dan ph sedang
    minimumNilaiR[1] = minimum(fuzzifikasiSuhuDingin(), fuzzyfikasiPhSedang());
    aturan[1][0] = tempOutUpBanyak;
    aturan[1][1] = tempOutDownKosong;
    aturan[1][2] = phOutStabilizerKosong;

    // aturan untuk kondisi suhu dingin dan ph tinggi
    minimumNilaiR[2] = minimum(fuzzifikasiSuhuDingin(), fuzzyfikasiPhTinggi());
    aturan[2][0] = tempOutUpBanyak;
    aturan[2][1] = tempOutDownKosong;
    aturan[2][2] = phOutStabilizerBanyak;

    // aturan untuk kondisi suhu sedang dan ph rendah
    minimumNilaiR[3] = minimum(fuzzifikasiSuhuSedang(), fuzzyfikasiPhRendah());
    aturan[3][0] = tempOutUpKosong;
    aturan[3][1] = tempOutDownKosong;
    aturan[3][2] = phOutStabilizerBanyak;

    // aturan untuk kondisi suhu sedang dan ph sedang
    minimumNilaiR[4] = minimum(fuzzifikasiSuhuSedang(), fuzzyfikasiPhSedang());
    aturan[4][0] = tempOutUpKosong;
    aturan[4][1] = tempOutDownKosong;
    aturan[4][2] = phOutStabilizerKosong;

    // aturan untuk kondisi suhu sedang dan ph tinggi
    minimumNilaiR[5] = minimum(fuzzifikasiSuhuSedang(), fuzzyfikasiPhTinggi());
    aturan[5][0] = tempOutUpKosong;
    aturan[5][1] = tempOutDownKosong;
    aturan[5][2] = phOutStabilizerBanyak;

    // aturan untuk kondisi suhu panas dan ph rendah
    minimumNilaiR[6] = minimum(fuzzifikasiSuhuPanas(), fuzzyfikasiPhRendah());
    aturan[6][0] = tempOutUpKosong;
    aturan[6][1] = tempOutDownSedikit;
    aturan[6][2] = phOutStabilizerBanyak;

    // aturan untuk kondisi suhu panas dan ph sedang
    minimumNilaiR[7] = minimum(fuzzifikasiSuhuPanas(), fuzzyfikasiPhSedang());
    aturan[7][0] = tempOutUpKosong;
    aturan[7][1] = tempOutDownBanyak;
    aturan[7][2] = phOutStabilizerKosong;

    // aturan untuk kondisi suhu panas dan ph tinggi
    minimumNilaiR[8] = minimum(fuzzifikasiSuhuPanas(), fuzzyfikasiPhTinggi());
    aturan[8][0] = tempOutUpKosong;
    aturan[8][1] = tempOutDownSedikit;
    aturan[8][2] = phOutStabilizerBanyak;
}

// fungsi defuzifikasi untuk nilai suhu up
float defuzzifikasiSuhuUp(){

  nilaiPertama = 0;
  nilaiKedua = 0;

  for(int i=0; i<9; i++){
        nilaiPertama += aturan[i][0] * minimumNilaiR[i];
        nilaiKedua += minimumNilaiR[i];
    }

    return nilaiPertama / nilaiKedua;
}

// fungsi deffuzifikasi untuk nilai suhu down
float defuzzifikasiSuhuDown(){

  nilaiPertama = 0;
  nilaiKedua = 0;

  for(int i=0; i<9; i++){
        nilaiPertama += aturan[i][1] * minimumNilaiR[i];
        nilaiKedua += minimumNilaiR[i];
    }

    return nilaiPertama / nilaiKedua;
}

// fungsi deffuzifikasi untuk nilai pH up
float defuzzifikasiPhStabilizer(){

  nilaiPertama = 0;
  nilaiKedua = 0;

  for(int i=0; i<9; i++){
        nilaiPertama += aturan[i][2] * minimumNilaiR[i];
        nilaiKedua += minimumNilaiR[i];
    }

    return nilaiPertama / nilaiKedua;
}

// fungsi untuk mendapatkan nilai suhu dari sensor
float getNilaiSuhu(){
  // mengirim permintaan untuk mendapatkan nilai temperatur sensor
  sensorSuhu.requestTemperatures();

  // memasukan nilai suhu yang didapat sensor kedalam variabel
  suhu = sensorSuhu.getTempCByIndex(0);
}

// fungsi untuk mendapatkan nilai ph dari sensor
float getNilaiPh(){
  // membaca Nilai Sensor pH
  nilaiSensorPh = analogRead(A0);
  teganganSensorPh = nilaiSensorPh * (5 / 1023.0) ;
  phStep = (teganganPh4 - teganganPh7) / 3;
  nilaiPh = 7 + ((teganganPh7 - teganganSensorPh) / phStep);

  // memasukan nilai hasil baca sensor ph kedalam variabel ph
  pH = nilaiPh;
}

void kirimData(float nilaiSuhu, float nilaiPh){
    
    // // mengirim Data sensor ke database
    // String Url = "/testv2/insertdatasensor.php?";
    // Url += "suhu="+String(Nilai_Suhu);
    // Url += "&ph="+String(Nilai_pH);
    
    // client.print(String("GET ") + Url + "Http/1.1\r\n" +
    //               "Host: " + host + "\r\n" +
    //               "Connection: close\r\n\r\n")

    // menambahkan nilai input sensor kedalam variabel url yang akan di panggil
    url = "/testv2/api/create.php?suhu=" + String(nilaiSuhu) + "&ph=" + String(nilaiPh) + "&idDevice=" + "1";

    // mengakses webserver dengan fungsi GET
    httpGet(server, url, port);
}

void kontrolRelay(float suhuUp, float suhuDown, float phStabilizer){

    // Kontrol Relay Pompa Drain dan Fill
    if (phStabilizer > 0)
    {
        // hidupkan pompa ph Up
        digitalWrite(relayPompaDrain, LOW);
        delay(phStabilizer * 300);
        digitalWrite(relayPompaDrain, HIGH);
        delay(1500);
        digitalWrite(relayPompaFill, LOW);
        delay(phStabilizer);
        digitalWrite(relayPompaFill, HIGH);
        delay(1500);
    }
    
    // Kontrol Relay Pompa Suhu Up
    if (suhuUp > 0)
    {
        // hidupkan pompa suhu up dan kipas
        digitalWrite(relayKipas, LOW);
        digitalWrite(relayPompaSuhuUp, LOW);
        delay(suhuUp * 300);
        digitalWrite(relayPompaSuhuUp, HIGH);

        // hidupkan kipas
        delay(suhuUp * 1200);
        digitalWrite(relayKipas, HIGH);
    }

    // Kontrol Relay Pompa Suhu Down
    if (suhuDown > 0)
    {
        // hidupkan kipas
        digitalWrite(relayKipas, LOW);
        delay(suhuDown * 600);

        // hidupkan pompa suhu down
        digitalWrite(relayPompaSuhuDown, LOW);
        delay(suhuDown * 300);
        digitalWrite(relayPompaSuhuDown, HIGH);

        // matikan kipas
        delay(suhuDown * 300);
        digitalWrite(relayKipas, HIGH);
    }
}

void printOutputToSerial(float suhu, float pH, float suhuUp, float suhuDown, float phStabilizier){
  // mencetak hasil output pada serial monitor
  Serial.print("nilai output sensor suhu : ");
  Serial.println(suhu);
  Serial.print("nilai output sensor ph : ");
  Serial.println(pH);
  Serial.print("nilai output suhu up : ");
  Serial.println(suhuUp);
  Serial.print("nilai output suhu down : ");
  Serial.println(suhuUp);
  Serial.print("nilai output ph stabilizer : ");
  Serial.println(phStabilizier);
}

void setup() {
  // memulai serial communication pada rate 9600
  Serial.begin(9600);

  // setup untuk sensor suhu
  sensorSuhu.begin();

  // deklarasi pin output
  pinMode(relayPompaSuhuUp, OUTPUT);
  pinMode(relayPompaSuhuDown, OUTPUT);
  pinMode(relayPompaDrain, OUTPUT);
  pinMode(relayPompaFill, OUTPUT);
  pinMode(relayKipas, OUTPUT);
  pinMode(ledLostConnection, OUTPUT);
  pinMode(ledWifiConnection, OUTPUT);
  pinMode(ledServerConnection, OUTPUT);

  // initial LED indicator
  digitalWrite(ledLostConnection, HIGH);
}

void loop() {
  // cek status wifi
  flagWifi = getWifiStatus();

  if (flagWifi == 0 )
  {
    digitalWrite(ledWifiConnection, LOW);
    digitalWrite(ledLostConnection, HIGH);
    
    // menghubungkan kejaringan wifi
    setWifi(ssid, pass);
    digitalWrite(ledWifiConnection, HIGH);
    digitalWrite(ledLostConnection, LOW);
  }

  // cek status server
  flagServer = getServerStatus(server, port);
  
  if (flagServer == 0)
  {
    digitalWrite(ledServerConnection, LOW);
  } else
  {
    digitalWrite(ledServerConnection, HIGH);
  }
  
  
  // menjalankan fungsi untuk mendapatkan nilai sensor
  getNilaiPh();
  getNilaiSuhu();

  // menjalankan fungsi implikasi
  implikasi();

  // menjalankan fungsi untuk mendapatkan nilai output hasil penerapan metode fuzzy logic
  nilaiOutputSuhuUp            = defuzzifikasiSuhuUp();
  nilaiOutputSuhuDown          = defuzzifikasiSuhuDown();
  nilaiOutputPhStabilizer      = defuzzifikasiPhStabilizer();

  // mencetak hasil output pada serial monitor
  printOutputToSerial(suhu, pH, nilaiOutputSuhuUp, nilaiOutputSuhuDown, nilaiOutputPhStabilizer);

  // kirim data sensor ke DB
  kirimData(suhu, pH);

  // jalankan fungsi kontrol relay
  kontrolRelay(nilaiOutputSuhuUp, nilaiOutputSuhuDown, nilaiOutputPhStabilizer);

  // delay selama 60 detik
  delay(600);
  
}
