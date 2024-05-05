#include "ACS712.h"
#include <LiquidCrystal_I2C.h>
//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps

//ACS712  ACS(A0, 5.0, 1023, 100);
ACS712  ACS(34, 3.3, 4095, 100);

int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

float Sensibilidad=0.100; //sensibilidad en V/A para nuestro sensor
float offset=0.100; // Equivale a la amplitud del ruido

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
}


void loop() {
  //----------------------------------------------
  float average = 0;
  for (int i = 0; i < 50; i++) {
    //average += ACS.mA_AC_sampling();
    average += ACS.mA_AC();
  }
  //float mA = (average / 50.0);
  float mA = (average / 50.0)-23;

  if(mA<0) mA=0;

  Serial.print("  mA: ");
  Serial.println(mA);

  //------------------------------------------------
  
  float Ip=mA / 1000 ;//obtenemos la corriente pico
  float Irms=Ip*0.707; //Intensidad RMS = Ipico/(2^1/2)
  float P=Irms*115.0; // P=IV watts
  
  Serial.print("A, Potencia: ");
  Serial.print(P,3);  
  Serial.println("W");
  
  //------------------------------------------------
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("Corr. ");
  lcd.print(mA);
  lcd.print(" mA");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("Po.   ");
  lcd.print(P);
  lcd.print(" Wa");
  delay(1000);
 //delay(16000);
}
