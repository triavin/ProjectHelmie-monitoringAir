#include <math.h>
float A, B;
int sel_;
float drajatKeanggotaanLambat;                              // variabel drajat keanggotaan nilai output lambat
float drajatKeanggotaanSedang1, drajatKeanggotaanSedang2;   // variabel drajat keanggotaan nilai output sedang
float drajatKeanggotaanCepat;                               // variabel drajat keanggotaan nilai output cepat
float L1, L2, L3, L4, L5, L6, L7;
float M1, M2, M3, M4, M5, M6, M7;
float fudeket[4] = {0, 0, 10, 100};     // nilai keanggotaan input dekat
float fulumayan[3] = {50, 150, 250};    // nilai keanggotaan input lumayang
float fujauh[4] = {200, 290, 300, 300}; // nilai keanggotaan input jauh
float fylambat[3] = {0, 0, 100};        // nilai keanggotaan output lambat
float fysedang[3] = {20, 127.5, 235};   // nilai keanggotaan output sedang
float fycepat[3] = {155, 255, 255};     // nilai keanggotaan output cepat
float inputf, outputf;

// fungsi fuzzyfikasi nilai input untuk nilai keanggotaan dekat

float FuzzyfikasiInputDekat()
{
    // jika nilai input kurang dari batas bawah variabel dekat
    // maka akan langsung mengeluaran nilai 1 (true)
    
    if (inputf < fudeket[2])
    {
        return 1;
    }

    // jika nilai input lebih besar atau sama dengan batas bawah 
    // tapi tidak lebih besar atau sama dengan dari batas atas variabel dekat
    // rumus [ (D - X) / (D - C)]
    // *note : X = Input
    //         C = Nilai sebelum batas atas pada variabel (array) dekat = dekat[last - 1]
    //         D = Nilai batas atas variabel (array) dekat atau nilai akhir pada array dekat = dekat[last]
    //
    // * rumus ini jika dibuat kedalam bentuk grafik akan membentuk garis diagonal menurun

    else if (inputf >= fudeket[2] && inputf <= fudeket[3])
    {
        return (fudeket[3] - inputf) / (fudeket[3] - fudeket[2]);
    }

    // jika nilai input lebih besar dari nilai batas atas variabel dekat
    // maka akan langsung mengeluarkan nilai 0 (false)
    
    else if (inputf > fudeket[3])
    {
        return 0;
    }
}

// fungsi fuzzyfikasi nilai input untuk nilai keanggotaan lumayan

