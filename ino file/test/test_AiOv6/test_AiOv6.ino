// include library
#include <KRwifi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// setup untuk perangkat onewire (sensor DS18B20)
#define ONE_WIRE_BUS 11
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensorSuhu(&oneWire);

// variabel ssid dan password wifi dan web server
//char *ssid = "Tuyul_plus";
//char *pass = "1q2w3e4r5t";

char *ssid = "ALT_F4";
char *pass = "MT4sumA$";

char *server = "192.168.86.101";

// setup Output for Relay
#define relayKipas 5 // relay 1
#define relayThermo 6 // relay 2
#define relayPompaSuhuDown 7 // relay 3
#define relayPompaSuhuUp 8 // relay 4
#define relayPompaDrain 9 // relay 5
#define relayPompaFill 10 // relay 6

// variable flag wifi & flag server connection
int flagWifi;
int flagServer;

// inisialisasi variabel untuk sensor pH
float suhu = 0;
float pH = 0;
int nilaiSensorPh;
double teganganSensorPh, phStep;
const float teganganPh4 = 3.036;
const float teganganPh7 = 2.63;


// variabel Untuk Defuzzyfikasi
float nilaiPertama, nilaiKedua;
float nilaiSuhuUp, nilaiSuhuDown;
float nilaiPhStabilizer;

// variable aturan dan implikasi
float minimumNilaiR[9];
float aturan[9][3];

// variabel untuk nilai keanggotaan suhu
const float fuzzyDingin[4]      = {0, 0, 26, 28};
const float fuzzySuhuSedang[4]  = {26, 28, 30, 32};
const float fuzzyPanas[4]       = {30, 32, 40, 40};

// vaiabel untuk nilai keanggotaan pH
const float fuzzyRendah[4]      = {0, 0 , 5, 6};
const float fuzzyPhSedang[4]    = {5, 6, 7, 7.5};
const float fuzzyTinggi[4]      = {7, 7.5, 14, 14};

// variable output suhu Up
const int tempOutUpKosong = 0;
const int tempOutUpSedikit = 50;
const int tempOutUpBanyak = 100;

// variable output suhu Down
const int tempOutDownKosong = 0;
const int tempOutDownSedikit = 50;
const int tempOutDownBanyak = 100;

// variable output pompa pH Stabilizer
const int phOutStabilizerKosong = 0;
const int phOutStabilizerSedang = 50;
const int phOutStabilizerBanyak = 100;

// fungsi untuk mengubah nilai input kedalam nilai keanggotaan suhu dingin
float fuzzifikasiSuhuDingin(){

  // if x < C 
  if (suhu <= fuzzyDingin[2]) {
    return 1;
  }

  // if x >= C && x <= D
  else if (suhu >= fuzzyDingin[2] && suhu <= fuzzyDingin[3]) {
    return (fuzzyDingin[3] - suhu) / (fuzzyDingin[3] - fuzzyDingin[2]);
  }

  // if x >= D
  else if (suhu > fuzzyDingin[3]) {
    return 0;
  }

}

// fungsi untuk mengubah nilai input kedalam nilai keanggotaan suhu sedang
float fuzzifikasiSuhuSedang() {
    if (suhu <= fuzzySuhuSedang[0]) {
        return 0;
    } else if (suhu >= fuzzySuhuSedang[0] && suhu <= fuzzySuhuSedang[1]) {
        return (suhu - fuzzySuhuSedang[0]) / (fuzzySuhuSedang[1] - fuzzySuhuSedang[0]);  // Diperbaiki dari fuzzySuhuSedang[1]
    } else if (suhu >= fuzzySuhuSedang[1] && suhu <= fuzzySuhuSedang[2]) {
        return 1;
    } else if (suhu >= fuzzySuhuSedang[2] && suhu <= fuzzySuhuSedang[3]) {
        return (fuzzySuhuSedang[3] - suhu) / (fuzzySuhuSedang[3] - fuzzySuhuSedang[2]);
    } else {
        return 0;
    }
}

// fungsi untuk mengubah nilai input kedalam nilai keanggotaan suhu panas
float fuzzifikasiSuhuPanas(){

  // if x < A 
  if (suhu <= fuzzyPanas[0]) {
    return 0;
  }

  // if x >= A && x <= B
  else if (suhu >= fuzzyPanas[0] && suhu <= fuzzyPanas[1]) {
    return (suhu - fuzzyPanas[0]) / (fuzzyPanas[1] - fuzzyPanas[0]);
  }

  // if x >= B
  else if (suhu >= fuzzyPanas[1]) {
    return 1;
  }

}

// fungsi untuk mengubah nilai input kedalam nilai keanggotaan ph rendah
float fuzzyfikasiPhRendah(){

  // if x < C
  if (pH <= fuzzyRendah[2]) {
    return 1;
  }
  
  // if x >= C && x <= D
  else if (pH >= fuzzyRendah[2] && pH <= fuzzyRendah[3]) {
    return ((fuzzyRendah[3] - pH) / (fuzzyRendah[3] - fuzzyRendah[2]));
  }

  // if x > D
  else if (pH >= fuzzyRendah[3]) {
    return 0;
  }

}

// fungsi untuk mengubah nilai input kedalam nilai keanggotaan ph sedang
float fuzzyfikasiPhSedang() {
    if (pH <= fuzzyPhSedang[0]) {
        return 0;
    } else if (pH >= fuzzyPhSedang[0] && pH <= fuzzyPhSedang[1]) {
        return (pH - fuzzyPhSedang[0]) / (fuzzyPhSedang[1] - fuzzyPhSedang[0]);
    } else if (pH >= fuzzyPhSedang[1] && pH <= fuzzyPhSedang[2]) {
        return 1;
    } else if (pH >= fuzzyPhSedang[2] && pH <= fuzzyPhSedang[3]) {
        return (fuzzyPhSedang[3] - pH) / (fuzzyPhSedang[3] - fuzzyPhSedang[2]);
    } else {
        return 0;
    }
}

