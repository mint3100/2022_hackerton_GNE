
//created By mint2792@mintserver.kr
//2022/10/16 (SUN)

#include <DHT11.h>   
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int pin= 3;  //DHT11 센서         
int speaker = 6; //부저
int led = 13;

DHT11 dht11(pin); 
LiquidCrystal_I2C lcd(0x27,16,2);
     
void setup()  {
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  //시작, 디버그용 시리얼
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Loading!");
  lcd.setCursor(3,1);
  lcd.print("BY WTTLAM");
  tone(speaker, 392);
  delay(60);
  noTone(speaker);
  delay(1000);
  lcd.clear();
  digitalWrite(led,LOW);
}
 
void loop()  {

  int err;
  int level = analogRead(A0);
  int level2 = digitalRead(4);
  float temp, humi;
 
  if((err=dht11.read(humi, temp))==0) {
    //그냥 정의해줌, 실제 코드는 아랫쪽에 몰려있음
    int t = temp;
    int h = humi; 

//analogSignal 오른쪽 하단 15,1 좌표에 출력
  }
  else  {
    lcd.println();
    lcd.print("Error No :");
    lcd.print(err);
    Serial.print("Error No :");
    Serial.print(err);
   //위 코드는 에러 났을때 에러출력 코드    
  }
//아래 코드는 analogSignal이 5 초과, digitalSignal이 참(1)이 되었을때 부저가 울리는 조건문
  if (level > 3 and level2 == 1) {

    digitalWrite(led,HIGH);
    tone(speaker, 392);
    delay(50);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Detected!");
    Serial.print("Detected!");
    Serial.println();
  } else {
    int t = temp;
    int h = humi; 
    noTone(speaker);
    digitalWrite(led,LOW);
    
    //아래 코드는 온도, 습도를 각각 I2C LCD의 0,0 좌표, 0,1 좌표부터 출력하는 코드
    lcd.setCursor(0,0);
    lcd.print("temp:");
    lcd.print(t);
    lcd.print(" C deg");
    lcd.setCursor(0,1);
    lcd.print("humidity:");
    lcd.print(h);
    lcd.print("%");
    lcd.setCursor(15,1);
    lcd.print(level);

    //아래 코드는 시리얼 모니터로 온도, 습도 출력
    Serial.print(t);
    Serial.print("/");
    Serial.print(h);
    Serial.println();    
  }
  delay(2000);
}