float FuzzyfikasiInputLumayan()
{
    // jika input kurang dari nilai batas bawah variable lumayan
    // maka akan langsung mengeluarkan nilai 0 (false)
    
    if (inputf < fulumayan[0])
    {
        return 0;
    }

    // jika input lebih dari atau sama dengan nilai batas bawah variabel lumayan 
    // dan kurang dari nilai kedua pada (array) variabel lumayan
    // maka akan menggunakan rumus [ (X - A) / (B - A)]
    // * note : X = nilai input
    //          A = Batas bawah / nilai pertama pada variabel (array) lumayan = lumayan[0]
    //          B = Nilai kedua pada variabel (array) lumayan = lumayan[1]
    //
    // * jika rumus ini dibuat kedalam bentuk grafik akan membentuk garis diagonal menanjak

    else if (inputf >= fulumayan[0] && inputf <= fulumayan[1])
    {
        return (inputf - fulumayan[0]) / (fulumayan[1] - fulumayan[0]);
    }

    // jika input lebih dari atau sama dengan nilai kedua variabel (array) lumayan
    // dan lebih kecil atau sama dengan nilai ketiga variabel (array) lumayan 
    // "nilai sebelum nilai terakhir pada variabel lumayan / lumayan[last -1]"
    // maka menggunakan rumus [ (C - X) / (C - B)]
    // * note : X = nilai input
    //          B = Nilai kedua pada variabel (array) lumayan = lumayan[1]
    //          C = Batas atas / nilai terakhir pada variabel (array) lumayan = lumayan[last]
    //
    // * jika rumus ini dibuat kedalam bentuk grafik akan membentuk garis diagonal menurun
    
    else if (inputf >= fulumayan[1] && inputf <= fulumayan[2])
    {
        return (fulumayan[2] - inputf) / (fulumayan[2] - fulumayan[1]);
    }
    
    // jika input lebih dari nilai batas atas variabel (array) lumayan
    // maka akan langsung mengembalikan nilai 0 (false)

    else if (inputf > fulumayan[2])
    {
        return 0;
    }

    // *note : penerapan fuzzyfikasi pada nilai keanggotaan lumayan akan membentuk grafik segitiga
    //         grafik segitiga ini terbentuk karna variabel (array) lumayan hanya memiliki 3 nilai
    //         untuk membuat grafik dengan bentuk jajar genjang maka tambahkan 1 nilai kedalam variabel (array) lumayan 
    //         hingga variabel (array) lumayan memiliki 4 nilai di dalamnya
    //         
    //         kemudian tambahkan baris code untuk kondisi diantara isi array ke dua dan 3 seperti dibawah ini :
    //         
    //            else if (inputf >= fulumayan[2] && inputf <= fulumayan[3])
    //            {
    //                return 1;
    //            }
    //         
    //         atau ubah isi function menjadi seperti dibawah ini:
    // 
    //            if (inputf < fulumayan[0])
    //            {
    //                return 0;
    //            }
    //
    //            else if (inputf >= fulumayan[0] && inputf <= fulumayan[1])
    //            {
    //                return (inputf - fulumayan[0]) / (fulumayan[1] - fulumayan[0]);
    //            }
    //            
    //            else if (inputf >= fulumayan[2] && inputf <= fulumayan[3])
    //            {
    //                return 1;
    //            }
    //
    //            else if (inputf >= fulumayan[3] && inputf <= fulumayan[4])
    //            {
    //                return (fulumayan[4] - inputf) / (fulumayan[4] - fulumayan[3]);
    //            }
    //
    //            else if (inputf > fulumayan[2])
    //            {
    //                return 0;
    //            }

}

// fungsi fuzzyfikasi nilai input untuk nilai keanggotaan jauh

float FuzzyfikasiInputJauh()
{
    // jika input bernilai lebih rendah dari nilai batas bawah variabel (array) jauh
    // maka akan langsung mengembakikan nilai 0 (false)
    
    if (inputf < fujauh[0])
    {
        return 0;
    }

    // jika nilai lebih besar atau sama dengan nilai batas bawah variabel (array) jauh
    // dan kurang dari atau sama dengan nilai kedua pada variable (array) jauh
    // maka akan menggunakan rumus [ (X - A) / (B - A)]
    // * note : X = nilai input
    //          A = Batas bawah / nilai pertama pada variabel (array) lumayan = lumayan[0]
    //          B = Nilai kedua pada variabel (array) lumayan = lumayan[1]
    //
    // * rumus ini jika dibuat kedalam bentuk grafik akan membentuk garis diagonal menanjak

    else if (inputf >= fujauh[0] && inputf <= fujauh[1])
    {
        return (inputf - fujauh[0]) / (fujauh[1] - fujauh[0]);
    }

    // jika nilai input lebih besar dari nilai kedua pada variable (array) jauh
    // maka akan langsung mengembalikan nilai 1 (true)

    else if (inputf > fujauh[1])
    {
        return 1;
    }
}

// fuzzifikasi nilai keanggotaan output dekat

float FoN()
{
    if (outputf < fylambat[1])
    {
        return 1;
    }
    else if (outputf >= fylambat[1] && outputf <= fylambat[2])
    {
        return (fylambat[2] - outputf) / (fylambat[2] - fylambat[1]);
    }
    else if (outputf > fylambat[2])
    {
        return 0;
    }
}
float FoZ()
{
    if (outputf < fysedang[0])
    {
        return 0;
    }
    else if (outputf >= fysedang[0] && outputf <= fysedang[1])
    {
        return (outputf - fysedang[0]) / (fysedang[1] - fysedang[0]);
    }
    else if (outputf >= fysedang[1] && outputf <= fysedang[2])
    {
        return (fysedang[2] - outputf) / (fysedang[2] - fysedang[1]);
    }
    else if (outputf > fysedang[2])
    {
        return 0;
    }
}
float FoP()
{
    if (outputf < fycepat[0])
    {
        return 0;
    }
    else if (outputf >= fycepat[0] && outputf <= fycepat[1])
    {
        return (outputf - fycepat[0]) / (fycepat[1] - fycepat[0]);
    }
    else if (outputf > fycepat[1])
    {
        return 1;
    }
}

