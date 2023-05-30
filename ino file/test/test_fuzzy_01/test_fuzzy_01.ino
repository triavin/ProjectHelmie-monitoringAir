#include <math.h>
// variabel untuk nilai keanggotaan suhu
float drajatKeanggotaanDingin;
float drajatKeanggotaanSuhuSedang1, drajatKeanggotaanSuhuSedang2;
float drajatKeanggotaanPanas;
float fuzzyDingin[4]      = {0, 26, 26, 28};
float fuzzySuhuSedang[4]  = {26, 28, 30, 32};
float fuzzyPanas[4]       = {30, 32, 40, 40};

// vaiabel untuk nilai keanggotaan pH
float drajatKeanggotaanRendah;
float drajatKeanggotaanSedang1, drajatKeanggotaanSedang2;
float drajatKeanggotaanTinggi;
float fuzzyRendah[4]      = {0, 0 , 5, 6};
float fuzzyPhSedang[4]    = {5, 6, 7, 7.5};
float fuzzyTinggi[4]      = {7, 7.5, 14, 14};

float suhu, pH;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void fuzzifikasiSuhuDingin(){

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

void fuzzifikasiSuhuSedang(){

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

void fuzzifikasiSuhuPanas(){

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

  // if x >= B && x <= C
  else if (suhu >= fuzzyPanas[1] && suhu <= fuzzyPanas[2])
  {
    return 1;
  }

  // if x >= D
  else if (suhu > fuzzyPanas[3])
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

  jika nilai input suhu lebih dari atau sama dengan nilai fuzzyPanas[1] = 32 
  dan nilai suhu kurang dari atau sama dengan nilai fuzzyPanas [2] = 40
  maka nilai keanggotaan fuzzyPanas = 1

  jika nilai input suhu lebih dari nilai fuzzyPanas[3] = 40
  maka nilai keanggotaan fuzzyPanas = 1
  */
}

void fuzzyfikasiPhRendah(){

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