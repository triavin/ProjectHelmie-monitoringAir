# !!! part info !!! 

bagian dari seluruh program yang akan di upload dibagi menjadi beberapa part
part-part ini dapat menjadi satu bagian utama dengan urutan

### import => IO => Fuzzy => Send Data 

namun urutan dapat digunakan sesuai kebutuhan
pembagian bagian utama bertujuan untuk mempermudah proses modifikasi codingan dan tracking perubahan pada program.

# !!! sebelum masuk tahap final pada penggabungan !!!

sebelum masuk ke tahap final, file dibuat dalam folder test untuk melakukan kalibrasi sensor, test IO dan ujicoba send data 
terlebih dahulu

pembuatan file percobaan harus dilakukan pada folder test baik itu pengujian semua fitur maupun gabungan dari semua fitur
penggabungan semua fitur masih masuk pada tahap test, jika program dan alat sudah dirasa cukup stabil baru akan masuk pada folder final.

perubahan pada folder final hanya akan berisi perubahan bersifat minor sedangkan perubahan bersifat major akan diletakan pada folder test.

## !!! tahap 1 test yang akan dilakukan !!!

test relay => test all sensor => kontrol relay dengan nilai sensor yang didapat dengan nilai crips => send data to db

## !!! tahap 2 test yang akan dilakukan !!!

test logika fuzzy dengan input nilai sensor (tanpa output relay) 

### Periksa apakah hasil output logika fuzzy sesuai dengan hasil yang ada pada matlab !!!

## !!! tahap 3 test yang akan dilakukan !!!

test logika fuzzy dengan input nilai sensor (dengan output relay) => tambah fitur send data 
