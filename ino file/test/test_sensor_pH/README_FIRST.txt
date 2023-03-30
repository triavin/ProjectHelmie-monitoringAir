link referensi:
https://www.hackster.io/infoelectorials/project-021-arduino-liquid-ph0-14-detection-sensor-project-a92093
https://www.electroniclinic.com/ph-meter-arduino-ph-meter-calibration-diymore-ph-sensor-arduino-code/
https://haraduino.blogspot.com/2020/04/cara-kalibrasi-sensor-ph-arduino.html

testing untuk sensor pH (pH 4502C) terdiri dari beberapa langkah atau tahapan, yaitu:
- kalibrasi sensor pH (bisa ikutin yang ada diskripsi Aldi)
- mengujian sensor pH secara langsung

tahap kalibrasi ada dua yaitu:
- kalibrasi via code
- kalibrasi via Module

* kalibrasi yang dilakukan via code 

  akan menangkap nilai yang diberikan pada sensor pH tertentu
  kemudian akan hasilnya akan digunakan untuk perhitungan pada saat sensor membaca nilai pH baru

  pada file test_sensor_pH.ino contoh pengkalibrasian ini terdapat 
  pada variabel Tegangan_pH_4 dan Tegangan_pH_7. nilai yang ditetapkan pada variabel tersebur
  didapat dari pembacaan sensor terhadap pH air dengan nilai pH 4 dan pH 6.86

  nilai variabel tersebut digunakan pada pembacaan sensor dengan rumus

  nilai pH = 7 + ((Tegangan_pH_7 - Tegangan_Sensor) / pH_Step)

  Keterangan:
  Tegangan_pH_7   : hasil pembacaan sensor pada air dengan pH 7
  Tegangan_Sensor : hasil pembacaan sensor
  pH_Step         : tegangan pH 4 – tegangan pH 7 / (PH7 - PH4)

* kalibrasi yang dilakukan via module

  kalibrasi ini dilakukan dengan melakukan pemantauan tegangan yang diberikan module
  kemudia kita akan memutar potensio meter yang ada pada modul untuk menyesuaikan tegangan
  jika menggunakan nilai tegangan 5v maka kita mencari nilai tengah dari 5v yaitu 2,5v.
  
  penyetelan module ini dilakukan dengan kondisi bagian groud prob pada modul dihubungkan dengan bagian positif
  yang terleta pada bagian tengah prob. tujuan dari menghubungkan bagian groud dan positif ini untuk mencari nilai
  yang akan diberikan module jika membaca air dengan nilai pH 7.

*note 30-03-23 :
  - Update nilai variabel pH 7 hasil kalibrasi from 2.68 to 2.53
  - Update rumus tegangan sensor mengikuti tegangan yang digunakan yaitu 5v
  - Update loop menjadi memanggil function getDataPh()