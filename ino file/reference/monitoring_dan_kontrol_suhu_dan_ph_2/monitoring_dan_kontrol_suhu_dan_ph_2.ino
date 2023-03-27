#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <DallasTemperature.h>

// variable ssid, password, ip host yang digunakan dan port yang di gunakan pada host
const char* ssid = "Tuyul_plus";
const char* password = "Dblow904rnow";
const char* host = "192.168.1.16";
const int port = 8080;

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

// variable anggota suhu
float uDingin[] = {0, 0, 15, 23};
float uSedang[] = {18, 25, 30, 33};
float uPanas[] = {30, 35, 50, 50};

// variable anggota pH
float uSangatAsam[] = {0, 0, 3, 4.5};
float uAsam[] = {3.5, 5, 5, 6.5};
float uNormal[] = {6, 7, 7, 8};
float uBasa[] = {7.5, 9, 9, 10};
float uSangatBasa[] = {9, 11, 14, 14};

// variable output suhu Up
float tUpKosong = 0;
float tUpSedikit = 100;
float tUpBanyak = 200;

// variable output suhu Down
float tDownKosong = 0;
float tDownSedikit = 100;
float tDownBanyak = 200;

// variable output pH Up
float pUpKosong = 0;
float pUpSedikit = 50;
float pUPsedang = 100;
float pUpBanyak = 150;
float pUPSangatBanyak = 200;

// variable output pH Down
float pDownKosong = 0;
float pDownSedikit = 50;
float pDownsedang = 100;
float pDownBanyak = 150;
float pDownSangatBanyak = 200;

// variable rules dan intrepetasi
float minr[15];
float rules[15][4];

float fuDingin(float suhu){
    if (suhu < uDingin[2]){
        return 1;
    }
    else if (suhu > uDingin[2] && suhu < uDingin[3]){
        return (uDingin[3] - suhu) / (uDingin[3] - uDingin[2]);
    }
    else if (suhu > uDingin[3]){
        return 0;
    }
}

float fuSedang(float suhu){
    if (suhu < uSedang[0]){
        return 0;
    }
    else if (suhu > uSedang[0] && suhu < uSedang[1]){
        return (suhu - uSedang[0]) / (uSedang[1] - uSedang[0]);
    }
    else if (suhu > uSedang[1] && suhu < uSedang[2]){
        return 1;
    }
    else if (suhu >= uSedang[2] && suhu <= uSedang[3]){
        return ((uSedang[3] - suhu) / (uSedang[3] - uSedang[2]));
    }
    else if (suhu > uSedang[3]){
        return 0;
    }
}

float fuPanas(float suhu){
    if (suhu < uPanas[0]){
        return 0;
    } 
    else if (suhu >= uPanas[0] && suhu <= uPanas[1]){
        return (suhu - uPanas[0]) / (uPanas[1] - uPanas[0]);
    }
    else if (suhu > uPanas[1]){
        return 1;
    }
}

float fuSangatAsam(float ph){
    if (pH < uSangatAsam[2]){
        return 1;
    }
    else if (uSangatAsam[2] < suhu  && suhu < uSangatAsam[3]){
        return (uSangatAsam[3] - pH) / (uSangatAsam[3] - uSangatAsam[2]);
    }
    else if (suhu > uSangatAsam[3]){
        return 0;
    }
}

float fuAsam(float ph){
    if (pH < uAsam[0]){
        return 0;
    }
    else if (uAsam[0] < pH && pH < uAsam[1]){
        return (pH - uAsam[0]) / (uAsam[1] - uAsam[0]);
    }
    else if (uAsam[1] < pH && pH < uAsam[2]){
        return 1;
    }
    else if (uAsam[2] < pH && pH < uAsam[3]){
        return (uAsam[3] - pH) / (uAsam[3] - uAsam[2]);
    }
    else if (pH > uAsam[3]){
        return 0;
    }
}

float fuNormal(float ph){
    if (pH < uNormal[0]){
        return 0;
    }
    else if (uNormal[0] < pH && pH < uNormal[1]){
        return (pH - uNormal[0]) / (uNormal[1] - uNormal[0]);
    }
    else if (uNormal[1] < pH && pH < uNormal[2]){
        return 1;
    }
    else if (uNormal[2] < pH && pH < uNormal[3]){
        return (uNormal[3] - pH) / (uNormal[3] - uNormal[2]);
    }
    else if (pH > uNormal[3]){
        return 0;
    }
}

float fuBasa(float ph){
    if (pH < uBasa[0]){
        return 0;
    }
    else if (uBasa[0] < pH && pH < uBasa[1]){
        return (pH - uBasa[0]) / (uBasa[1] - uBasa[0]);
    }
    else if (uBasa[1] < pH && pH < uBasa[2]){
        return 1;
    }
    else if (uBasa[2] < pH && pH < uBasa[3]){
        return (uBasa[3] - pH) / (uBasa[3] - uBasa[2]);
    }
    else if (pH > uBasa[3]){
        return 0;
    }
}

