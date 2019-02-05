#include<LiquidCrystal.h>
LiquidCrystal lcd(2,4,6,8,10,12);
int c=0,a=0,i=0,value=40,b=0,g=0;

void setup()
{
  Serial.begin(9600);
    lcd.begin(16,2);
  pinMode(9,OUTPUT);  // analog led output
  pinMode(11,INPUT);
  pinMode(13,INPUT);
  pinMode(7,OUTPUT);  // green signal when MOTOR is ON 
  pinMode(5,OUTPUT);  // red signal for DANGER
  pinMode(A4,OUTPUT);  // blue signal when MOTOR is OFF
  pinMode(A0,OUTPUT); // DC MOTOR OUTPUT
  pinMode(A1,OUTPUT); // ALARM
  pinMode(A2,INPUT);  // DC MOTOR INPUT from D8(APP)
  pinMode(A3,INPUT);  // ANALOG LED INPUT from D7(APP)
  pinMode(3,INPUT);  // WHEN TANK IS FULL!!
   
   lcd.print("MEMBERS IN HOUSE");
   lcd.setCursor(0,1); 
   lcd.print("ENTRY STARTS");  
}

void loop()
{
  int N,M,X,Y,Z;
  if(c>0)
  M=digitalRead(11);      //EXIT GATE
  N=digitalRead(13);      //ENTRY GATE
  Z=digitalRead(3);       // TANK IS FULL
  X=analogRead(A2);      //DC MOTOR INPUT
  Y=analogRead(A3);      //ANALOG LED INPUT
  
  if(X>750)
  {
    digitalWrite(A0,HIGH);
    Serial.println("HELLO11");
    Serial.println(A0);
      
    if(g!=1)
    {
      digitalWrite(5,0);
      digitalWrite(7,1);
      digitalWrite(A4,0);
    }
     if(Z==1)
       {                                    // Raise the alarm when tank is full
        digitalWrite(A1,HIGH);
        digitalWrite(7,0);
        digitalWrite(5,1);
        digitalWrite(A4,0);
        g=1;
       }
      if (Z==0)                     // again if tank is not full
       {
        digitalWrite(A1,LOW);
        g=0;   
        }
  }
  else if(X <=750)
  {
    
    digitalWrite(A1,LOW);
    digitalWrite(A0,LOW);
    digitalWrite(A4,1);
    digitalWrite(7,0);
    digitalWrite(5,0);
    g=0;
  }
  
  if(N==1 && a!=1 )
 {c++;
   i=i+value;
   lcd.clear();
   lcd.print("ONE PERSON ENTERS IN HOUSE");
   delay(1000);
   lcd.clear();
   lcd.print("MEMBERS IN HOUSE");
   lcd.setCursor(0,1); 
   lcd.print(c); 
   if(i>=0 && Y>750)
     analogWrite(9,i);
 a=1;   
 }
 
   if(N==0)
  {
    a=0;
  }
  if(M==1 && b!=1)
  { c--;
    i=i-value;
    lcd.clear();
    lcd.print("ONE PERSON LEAVES THE HOUSE");
    delay(1000);
    lcd.clear();
    lcd.print("MEMBERS IN HOUSE");
    lcd.setCursor(0,1); 
    lcd.print(c); 
   if(i>=0 && Y>=750)
    analogWrite(9,i);
   b=1;
   
   
  }
   if(M==0)
  {
    b=0;
  }
 if(Y<750)                  // light OFF from APP
  analogWrite(9,LOW);
delay(500);
}

