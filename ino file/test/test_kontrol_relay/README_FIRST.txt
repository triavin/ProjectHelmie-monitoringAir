test ini menguji apakah relay dapat bekerja dengan baik
berdasarkan nilai yang didapatkan sensor suhu dan pH

pada pengujian relay 1 sampa 4 terhubung dengan arduino pada pin digital, yaitu :
- relay 1 : 4 
- relay 2 : 5
- relay 3 : 6
- relay 4 : 7

*note
    - sensor membaca nilai dengan cukup baik
    - relay 1 sampai 4 dapat bekerja dengan baik 
    - total delay pada setiap runing yaitu 40 detik yaitu :
        + 30 detik delay untuk sensor pH agar dapat membaca nilai dengan cukup baik
        + 5 detik delay untuk membuat relay suhu tetap dalam kondisi menyala
        + 5 detik delay untuk membuat relay pH tetap dalam kondisi menyala