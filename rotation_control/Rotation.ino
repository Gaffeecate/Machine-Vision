#include <Servo.h>

Servo myservo;
int servoPin = 9; // 서보 모터 연결 핀

void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
  Serial.println("0~180까지 입력:");
}

void loop() {
  if (Serial.available() > 0) {
    int angle = Serial.parseInt();
    
    if (angle >= 0 && angle <= 180) {
      myservo.write(angle);
      Serial.print("Servo rotate to ");
      Serial.print(angle);
      Serial.println(" degrees");
    } else {
      Serial.println("0~180까지만 입력가능");
    }
    
    // 입력 버퍼 비우기
    while (Serial.available() > 0) {
      Serial.read();
    }
    
    Serial.println("0~180까지 입력:");
  }
}