float fuSangatBasa(float ph){
    if (pH < uSangatBasa[0]){
        return 0;
    }
    else if (uSangatBasa[0] < pH && pH < uSangatBasa[1]){
        return (pH - uSangatBasa[0]) / (uSangatBasa[1] - uSangatBasa[0]);
    }
    else if (pH > uSangatAsam[2]){
        return 1;
    }
}

// mencari nilai terkecil dari hasil fuzzyfikasi
float Min(float a, float b){
    if (a < b){
        return a;
    }
    else if (b < a){
        return b;
    }
    else {
        return a;
    }
}

// rules fuzzy yang digunakan
void rule(float suhu, float ph){
    
    minr[0] = Min(fuDingin(suhu), fuSangatAsam(ph));
    rules[0][0] = tUpBanyak;
    rules[0][1] = tDownKosong;
    rules[0][2] = pUpKosong;
    rules[0][3] = pDownSangatBanyak;

    minr[1] = Min(fuDingin(suhu), fuAsam(ph));
    rules[1][0] = tUpBanyak;
    rules[1][1] = tDownKosong;
    rules[1][2] = pUpKosong;
    rules[1][3] = pDownBanyak;

    minr[2] = Min(fuDingin(suhu), fuNormal(ph));
    rules[2][0] = tUpBanyak;
    rules[2][1] = tDownKosong;
    rules[2][2] = pUpKosong;
    rules[2][3] = pDownKosong;

    minr[3] = Min(fuDingin(suhu), fuBasa(ph));
    rules[3][0] = tUpBanyak;
    rules[3][1] = tDownKosong;
    rules[3][2] = pUpBanyak;
    rules[3][3] = pDownKosong;

    minr[4] = Min(fuDingin(suhu), fuSangatBasa(ph));
    rules[4][0] = tUpBanyak;
    rules[4][1] = tDownKosong;
    rules[4][2] = pUPSangatBanyak;
    rules[4][3] = pDownKosong;

    minr[5] = Min(fuSedang(suhu), fuSangatAsam(ph));
    rules[5][0] = tUpKosong;
    rules[5][1] = tDownKosong;
    rules[5][2] = pUpKosong;
    rules[5][3] = pDownSangatBanyak;

    minr[6] = Min(fuSedang(suhu), fuAsam(ph));
    rules[6][0] = tUpKosong;
    rules[6][1] = tDownKosong;
    rules[6][2] = pUpKosong;
    rules[6][3] = pDownBanyak;

    minr[7] = Min(fuSedang(suhu), fuNormal(ph));
    rules[7][0] = tUpKosong;
    rules[7][1] = tDownKosong;
    rules[7][2] = pUpKosong;
    rules[7][3] = pDownKosong;

    minr[8] = Min(fuSedang(suhu), fuBasa(ph));
    rules[8][0] = tUpKosong;
    rules[8][1] = tDownKosong;
    rules[8][2] = pUpBanyak;
    rules[8][3] = pDownKosong;

    minr[9] = Min(fuSedang(suhu), fuSangatBasa(ph));
    rules[9][0] = tUpKosong;
    rules[9][1] = tDownKosong;
    rules[9][2] = pUPSangatBanyak;
    rules[9][3] = pDownKosong;

    minr[10] = Min(fuPanas(suhu), fuSangatAsam(ph));
    rules[10][0] = tUpKosong;
    rules[10][1] = tDownBanyak;
    rules[10][2] = pUpKosong;
    rules[10][3] = pDownSangatBanyak;

    minr[11] = Min(fuPanas(suhu), fuAsam(ph));
    rules[11][0] = tUpKosong;
    rules[11][1] = tDownBanyak;
    rules[11][2] = pUpKosong;
    rules[11][3] = pDownBanyak;

    minr[12] = Min(fuPanas(suhu), fuNormal(ph));
    rules[12][0] = tUpKosong;
    rules[12][1] = tDownBanyak;
    rules[12][2] = pUpKosong;
    rules[12][3] = pDownKosong;

    minr[13] = Min(fuPanas(suhu), fuBasa(ph));
    rules[13][0] = tUpKosong;
    rules[13][1] = tDownBanyak;
    rules[13][2] = pUpBanyak;
    rules[13][3] = pDownKosong;

    minr[14] = Min(fuPanas(suhu), fuSangatBasa(ph));
    rules[14][0] = tUpKosong;
    rules[14][1] = tDownBanyak;
    rules[14][2] = pUPSangatBanyak;
    rules[14][3] = pDownKosong;
}

// defuzzyfikasi suhu Up
float defuzzyfikasitUp(float suhu, float ph){
    rule(suhu, ph);
    A = 0;
    B = 0;

    for(int i=0; i<15; i++){
        A += rules[i][0] * minr[i];
        B += minr[i];
    }

    return A / B;
}

