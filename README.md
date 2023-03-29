# Project monitoring dan kontrol suhu dan pH otomatis

## Part Info

bagian dari seluruh program yang akan di upload dibagi menjadi beberapa part
part-part ini dapat menjadi satu bagian utama dengan urutan

**import => IO => Fuzzy => Send Data**

namun urutan dapat digunakan sesuai kebutuhan !

pembagian bagian utama bertujuan untuk mempermudah proses modifikasi codingan dan tracking perubahan pada program.

## Sebelum masuk tahap final pada penggabungan !

sebelum masuk ke tahap final, file dibuat dalam folder test untuk melakukan kalibrasi sensor, test IO dan ujicoba send data 
terlebih dahulu

pembuatan file percobaan harus dilakukan pada folder test baik itu pengujian semua fitur maupun gabungan dari semua fitur
penggabungan semua fitur masih masuk pada tahap test, jika program dan alat sudah dirasa cukup stabil baru akan masuk pada folder final.

perubahan pada folder final hanya akan berisi perubahan bersifat minor sedangkan perubahan bersifat major akan diletakan pada folder test.

## tahap 1 test yang akan dilakukan 

1. **test relay** :white_check_mark:
2. **test all sensor** 
    * Sensor Suhu (ds18b20) :white_check_mark:
    * Sensor pH (4502C)
        * kalibrasi Module :white_check_mark:
        * kalibrasi Software
        * test sensor dengan media air tanpa buffer
3. **kontrol relay dengan nilai sensor**
4. **send data to db**

## tahap 2 test yang akan dilakukan 

1. **test logika fuzzy dengan input nilai sensor (tanpa output relay) output akan melalui serial monitor untuk mempermudah pembacaan data**

>Periksa apakah hasil output logika fuzzy sesuai dengan hasil yang ada pada matlab !

## tahap 3 test yang akan dilakukan 

1. **test logika fuzzy dengan input nilai sensor (dengan output relay)**
2.  **tambah fitur send data** 

## PART INFO

* arduino uno R3
* esp12 (Kelas Robot Module)
* DS18B20
* pH Sensor
* Relay Module 6 channel + 1 channel
* 4 Motor DC 12v (pump)
* Thermoelectrik
* Power Supply 12v 10A
* 2 Waterblok
* 2 Heatsink
* Fan 12v DC

## Software Tools

* arduino IDE
* VSCode
* XAMPP
* mySQL Front
* Matlab
## Authors

- [Aldi Triavin Dwi Putra](https://www.https://github.com/triavin)