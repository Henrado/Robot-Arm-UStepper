const float L1o = 40;
const float Zo = -77;
const float L_2 = 71.0;
const float Lo= 41;
const float Au = 180.0;
const float Al = 177.0;
const float pi = 3.141;
const int antStepp = 200;

#include <AccelStepper.h>
const int stepX = 2; //Steppermotor X
const int dirX  = 5;
AccelStepper stepperX(1, stepX, dirX);

const int stepY = 3; //Steppermotor Y
const int dirY  = 6;
AccelStepper stepperY(1, stepY, dirY);

const int stepZ = 4; //Steppermotor Z
const int dirZ  = 7;
AccelStepper stepperZ(1, stepZ, dirZ);

const int enPin = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  // Start the Serial monitor with speed of 9600 Bauds

  pinMode(enPin,OUTPUT); //For at stepperen skal fungere
  digitalWrite(enPin,LOW);

  stepperX.setMaxSpeed(100);
  stepperX.setAcceleration(100);
  stepperY.setMaxSpeed(100);
  stepperY.setAcceleration(100);
  stepperZ.setMaxSpeed(100);
  stepperZ.setAcceleration(100);

  Serial.println("Forste");
  arm(200, 0, 0);
  delay(10000);
  Serial.println("neste");
  arm(300, 0, 0);
  delay(10000);
  Serial.println("Forste");
  arm(200, 0, 0);
  
  //Serial.println("Neste");
  //arm(-100, 100, 0);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void arm(float x, float y, float z){
  float lengde = sqrt(x*x+y*y);
  /*if (lengde > 470-z*2 || lengde < 230-z*2){
    Serial.println("Ugyldig kordinat: 230 < " + (String)lengde + " < 470 og 0 < ");
    return;
  }*/
  if (z > 220 || z < 0){
    Serial.println("Ugyldig z-kordinat: " + (String)z);
    return;
  }
  if (lengde < 200 || lengde > 400){
    Serial.println("Ugyldig lengde: " + (String)lengde);
    return;
  }
  /*
  if (lengde > 470 || lengde < 230 || z > 220 || z < 0){
    Serial.println("Ugyldig kordinat: 230 < " + (String)lengde + " < 470 og 0 < " + (String)z + " 220");
    return;
  }*/
  
  float rot = atan2(y,x);
  x = x - cos(rot)*L1o;
  y = y - sin(rot)*L1o;
  z = z - Zo-L_2;

  float L1 = sqrt(x*x+y*y)-Lo;
  float L_2 = sqrt(L1*L1+z*z);

  float a = z/(L_2);
  float b = (L_2*L_2 + Al*Al - Au*Au)/(2*L_2*Al);
  float c = (Al*Al+Au*Au-L_2*L_2)/(2*Al*Au);

  float right = (atan2(a,sqrt(1-a*a))+atan2(sqrt(1-b*b),b));
  float left = atan2(sqrt(1-c*c), c);

  rot = degrees(rot);
  right = degrees(right);
  left = degrees(left);
  
  //Serial.println(rot);
  //Serial.println(right);
  Serial.println("Vinkel " + (String)left);

  float desimalX = antStepp/360*rot;
  int tallX = (int)desimalX*5.1;

  float desimalY = (antStepp*(90-right))/360;
  int tallY = (int)desimalY*5.1;
  
  float desimalZ = (antStepp*(90-left))/360;
  int tallZ = (int)desimalZ*5.1+tallY;

  //Serial.println(tallX);
  //Serial.println("Skal ga " + (String)(90-right));
  //Serial.println("Antall steg Y " + (String)tallY);
  Serial.println("Antall steg Z " + (String)tallZ);

  
  stepperX.moveTo(tallX);
  while (stepperX.distanceToGo() != 0){
    stepperX.run();
  }
  
  stepperY.moveTo(tallY);
  while (stepperY.distanceToGo() != 0){
    stepperY.run();
  }

  
  stepperZ.moveTo(tallZ);
  while (stepperZ.distanceToGo() != 0){
    stepperZ.run();
  }
  
}

float radianer(float degrees) {
  return degrees / 360 * 2 * pi;
}
float grader(float radians) {
  return radians / (2*pi) * 360;
}
