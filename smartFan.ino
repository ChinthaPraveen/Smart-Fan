#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define DHTPIN 10
#define DHTTYPE DHT11
#define trig_pin 8
#define echo_pin 9
DHT dht(DHTPIN,DHTTYPE);
Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);  
long duration;
long distance;
int spd=0;
void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(3000);
  lcd.backlight(); 
  lcd.init();
  dht.begin();
  pinMode(A0,INPUT);
  pinMode(5,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
  myservo.attach(7);
}
 
void lev(float a)
{
  if (a>=0 && a<50)
  {
     lcd.setCursor(0,1);
    lcd.print("Level-0         ");
    analogWrite(5,0);
    myservo.write(110);
  }
  else if (a>=50 && a<=120)
  {
     lcd.setCursor(0,1);
    lcd.print("Level-1         ");
     analogWrite(5,90);
  }
  else if (a>120 && a<=180)
  {
     lcd.setCursor(0,1);
    lcd.print("Level-2         ");
     analogWrite(5,100);
  }
  else if (a>=181 && a<=230)
  {
     lcd.setCursor(0,1);
    lcd.print("Level-3         ");
    analogWrite(5,110);
  }
  else if (a>=231 && a<=255)
  {
     lcd.setCursor(0,1);
    lcd.print("Level-4         ");
    analogWrite(5,130);
  }
}
void loop()
 {   
    int j=41,k=179;
    digitalWrite(trig_pin,LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin,LOW);
    duration = pulseIn(echo_pin,HIGH);
    distance = duration*0.034/2;
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    if(distance>=0 && distance<=15)
   {
        int val;
        int data;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.println("Regulator       ");
        val=analogRead(A0);
        delay(100);
        data=map(val,0,1023,0,255);
        Serial.println(data);
        lev(data);
        if(data>=50)
        {
           for(int i=140;i>=0;i--)
           {  
             if(i>=70 && i<=140)
             {
               myservo.write(i-30);
               delay(25);
             }
             else
             { 
               myservo.write(j);
               delay(25);
               j++;
             }
            }
            delay(50);
            for(int i=1;i<=140;i++)
            {  
              if(i>=1 && i<=70)
              {
                myservo.write(i+110);
                delay(25);
              }
              else 
              { 
                myservo.write(k);
                delay(25);
                k--;
              }
            }
        }
    }
    else if (distance>=16 && distance<=40)
    {
        float t=0;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.println("AutoMatic       ");
        t=dht.readTemperature();
        lcd.setCursor(0,1);
        lcd.print("Temperature:");
        lcd.print(t);
        lcd.println("°C");
        if(t>21 && t<=26)
        {
           analogWrite(5,90);
        }
        else if(t>26 && t<=27)
        {
           analogWrite(5,100);
        }
        else if(t>27 && t<=28)
        {
           analogWrite(5,110); 
        }
        else if(t>28 && t<=29)
        {
           analogWrite(5,120); 
        }
        else if(t>29 && t<=30) 
        {
           analogWrite(5,130); 
        }
        else
        {
           analogWrite(5,140); 
        }
         for(int i=140;i>=1;i--)
        {  
           if(i>=70 && i<=140)
           {
            myservo.write(i-30);
            delay(25);
           }
           else 
           { 
            myservo.write(j);
            delay(25);
            j++;
           }
        }
        delay(25);
        for(int i=1;i<=140;i++)
        {  
           if(i>=1 && i<=70)
           {
            myservo.write(i+110);
            delay(25);
           }
           else
           { 
            myservo.write(k);
            delay(25);
            k--;
           }
        }
        
    }
    else 
   {        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("bluetooth:      ");
        if(Serial.available()>0)
        {
          spd=Serial.parseInt();
        }
        lev(spd);
        if (spd>=50)
        {
           for(int i=140;i>=0;i--)
           {  
             if(i>=70 && i<=140)
             {
              myservo.write(i-30);
              delay(25);
             }
             else
             { 
              myservo.write(j);
              delay(25);
              j++;
             }
           }
           delay(50); 
           for(int i=1;i<=140;i++)
           {  
             if(i>=1 && i<=70)
             {
               myservo.write(i+110);
               delay(25);
             }
             else
             { 
                myservo.write(k);
                delay(25);
                k--;
             }
           }
        }
    }
   
 }

