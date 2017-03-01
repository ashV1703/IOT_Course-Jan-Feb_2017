//Enable-A HIGH
//Connect VCC, GND
//A1,A2 connected to digital pins of Arduino, decide direction
//+-V connected to battery to power motor
//MA 1,2 connected to motor
#include<SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
int count =0;
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {
    '1','2','3', 'A'  }
  ,
  {
    '4','5','6', 'B'  }
  ,
  {
    '7','8','9', 'C'  }
  ,
  {
    '*','0','#', 'D'  }
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 
  14, 15, 16, 17 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 
  18, 19, 7, 10 }; 
String passkey="";
// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
const String password="1234";
char junk;
String inputString="";
//SoftwareSerial mySerial(0,1);
SoftwareSerial buleSerial(6,1);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int read_count=0;
int j=0,k=0; // Variables to iterate in for loops
char data_temp, RFID_data[12];
char keypad[4][4]={
  '1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
char Saved_Tags[1][12]={
  '4','5','0','0','4','1','1','6','6','9','7','B'};
boolean tag_check,tag_status,entry_control;
boolean flag=false;
boolean granted=false;
boolean interrupt = false;

void setup() {
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(10,OUTPUT);
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  // mySerial.begin(9600);
  buleSerial.begin(9600);
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}

void loop() {
  digitalWrite(13,HIGH);
  char key = kpd.getKey();
  if(key == '#') ///Means *
  {
    //check pass
    if(passkey==password)
    {
      vGrantAccess();
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      count =0;
      lcd.print("Wrong passkey");
      passkey = " ";
    }
    passkey = "";
  }
  else if(key!=NO_KEY)
  {
    passkey += key;
    count++;
    lcd.clear();
    for (int i=0; i<count; i++)
    {
      lcd.print('*');
    }
  }

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
    if(inputString == password){         //in case of 'a' turn the LED on
      vGrantAccess();
    }
    else {   //incase of 'b' turn the LED off
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Wrong passkey");
      count = 0;
      passkey = " ";
    }
    inputString = "";
  }//lcd.clear();
  RecieveData();
  CheckData();


  // put your main code here, to run repeatedly:
  if(entry_control==true)
  {
    AccessCheck();

    if(granted)
    {
      vGrantAccess();
    } 
  }
  //  }
  //  else
  //  {
  //    lcd.clear();
  //    lcd.print("Test");
  //  }
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
      count = 0;
      passkey = " ";
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
void vGrantAccess()
{
  passkey = " ";
  count =0;
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



