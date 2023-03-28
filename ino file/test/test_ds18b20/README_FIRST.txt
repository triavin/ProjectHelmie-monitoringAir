sumber referensi berasal dari:
https://www.makerguides.com/ds18b20-arduino-tutorial/

sensor suhu ds18b20 menggunakan 2 library, yaitu:
- OneWire
- DallasTemperature

sensor harus ditentukan terlebih dahulu terhubung pada pin berapa arduino.
kemudian akan dipanggil pada class OneWire untuk dapat berkomunikasi
kemudian class OneWire yang sudah berisikan informasi pin sensor akan 
menjadi referensi untuk library DallasTemperature dan akan merubah nilai yang dibaca sensor (berupa tegangan) 
menjadi nilai suhu seperti celsius dan fahrenheit.

penggabungan sensor sangat mudah dan tidak memerlukan kalibrasi terlebih dahulu.