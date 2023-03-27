// variable ssid, password, ip host yang digunakan dan port yang di gunakan pada host
const char *ssid = "Tuyul_plus";
const char *password = "Dblow904rnow";
const char *host = "192.168.1.16";
const int port = 8080;

void setup()
{
    Serial.begin(9600);

    // menghubungkan dengan jaringan wifi
    Serial.print("Connecting to : ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // fungsi WiFi itu harusnya punya library board esp8266 karna gk di import makanya error
    // karna make node mcu dan modul esp8266-12 "kalo gk salah inget nama", makanya nanti diganti ngikutin library
    // baca dokumentasi library dan lakuin testing dulu nanti sebelum coba dipake
    //
    // *note : didocumentasi fungsi yang dipake setWifi(ssid, pass) dan library yang dipake KRwifi.h
    // link library : https://github.com/kelasrobot/KRwifi-Library/archive/master.zip <KRwifi.h>
    //              : https://github.com/bportaluri/WiFiEsp/archive/master.zip <WiFiESP.h>
    //
    // library WiFiESP dibutuhkan karna library KRwifi menggunakan library WiFiESP di dalamnya makanya tetap harus diimport
    // link Documentasi : https://kelasrobot.com/menghubungkan-arduino-uno-nano-mega-dengan-wifi-module/ <part 1>
    //                  : https://kelasrobot.com/arduino-wifi-module-ambil-data-dari-web/                <part 2>
}

void loop()
{
    // penggunaan codinggannya buat terhubung ke wifi ada di setup di loop buat ngirim data coba cek file punya yuda yang v2
}