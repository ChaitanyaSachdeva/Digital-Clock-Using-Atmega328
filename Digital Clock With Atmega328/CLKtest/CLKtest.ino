#include "LiquidCrystal.h"

// This defines the LCD wiring to the DIGITALpins
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Digital LCD Constrast setting
int cs=9;// pin 9 for contrast PWM
const int contrast = 100;// default contrast

// initial Time display is 12:59:45 PM
int h=12;
int m=59;
int s=45;
int flag=1; //PM

// Time Set Buttons
int button1;
int button2;

// Pins definition for Time Set Buttons
int hs=0;// pin 0 for Hours Setting
int ms=1;// pin 1 for Minutes Setting


int bl=10; // Backlight pin
const int backlight=120; 

// For accurate Time reading, use Arduino Real Time Clock and not just delay()
static uint32_t last_time, now = 0; // RTC


void setup()
{
  lcd.begin(16,2);
  pinMode(hs,INPUT_PULLUP);// avoid external Pullup resistors for Button 1
  pinMode(ms,INPUT_PULLUP);// and Button 2
  analogWrite(cs,contrast);// Adjust Contrast VO   
  analogWrite(bl,backlight);// Turn on Backlight 
  now=millis(); // read RTC initial value  
}


void loop()
{ 
  s=now/1000;
  lcd.begin(16,2);

 lcd.setCursor(0,0);
 lcd.print("Time ");
 if(h<10)
 lcd.print("0");
 lcd.print(h);
 lcd.print(":");
 if(m<10)
 lcd.print("0");
 lcd.print(m);
 lcd.print(":");
 if(s<10)
 lcd.print("0");
 lcd.print(s);

 if(flag==0) lcd.print(" AM");
 if(flag==1) lcd.print(" PM");
 
 lcd.setCursor(0,1);
 lcd.print("Digital clock");

for ( int i=0 ;i<5 ;i++)//5 time 200ms loop, for faster Button response
{

  while ((now-last_time)<200) //delay200ms
  { 
    now=millis();
  }
 // inner 200ms loop
 last_time=now; }// prepare for next loop 

 // read Setting Buttons
 button1=digitalRead(hs);
 button2=digitalRead(ms);

/* ---- manage seconds, minutes, hours am/pm overflow ----*/
 if(s==60){
  s=0;
  m=m+1;
 }
 if(m==60)
 {
  m=0;
  h=h+1;
 }
 if(h==13)
 {
  h=1;
  flag=flag+1;
  if(flag==2)flag=0;
 }


 if((button1==0)|(button2==0))// Update display if time set button pressed
 {
  lcd.setCursor(0,0);
  lcd.print("Time ");
  if(h<10)lcd.print("0");// always 2 digits
  lcd.print(h);
  lcd.print(":");
  if(m<10)lcd.print("0");
  lcd.print(m);
  lcd.print(":");
  if(s<10)lcd.print("0");
  lcd.print(s);

  if(flag==0) lcd.print(" AM");
  if(flag==1) lcd.print(" PM");
 
  lcd.setCursor(0,1);
  lcd.print("Digital clock");
 } delay(1000);
} // end if else
