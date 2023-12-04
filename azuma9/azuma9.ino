#include<SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

#include <IRremote.h>
#include<Servo.h>           //サーボをインクルード
#define SERVO1 5
#include <LiquidCrystal_I2C.h>

Servo servo1;  //サーボのインスタンスを宣言

SoftwareSerial mySerial(10, 11); //mp3モジュールのライブラリをインクルード RX,TX

const int ReceiverPin = 12;  // 赤外線受信モジュール接続ピンをD2に
IRrecv irrecv(ReceiverPin);  // IR受信オブジェクトの生成(使用ピンを指定)
decode_results results; //赤外線送信用オブジェクト設定

long randNumber;

// RGBLEDlight
int led_pins[]={3,4,6};

// display
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {
  Serial.begin(9600);  //communication speed is 9600
  irrecv.enableIRIn(); // 受信を開始する
  servo1.attach(SERVO1); //

  // mp3再生
  mySerial.begin(9600);
  mp3_set_serial(mySerial);
  mp3_set_volume(25);

  lcd.init();                  //initialize the lcd 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Please beat this");
  lcd.setCursor(1,1);
  lcd.print("target coolly!");

  //random function
  randomSeed(analogRead(1));

  //RGB_LED_Light
  int i;

  lcd.init(); 

  for(i=0;i<3;i++){
    pinMode(led_pins[i],OUTPUT);
    }

  
}

int j=0;
int k=0;

void loop() {
  
  
  if (irrecv.decode(&results)) {
    if (results.value == 0x1FE20DF) {
      Serial.println(results.value, HEX);
      servo1.write(150);

      j = j + 1;

      // LED light up  == red
      digitalWrite(led_pins[1],LOW);
      digitalWrite(led_pins[0],HIGH);
      digitalWrite(led_pins[2],HIGH);


      // display
      //lcd.init();                  //initialize the lcd 
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("IPPON!IPPON!IPPON!");
      lcd.setCursor(0,1);
      lcd.print("IPPON!IPPON!IPPON!");

      randNumber = random(100);
      
      randNumber = random(1, 10); // 1から2の乱数を生成
      // mp3再生
      delay(250);
      mp3_play(randNumber);
      //Serial.println(randNumber);
      
      delay(1500);
    }
      
  if (results.value == 0x1FE609F) {
      Serial.println(results.value, HEX);
      servo1.write(150);

      k = k + 1;

      // LED light up  == red
      digitalWrite(led_pins[2],LOW);
      digitalWrite(led_pins[0],HIGH);
      digitalWrite(led_pins[1],HIGH);


      // display
      //lcd.init();                  //initialize the lcd 
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("IPPON!IPPON!IPPON!");
      lcd.setCursor(0,1);
      lcd.print("IPPON!IPPON!IPPON!");

      randNumber = random(100);
      
      randNumber = random(1, 10); // 1から10の乱数を生成
      // mp3再生
      delay(250);
      mp3_play(randNumber);
      //Serial.println(randNumber);
      
      delay(1500);
    }

    irrecv.resume();


  }
  servo1.write(90);
  // led light yellow
  digitalWrite(led_pins[1],LOW);
  digitalWrite(led_pins[0],LOW);
  digitalWrite(led_pins[2],HIGH);
  lcd.init();                  //initialize the lcd 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Red:");
  lcd.setCursor(6,0);
  lcd.print(j);
  lcd.setCursor(8,0);
  lcd.print("POINT");
  lcd.setCursor(0,1);
  lcd.print("Blue:");
  lcd.setCursor(6,1);
  lcd.print(k);
  lcd.setCursor(8,1);
  lcd.print("POINT");
  

}
