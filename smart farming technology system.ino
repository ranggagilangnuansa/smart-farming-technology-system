
/*

  AT+CWJAP="DR.IMAM SUPRAYOGI","354354313"
  +CIFSR:STAIP,"192.168.1.7"






*/


#include <SoftwareSerial.h>
#define DEBUG true

#include <Wire.h>
#include <virtuabotixRTC.h>
virtuabotixRTC myRTC(34, 36, 38); //CLK, DAT, RST
////////////////////////






int sensorPin1 = A0;
int sensorPin2 = A1;
int sensorPin3 = A2;

int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;







const int buttonPin1 = 24;
const int buttonPin2 = 26;
const int buttonPin3 = 28;
const int buttonPin4 = 30;


const int ledPin1 =  25;
const int ledPin2 =  27;
const int ledPin3 =  29;
const int ledPin4 =  31;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;




void setup ()
{
  Serial.begin(115200);
  Serial3.begin(115200);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);



  // Reset modul
  sendCommand("AT+RST\r\n", 2000, DEBUG);
  // Konfigurasikan sebagai Akses poin
  sendCommand("AT+CWMODE=3\r\n", 1000, DEBUG);
  // Sesuaikan dengan SSID dan Password
  sendCommand("AT+CWJAP=\"DR.IMAM SUPRAYOGI\",\"354354313\"\r\n", 10000, DEBUG);
  // Mendapatkan IP adress
  sendCommand("AT+CIFSR\r\n", 1000, DEBUG);
  // Konfigurasikan untuk multiple connection
  sendCommand("AT+CIPMUX=1\r\n", 1000, DEBUG);
  // Aktifkan server pada port 80
  sendCommand("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);
  Serial.println("Server sudah siap!");

  Wire.begin();

 //myRTC.setDS1302Time(00, 10, 11, 7, 9, 11, 2020);



  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);


  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);



}

void loop ()
{

  myRTC.updateTime();
  Serial.print("Tanggal / Waktu: ");
  Serial.print(myRTC.dayofmonth); //menampilkan tanggal
  Serial.print("/");
  Serial.print(myRTC.month); //menampilkan bulan
  Serial.print("/");
  Serial.print(myRTC.year); //menampilkan tahun
  Serial.print(" ");
  Serial.print(myRTC.hours); //menampilkan jam
  Serial.print(":");
  Serial.print(myRTC.minutes); //menampilkan menit
  Serial.print(":");
  Serial.println(myRTC.seconds); //menampilkan detik
  delay( 1000);
  // delay(2000);

  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);

  Serial.print("  sensor1= ");
  Serial.print(sensorValue1);
  Serial.print("  sensor2= ");
  Serial.print(sensorValue2);
  Serial.print("  sensor3= ");
  Serial.println(sensorValue3);


  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);

  // delay(2000);
  
    if (myRTC.hours == 11  && myRTC.minutes == 21 )
    {
     if (sensorValue1 > 700)
     {
       digitalWrite(ledPin1, HIGH);
        digitalWrite(9, LOW);
       digitalWrite(6, LOW);
       Serial.println("solenoid 1r aktif");
       delay (5000);
     }
     if (sensorValue2 > 700)
     {
       digitalWrite(ledPin2, HIGH);
        digitalWrite(9, LOW);
       digitalWrite(7, LOW);
       Serial.println("solenoid 2r aktif");
       delay (5000);
     }
     if (sensorValue3 > 700)
     {
       digitalWrite(ledPin3, HIGH);
        digitalWrite(9, LOW);
       digitalWrite(8, LOW);
       Serial.println("solenoid 3r aktif");
       delay (3000);
     }
     //////////////////////////////////////////////////////////
     if (sensorValue1 < 400)
     {
       digitalWrite(ledPin1, LOW);
         digitalWrite(9, HIGH);
       digitalWrite(6, HIGH);
       Serial.println("solenoid 1r mati");
     }
     if (sensorValue2 < 700)
     {
       digitalWrite(ledPin2, LOW);
         digitalWrite(9, HIGH);
       digitalWrite(7, HIGH);
       Serial.println("solenoid 2r mati");
     }
     if (sensorValue3 < 700)
     {
       digitalWrite(ledPin3, LOW);
         digitalWrite(9, HIGH);
       digitalWrite(8, HIGH);
       Serial.println("solenoid 3r mati");
     }
          digitalWrite(9, HIGH);
       digitalWrite(6, HIGH);
            digitalWrite(7, HIGH);
       digitalWrite(8, HIGH);
    }
  
  if (buttonState1 == LOW) //PUPUK
  {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(5, LOW);
     delay(2000);
    digitalWrite(6, LOW);
      delay(2000);
    digitalWrite(7, LOW);
      delay(2000);
    digitalWrite(8, LOW);
      delay(2000);
    Serial.println("PUPUK");
    delay(5000);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(ledPin1, LOW);
   
  }
  if (buttonState2 == LOW) //KERAN 1
  {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(9, LOW);
    delay(2000);
    digitalWrite(8, LOW);
    Serial.println("solenoid 2p aktif");
    delay(105000);
   // delay(5000);
    digitalWrite(ledPin2, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
  }
  if (buttonState3 == LOW)//KERAN 2
  {
    digitalWrite(ledPin3, HIGH);
    digitalWrite(9, LOW);
    delay(2000);
    digitalWrite(7, LOW);
    Serial.println("solenoid 3p aktif");
     delay(105000);
    digitalWrite(ledPin3, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(7, HIGH);
  }
  if (buttonState4 == LOW) //KERAN 3
  {
    digitalWrite(ledPin4, HIGH);
    digitalWrite(9, LOW);
    delay(2000);
    digitalWrite(6, LOW);
    Serial.println("solenoid 4p aktif");
   delay(105000);
    digitalWrite(ledPin4, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(6, HIGH);
  }

  if (Serial3.available())
  {

    if (Serial3.find("+IPD,")) {
      delay(1000);
      int connectionId = Serial3.read() - 48;
      Serial3.find("pin=");
      int pinNumber = (Serial3.read() - 48) * 10;
      pinNumber += (Serial3.read() - 48);

      int secondNumber = (Serial3.read() - 48);
      if (secondNumber >= 0 && secondNumber <= 9)
      {
        pinNumber *= 13;
        pinNumber += secondNumber;
      }
      pinMode(pinNumber, OUTPUT);
      digitalWrite(pinNumber, !digitalRead(pinNumber));

      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId;
      closeCommand += "\r\n";
      sendCommand(closeCommand, 1000, DEBUG);
    }
  }
}

String sendCommand(String command, const int timeout, boolean debug)
{
  String response = "";
  Serial3.print(command);
  long int time = millis();

  while ( (time + timeout) > millis())
  {
    while (Serial3.available())
    {
      char c = Serial3.read();
      response += c;
    }
  }

  if (debug) {
    Serial.print(response);
  }
  return response;
}