void implikasi()
{
    // sesuai dengan rule
    //  if deket then lambat

    drajatKeanggotaanLambat = fylambat[2] - (FuzzyfikasiInputDekat() * (fylambat[2] - fylambat[1]));
    
    // if lumayan then sedang
    
    drajatKeanggotaanSedang1 = fysedang[0] + (FuzzyfikasiInputLumayan() * (fysedang[1] - fysedang[0]));
    drajatKeanggotaanSedang2 = fysedang[3] - (FuzzyfikasiInputLumayan() * (fysedang[2] - fysedang[1]));
    
    // if jauh then cepat
    
    drajatKeanggotaanCepat = fycepat[0] + (FuzzyfikasiInputJauh() * (fycepat[1] - fycepat[0]));

    // code diatas merupakan rumus untuk nilai keanggotaan output
    // dengan rumus sebagai berikut :
    // keanggotaan lambat           = (C - X) / (C - B)
    // keanggotaan sedang pertama   = (X - A) / (B - A)
    // keanggotaan sedang kedua     = (C - X) / (C - B)
    // keanggotaan cepat            = (X - A) / (B - A)
    //
    // penulisan code juga bisa ditulis seperti di bawah ini
    //
    // drajatKeanggotaanLambat = ((fylambat[2] - FuzzyfikasiInputDekat()) / (fylambat[2] - fylambat[1]));
    //
    // drajatKeanggotaanSedang1 = ((FuzzyfikasiInputLumayan() - fysedang[0]) / (fysedang[1] - fysedang[0]));
    // drajatKeanggotaanSedang2 = ((fysedang[2] - FuzzyfikasiInputLumayan()) / (fysedang[2] - fysedang[1]));
    //
    // drajatKeanggotaanCepat = ((FuzzyfikasiInputJauh() - fycepat[0]) / (fycepat[1] - fycepat[0]));
}


void luas_deffuzzy()
{
    implikasi();
    L1 = ((fylambat[2] - drajatKeanggotaanLambat) * FuzzyfikasiInputDekat()) / 2;           //= 15.432222
    L2 = (drajatKeanggotaanLambat - fylambat[0]) * FuzzyfikasiInputDekat();                 // = 24.69155
    L3 = ((drajatKeanggotaanSedang1 - fysedang[0]) * FuzzyfikasiInputLumayan()) / 2;        // = 0
    L4 = ((fysedang[2] - drajatKeanggotaanSedang2) * FuzzyfikasiInputLumayan()) / 2;        // = 0
    L5 = (drajatKeanggotaanSedang2 - drajatKeanggotaanSedang1) * FuzzyfikasiInputLumayan(); // = 0
    L6 = ((drajatKeanggotaanCepat - fycepat[0]) * FuzzyfikasiInputJauh()) / 2;              // = 0
    L7 = (fycepat[2] - drajatKeanggotaanCepat) * FuzzyfikasiInputJauh();                    // = 0

    /* 
    Variabel L merupakan Luas dari nilai keanggotaan yang didapat
    */
}

float f(float x)
{
    if (B > 0 && sel_ == 0)
    {
        return ((x - A) / B) * x;
    }
    else if (B > 0 && sel_ == 1)
    {
        return ((A - x) / B) * x;
    }
    else
    {
        return A * x;
    }
}

