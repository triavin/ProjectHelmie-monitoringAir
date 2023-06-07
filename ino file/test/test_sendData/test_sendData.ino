#include <LiquidCrystal_I2C.h>
#include <KRwifi.h>

// variabel ssid dan password wifi dan web server
char *ssid = "Tuyul_plus";
char *pass = "1q2w3e4r5t";

char *server = "monitoringbanjirunpam01.000webhostapp.com";
String url;

void setup()
{
    Serial.begin(9600);

    // menghubungkan kejaringan wifi
    setWifi(ssid, pass);
}

void kirimData(float nilaiSuhu, float nilaiPh)
{
    // menambahkan nilai input sensor kedalam variabel url yang akan di panggil
    url = "/data_sensor.php?suhu=" + String(nilaiSuhu) + "&ph=" + String(nilaiPh);

    // mengakses webserver dengan fungsi GET
    httpGet(server, url, 80);
    
}

void loop()
{
    kirimData(suhu,ph)
    delay(1000);
}