// defuzzyfikasi suhu Down
float defuzzyfikasitDown(float suhu, float ph){
    rule(suhu, ph);
    A = 0;
    B = 0;

    for(int i=0; i<15; i++){
        A += rules[i][1] * minr[i];
        B += minr[i];
    }

    return A / B;
}

// defuzzyfikasi pH Up
float defuzzyfikasipUp(float suhu, float ph){
    rule(suhu, ph);
    A = 0;
    B = 0;

    for(int i=0; i<15; i++){
        A += rules[i][2] * minr[i];
        B += minr[i];
    }

    return A / B;
}

// // defuzzyfikasi pH Down
float defuzzyfikasipDown(float suhu, float ph){
    rule(suhu, ph);
    A = 0;
    B = 0;

    for(int i=0; i<15; i++){
        A += rules[i][3] * minr[i];
        B += minr[i];
    }

    return A / B;
}

void setup() {
  Serial.begin(9600);

  // menghubungkan dengan jaringan wifi
  Serial.print("Connecting to : ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // inisialisasi pin input pada sensor ph
  pinMode(Nilai_Sensor_pH, INPUT);

  // inisialisasi pin output pada relay
  pinMode(relay_temp, OUTPUT);
  pinMode(relay_suhu_up, OUTPUT);
  pinMode(relay_suhu_down, OUTPUT);
  pinMode(relay_PH_UP, OUTPUT);
  pinMode(relay_PH_DOWN, OUTPUT);

  delay(2000);
  
  // memastikan semua relay mati saat baru pertama kali dihidupkan
  digitalWrite(relay_temp,HIGH);
  digitalWrite(relay_suhu_up,HIGH);
  digitalWrite(relay_suhu_down,HIGH);
  digitalWrite(relay_PH_UP,HIGH);
  digitalWrite(relay_PH_DOWN,HIGH);
}

void loop() {
  
  WiFiClient client;

  //memeriksa koneksi dengan host apakah baik
  if (!client.connect(host, port)){
    Serial.println("Connection failed");
    return;
  }

  // membaca Nilai Sensor pH
  Nilai_Sensor_pH = analogRead(A0);
  Tegangan_Sensor_pH = Nilai_Sensor_pH * (3.3 / 1023.0);
  pH_Step = (Tegangan_pH_4 - Tegangan_pH_7) / 3;
  Nilai_pH = 7 + (( Tegangan_pH_7 - Tegangan_Sensor_pH) / pH_Step);
  
  // membaca Nilai Sensor Suhu
  sensors.requestTemperatures();
  Nilai_Suhu = sensors.getTempCByIndex(0);

  // mengirim Data sensor ke database
  String Url = "/websensor/insertdatasensor.php?";
  Url += "suhu="+String(Nilai_Suhu);
  Url += "&ph="+String(Nilai_pH);
  
  client.print(String("GET ") + Url + "Http/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client. available() == 0){
    if (millis() - timeout > 3000){
      Serial.println(">>> Client Timeout ");
      Serial.println(">>> Gagal Mengirim Data ");
      client.stop();
      return;
    }
  }

  suhu = Nilai_Suhu;
  pH = Nilai_pH;
  
  float hasilSuhuUp = defuzzyfikasitUp(suhu,pH);
  float hasilSuhuDown = defuzzyfikasitDown(suhu,pH);
  float hasilPHUp = defuzzyfikasipUp(suhu,pH);
  float hasilPHDown = defuzzyfikasipDown(suhu,pH);

  Serial.print("suhu : ");
  Serial.println(suhu);
  Serial.print("pH : ");
  Serial.println(pH);
  Serial.println("");

  Serial.print("fuDingin : ");
  Serial.println(fuDingin(suhu));
  Serial.print("fuDSedang : ");
  Serial.println(fuSedang(suhu));
  Serial.print("fuPanas : ");
  Serial.println(fuPanas(suhu));
  Serial.println("");
  
  Serial.print("fuSangatAsam : ");
  Serial.println(fuSangatAsam(pH));
  Serial.print("fuAsam : ");
  Serial.println(fuAsam(pH));
  Serial.print("fuNormal : ");
  Serial.println(fuNormal(pH));
  Serial.print("fuBasa : ");
  Serial.println(fuBasa(pH));
  Serial.print("fuSangatBasa : ");
  Serial.println(fuSangatBasa(pH));
  Serial.println("");
  
  Serial.print("hasil defuzifikasi suhu up : ");
  Serial.println(hasilSuhuUp);
  Serial.print("hasil defuzifikasi suhu down : ");
  Serial.println(hasilSuhuDown);
  Serial.print("hasil defuzifikasi ph up : ");
  Serial.println(hasilPHUp);
  Serial.print("hasil defuzifikasi ph up : ");
  Serial.println(hasilPHDown);
  Serial.println("");

  delay(60000);
}