// fungsi untuk mengubah nilai input kedalam nilai keanggotaan ph tinggi
float fuzzyfikasiPhTinggi(){

  // if x < A
  if (pH <= fuzzyTinggi[0]) {
    return 0;
  }
  
  // if x >= A && x <= B
  else if (pH >= fuzzyTinggi[0] && pH <= fuzzyTinggi[1]) {
    return ((pH - fuzzyTinggi[0]) / (fuzzyTinggi[1] - fuzzyTinggi[0]));
  }

  // if x > D
  else if (pH >= fuzzyTinggi[1]) {
    return 1;
  }
  
}

// fungsi untuk mencari nilai minimum dari hasil fuzzyfikasi
float minimum(float nilai1, float nilai2) {
    if (nilai1 < nilai2) {
        return nilai1;
    }else if (nilai2 < nilai1)
    {
      return nilai2;
    }
    else
    {
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
    aturan[6][1] = tempOutDownBanyak;
    aturan[6][2] = phOutStabilizerBanyak;

    // aturan untuk kondisi suhu panas dan ph sedang
    minimumNilaiR[7] = minimum(fuzzifikasiSuhuPanas(), fuzzyfikasiPhSedang());
    aturan[7][0] = tempOutUpKosong;
    aturan[7][1] = tempOutDownBanyak;
    aturan[7][2] = phOutStabilizerKosong;

    // aturan untuk kondisi suhu panas dan ph tinggi
    minimumNilaiR[8] = minimum(fuzzifikasiSuhuPanas(), fuzzyfikasiPhTinggi());
    aturan[8][0] = tempOutUpKosong;
    aturan[8][1] = tempOutDownBanyak;
    aturan[8][2] = phOutStabilizerBanyak;
}

// fungsi defuzifikasi untuk nilai suhu up
float defuzzifikasiSuhuUp(){

  // implikasi();
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

  // implikasi();
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

  // implikasi();
  nilaiPertama = 0;
  nilaiKedua = 0;

  for(int i=0; i<9; i++){
        nilaiPertama += aturan[i][2] * minimumNilaiR[i];
        nilaiKedua += minimumNilaiR[i];
    }

    return nilaiPertama / nilaiKedua;
}

// fungsi untuk mendapatkan nilai suhu dari sensor
void getNilaiSuhu(){
  float temp = 0;
  // mengirim permintaan untuk mendapatkan nilai temperatur sensor
  sensorSuhu.requestTemperatures();

  // memasukan nilai suhu yang didapat sensor kedalam variabel
  temp = sensorSuhu.getTempCByIndex(0);

  if (temp != 0) {
    suhu = temp;
  }
  
}

// fungsi untuk mendapatkan nilai ph dari sensor
void getNilaiPh(){
  float temp = 0;
  // membaca Nilai Sensor pH
  nilaiSensorPh = analogRead(A0);
  teganganSensorPh = (5 / 1023.0) * nilaiSensorPh ;
  phStep = 3 / (teganganPh4 - teganganPh7);
  temp = 7 + ((teganganPh7 - teganganSensorPh) / phStep);

  if (pH != temp) {
    pH = temp;
  }
  
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
        delay(phStabilizer * 300);
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
void checkWifiStatus(){
  // cek status wifi
  flagWifi = getWifiStatus();
  if (flagWifi == 0 )
  {
    // menghubungkan kejaringan wifi
    setWifi(ssid, pass);
  }
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
  pinMode(relayThermo, OUTPUT);

  digitalWrite(relayPompaSuhuUp, LOW);
  delay(10000);
  digitalWrite(relayPompaSuhuUp, HIGH);
  digitalWrite(relayPompaSuhuDown, LOW);
  delay(10000);
  digitalWrite(relayPompaSuhuDown, HIGH);
  digitalWrite(relayPompaDrain, HIGH);
  digitalWrite(relayPompaFill, HIGH);
  digitalWrite(relayKipas, HIGH);
  digitalWrite(relayThermo, HIGH);
  // initial LED indicator

  // menghubungkan kejaringan wifi
  setWifi(ssid, pass);
}

void loop() {
  
  checkWifiStatus();

  while(flagWifi != 1){
    checkWifiStatus();
  }
  // menjalankan fungsi untuk mendapatkan nilai sensor
  getNilaiPh();
  getNilaiSuhu();

  if (suhu != 0 && pH != 0) {
    implikasi();
    // menjalankan fungsi untuk mendapatkan nilai output hasil penerapan metode fuzzy logic
    float nilaiOutputSuhuUp            = defuzzifikasiSuhuUp();
    float nilaiOutputSuhuDown          = defuzzifikasiSuhuDown();
    float nilaiOutputPhStabilizer      = defuzzifikasiPhStabilizer();
    
    String url = "/testv2/api/createDetail.php?idD=7&suhu=" + String(suhu) + "&ph=" + String(pH) + "&osu=" + String(nilaiOutputSuhuUp) + "&osd=" + String(nilaiOutputSuhuDown) + "&op=" + String(nilaiOutputPhStabilizer);
    Serial.println(url);
    httpGet(server, url, 8080);  
    
    // jalankan fungsi kontrol relay
    kontrolRelay(nilaiOutputSuhuUp, nilaiOutputSuhuDown, 0);
  }

  Serial.println("suhu atau pH bernilai 0");
  Serial.print("suhu : ");
  Serial.println(suhu);
  Serial.print("pH : ");
  Serial.println(pH);
  Serial.println("========================================");
  
  // delay selama 60 detik
  delay(60000);
}
