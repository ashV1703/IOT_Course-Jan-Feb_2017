//Enable-A HIGH
//Connect VCC, GND
//A1,A2 connected to digital pins of Arduino, decide direction
//+-V connected to battery to power motor
//MA 1,2 connected to motor
#include<SoftwareSerial.h>
#include <LiquidCrystal.h>
char junk;
String inputString="";
//SoftwareSerial mySerial(0,1);
SoftwareSerial buleSerial(6,1);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int read_count=0;
int j=0,k=0; // Variables to iterate in for loops
char data_temp, RFID_data[12];
char Saved_Tags[1][12]={
  '4','5','0','0','4','1','1','6','6','9','7','B'};
boolean tag_check,tag_status,entry_control;
boolean flag=false;
boolean granted=false;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  // mySerial.begin(9600);
  buleSerial.begin(9600);
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(10,HIGH);
}

void loop() {
  if(buleSerial.available()>0){
    while(buleSerial.available())
    {
      char inChar = (char)buleSerial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    Serial.print(inputString);
    while (buleSerial.available() > 0)  
    { 
      junk = buleSerial.read() ; 
    }    // clear the serial buffer
    Serial.println(inputString);
    if(inputString == "1234"){         //in case of 'a' turn the LED on
      flag=!flag;
            lcd.setCursor(0, 0);
      lcd.print("Passkey accepted");
      if(flag)
      {
        Unlock(); 
        Serial.println("Door unlocked");
        lcd.setCursor(0, 1);
        lcd.print("Door unlocked");
        delay(2000);
        Stop();
      }
      else
      {
        Lock();
        Serial.println("Door locked");
        lcd.setCursor(0, 1);
        lcd.print("Door locked");
        delay(2000);
        Stop();
      } 
    }
    else {   //incase of 'b' turn the LED off
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Wrong passkey");
    }
    inputString = "";
  }//lcd.clear();
  RecieveData();
  CheckData();


  // put your main code here, to run repeatedly:
  if(entry_control==true)
  {
    AccessCheck();
    //Unlock();
    //  digitalWrite(13,HIGH);
    //  delay(2000);
    // Stop();
    // delay(2000);
    //Lock();
    //digitalWrite(13,LOW);
    //delay(2000);
    //Stop();
    if(granted)
    {
      flag=!flag;
      if(flag)
      {
        Unlock(); 
        Serial.println("Door unlocked");
        lcd.setCursor(0, 1);
        lcd.print("Door unlocked");
        delay(2000);
        Stop();
      }
      else
      {
        Lock();
        Serial.println("Door locked");
        lcd.setCursor(0, 1);
        lcd.print("Door locked");
        delay(2000);
        Stop();
      }
    } 
  }
}
void Stop()
{
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
}

void Lock()
{
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
}
void Unlock()
{
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
}
void RecieveData()
{
  if(Serial.available()>0)
  {
    data_temp=Serial.read();
    RFID_data[read_count]=data_temp;
    read_count++;
  }
}

void CheckData()
{
  if(read_count==12)
  {
    entry_control=true;  
    for(k=0;k<1;k++)
    {
      for(j=0;j<12;j++)
      {
        if(Saved_Tags[k][j]==RFID_data[j])
        {
          tag_check=true;
        }
        else
        {
          tag_check=false;
          break;
        }
      }
      if(tag_check==true)
      {
        tag_status=true;
      }
    }
    read_count=0;
  }
}

void AccessCheck()
{
  if(entry_control==true)
  {
    if(tag_status==true)
    {
      lcd.clear();
      Serial.println("Access Granted");
      lcd.setCursor(0, 0);
      lcd.print("Access Granted");
      granted=true;
    }
    else
    {
      Serial.println("Access Denied");
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.print("Access Denied");
      granted=false;
    }
    entry_control=false;
    tag_status=false;
  }
}


