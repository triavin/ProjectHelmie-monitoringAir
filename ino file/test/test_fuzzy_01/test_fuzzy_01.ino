#include <math.h>

// variabel Input Sensor
float suhu, pH;

// variable aturan dan implikasi
float minimumNilaiR[9];
float aturan[9][5];

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

// variable output pompa pH Up
float phOutUpKosong = 0;
float phOutUpSedikit = 50;
float phOutUpBanyak = 100;

// variable output pompa pH Down
float phOutDownKosong = 0;
float phOutDownSedikit = 50;
float phOutDownBanyak = 100;

// variable output pompa Drain
float DrainOutKosong = 0;
float DrainOutSedikit = 50;
float DrainOutBanyak = 100;

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
    aturan[0][2] = phOutUpBanyak;
    aturan[0][3] = phOutDownKosong;
    aturan[0][4] = DrainOutBanyak;

    // aturan untuk kondisi suhu dingin dan ph sedang
    minimumNilaiR[1] = minimum(fuzzifikasiSuhuDingin(), fuzzyfikasiPhSedang());
    aturan[1][0] = tempOutUpBanyak;
    aturan[1][1] = tempOutDownKosong;
    aturan[1][2] = phOutUpKosong;
    aturan[1][3] = phOutDownKosong;
    aturan[1][4] = DrainOutKosong;

    // aturan untuk kondisi suhu dingin dan ph tinggi
    minimumNilaiR[2] = minimum(fuzzifikasiSuhuDingin(), fuzzyfikasiPhTinggi());
    aturan[2][0] = tempOutUpBanyak;
    aturan[2][1] = tempOutDownKosong;
    aturan[2][2] = phOutUpKosong;
    aturan[2][3] = phOutDownBanyak;
    aturan[2][4] = DrainOutBanyak;

    // aturan untuk kondisi suhu sedang dan ph rendah
    minimumNilaiR[3] = minimum(fuzzifikasiSuhuSedang(), fuzzyfikasiPhRendah());
    aturan[3][0] = tempOutUpKosong;
    aturan[3][1] = tempOutDownKosong;
    aturan[3][2] = phOutUpBanyak;
    aturan[3][3] = phOutDownKosong;
    aturan[3][4] = DrainOutBanyak;

    // aturan untuk kondisi suhu sedang dan ph sedang
    minimumNilaiR[4] = minimum(fuzzifikasiSuhuSedang(), fuzzyfikasiPhSedang());
    aturan[4][0] = tempOutUpKosong;
    aturan[4][1] = tempOutDownKosong;
    aturan[4][2] = phOutUpKosong;
    aturan[4][3] = phOutDownKosong;
    aturan[4][4] = DrainOutKosong;

    // aturan untuk kondisi suhu sedang dan ph tinggi
    minimumNilaiR[5] = minimum(fuzzifikasiSuhuSedang(), fuzzyfikasiPhTinggi());
    aturan[5][0] = tempOutUpKosong;
    aturan[5][1] = tempOutDownKosong;
    aturan[5][2] = phOutUpBanyak;
    aturan[5][3] = phOutDownKosong;
    aturan[5][4] = DrainOutBanyak;

    // aturan untuk kondisi suhu panas dan ph rendah
    minimumNilaiR[6] = minimum(fuzzifikasiSuhuPanas(), fuzzyfikasiPhRendah());
    aturan[6][0] = tempOutUpKosong;
    aturan[6][1] = tempOutDownSedikit;
    aturan[6][2] = phOutUpBanyak;
    aturan[6][3] = phOutDownKosong;
    aturan[6][4] = DrainOutBanyak;

    // aturan untuk kondisi suhu panas dan ph sedang
    minimumNilaiR[7] = minimum(fuzzifikasiSuhuPanas(), fuzzyfikasiPhSedang());
    aturan[7][0] = tempOutUpKosong;
    aturan[7][1] = tempOutDownBanyak;
    aturan[7][2] = phOutUpKosong;
    aturan[7][3] = phOutDownKosong;
    aturan[7][4] = DrainOutKosong;

    // aturan untuk kondisi suhu panas dan ph tinggi
    minimumNilaiR[8] = minimum(fuzzifikasiSuhuPanas(), fuzzyfikasiPhTinggi());
    aturan[8][0] = tempOutUpKosong;
    aturan[8][1] = tempOutDownSedikit;
    aturan[8][2] = phOutUpKosong;
    aturan[8][3] = phOutDownBanyak;
    aturan[8][4] = DrainOutBanyak;
    
}



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}