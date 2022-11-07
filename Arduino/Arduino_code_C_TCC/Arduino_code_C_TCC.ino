#include <Servo.h>
#include <HCSR04.h>
#include <math.h>

#define SERVO 12 // Porta Digital 7 PWM
#define p_trigger 8
#define p_echo 10

Servo s; // Variável Servo
int pos; // Posição Servo

int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
float Speed = 0.224;

int matriz[24][24], sensorPos[2], seeing[2];
int opening = 0;
int steps = 0;

UltraSonicDistanceSensor distanceSensor(p_trigger, p_echo);
float dist_cm, dist_M;

void setup ()
{
  s.attach(SERVO);
  Serial.begin(9600);
  s.write(0); // Inicia motor posição zero
  sensorPos[0] = 8;
  sensorPos[1] = 8;

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void readSensor(int ang){
  float degree = pos + 90;
  delay(10);
  float hipotenusa = distanceSensor.measureDistanceCm();
  delay(30);
  float hipotenusa2 = distanceSensor.measureDistanceCm();

  hipotenusa = (hipotenusa + hipotenusa2) / 2;
  
  Serial.print(hipotenusa);
  Serial.print(";");

  if((ang <= 100) && (ang >= 80)){
    if((hipotenusa >= 15) || (hipotenusa < 0)){
      if(opening != -1){
        opening ++;
      }
    } else {
      opening = -1;
    }
  }

  if(pos == 0){
    if(opening == 21){
      Serial.print('+');
      steps ++;
    } else {
      steps = 4;
    }
  }
}

void loop()
{
  if(steps < 3){
    opening = 0;
    for(pos = 180; pos >= 0; pos--)
    {
      s.write(pos);
      readSensor(180 - pos);
    }
    delay(1000);
    if(opening > 0){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

      delay(Speed * 1000);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
   } else {
     steps = 0;
     Serial.println(' ');
     Serial.println(' ');
     Serial.println(' ');
   }

  

  delay(100);
}