/*Function deFuzzyfikasiInputDekatition to perform integration by Simpson's 1/3rd Rule */
float simpsons(float f(float x), float a, float b, float n)
{
    float h, integral, x, sum = 0;
    int i;
    h = fabs(b - a) / n;
    for (i = 1; i < n; i++)
    {
        x = a + i * h;
        if (i % 2 == 0)
        {
            sum = sum + 2 * f(x);
        }
        else
        {
            sum = sum + 4 * f(x);
        }
    }
    integral = (h / 3) * (f(a) + f(b) + sum);
    return integral;
}
float fx(float limd, float limu, float a, float b, int sel)
{
    int n, i = 2;
    float h, x, integral, eps = 0.1, integral_new;
    A = a;
    B = b;
    sel_ = sel;
    integral_new = simpsons(f, limd, limu, i);
    do
    {
        integral = integral_new;
        i = i + 2;
        integral_new = simpsons(f, limd, limu, i);
    } while (fabs(integral_new - integral) >= eps);
    /*Print the answer */
    return integral_new;
}
/*
  (fylambat[2]-pwm)/fylambat[2]-fylambat[0] untuk drajatKeanggotaanLambat <= pwm <= 100
  FuzzyfikasiInputDekat() untuk pwm < drajatKeanggotaanLambat
  (pwm-20)/127.5-20 untuk 20 <= pwm <= drajatKeanggotaanSedang1
  (235-pwm)/235-1275 untuk drajatKeanggotaanSedang2 <= pwm <= 235
  0 untuk drajatKeanggotaanSedang1 < pwm > drajatKeanggotaanSedang2
  (pwm-155)/255-155 untuk 155 <= pwm <= drajatKeanggotaanCepat
  0 untuk pwm > drajatKeanggotaanCepat
*/
void moment()
{
    luas_deffuzzy();
    // M1 = ∫ ((100-x)/100)x dx ==================> limd drajatKeanggotaanLambat dan limup 100
    M1 = fx(drajatKeanggotaanLambat, fylambat[2], fylambat[2], (fylambat[2] - fylambat[0]), 1);
    // M2 = ∫ 0.555556x dx ==================> limd 0 dan limup drajatKeanggotaanLambat
    M2 = fx(fylambat[0], drajatKeanggotaanLambat, FuzzyfikasiInputDekat(), 0, 0);
    // M3 = ∫ ((x-20)/107.5)x dx ==================> limd 20 dan limup drajatKeanggotaanSedang1
    M3 = fx(fysedang[0], drajatKeanggotaanSedang1, fysedang[0], (fysedang[1] - fysedang[0]), 0);
    // M4 = ∫ ((235-x)/107.5)x dx ==================> limd drajatKeanggotaanSedang2 dan limup 235
    M4 = fx(drajatKeanggotaanSedang2, fysedang[2], fysedang[2], (fysedang[2] - fysedang[1]), 1);
    // M5 = ∫ 0 dx ==================> limd drajatKeanggotaanSedang1 dan limup drajatKeanggotaanSedang2
    M5 = fx(drajatKeanggotaanSedang1, drajatKeanggotaanSedang2, FuzzyfikasiInputLumayan(), 0, 0);
    // M6 = ∫ ((x-155)/100)x dx ==================> limd 155 dan limup drajatKeanggotaanCepat
    M6 = fx(fycepat[0], drajatKeanggotaanCepat, fycepat[0], (fycepat[2] - fycepat[0]), 0);
    // M7 = ∫ 0 dx ==================> limd drajatKeanggotaanCepat dan limup 255
    M7 = fx(drajatKeanggotaanCepat, fycepat[2], FuzzyfikasiInputJauh(), 0, 0);
}

float deffuzzyfikasi()
{
    moment();
    return (M1 + M2 + M3 + M4 + M5 + M6 + M7) / (L1 + L2 + L3 + L4 + L5 + L6 + L7);
}

void setup()
{
    Serial.begin(9600);
    Serial.println("---Program Fuzzy anakkendali.co---");
    Serial.println("Masukan Input Jarak 0 - 300 :");
}
void loop()
{
    if (Serial.available())
    {
        int a = Serial.parseInt();
        if (a >= 0)
        {
            inputf = a;
            Serial.print("Input jarak :");
            Serial.print(inputf);
            Serial.println(" CM");
            Serial.print("Output Deffuzyfikasi Mamdani :");
            Serial.println(deffuzzyfikasi());
        }
    }
}