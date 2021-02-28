#include <AccelStepper.h>

class RobotArm2 {
  private:
    const float L1o = 40;
    const float Zo = -77;
    const float L_2 = 71.0;
    const float Lo= 41;
    const float Au = 180.0;
    const float Al = 177.0;
    const float pi = 3.141;
    const int antStepp = 200;

    AccelStepper stepperX;
    AccelStepper stepperY;
    AccelStepper stepperZ;

    const int enPin = 8;

    float radianer(float degrees) {
      return degrees / 360 * 2 * pi;
    }
    float grader(float radians) {
      return radians / (2*pi) * 360;
    }
    void flyttTil(AccelStepper acSt, int tall){
      acSt.moveTo(tall);
      acSt.run();
      /*while (acSt.distanceToGo() != 0){
        acSt.run();
      }*/
    }
    
  public:
    RobotArm2(AccelStepper x, AccelStepper y, AccelStepper z){
      stepperX = x;
      stepperY = y;
      stepperZ = z;
      
      pinMode(enPin,OUTPUT); //For at stepperen skal fungere
      digitalWrite(enPin,LOW);
      Serial.begin(9600); 
      setFart(100,100);
    }
    void setFart(int speed, int aksel){
      stepperX.setMaxSpeed(speed);
      stepperX.setAcceleration(aksel);
      stepperY.setMaxSpeed(speed);
      stepperY.setAcceleration(aksel);
      stepperZ.setMaxSpeed(speed);
      stepperZ.setAcceleration(aksel);
    }
    void gaaTilKor(float x, float y, float z){
      float lengde = sqrt(x*x+y*y);
      if (z > 220 || z < 0){
        Serial.println("Ugyldig z-kordinat: " + (String)z);
        return;
      }
      if (lengde < 200 || lengde > 400){
        Serial.println("Ugyldig lengde: " + (String)lengde);
        return;
      }
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
      
      Serial.println("Vinkel " + (String)left);
    
      float desimalX = antStepp/360*rot;
      int tallX = (int)desimalX*5.1;
    
      float desimalY = (antStepp*(90-right))/360;
      int tallY = (int)desimalY*5.1;
      
      float desimalZ = (antStepp*(90-left))/360;
      int tallZ = (int)desimalZ*5.1+tallY;
    
      Serial.println("Antall steg Z " + (String)tallZ);

      flyttTil(stepperX,tallX);
      flyttTil(stepperY,tallY);
      flyttTil(stepperZ,tallZ);
    }
};

const int stepX = 2; //Steppermotor X
const int dirX  = 5;
AccelStepper sX(1, stepX, dirX);

const int stepY = 3; //Steppermotor Y
const int dirY  = 6;
AccelStepper sY(1, stepY, dirY);

const int stepZ = 4; //Steppermotor Z
const int dirZ  = 7;
AccelStepper sZ(1, stepZ, dirZ);

void setup() {
  RobotArm2 RA2(sX, sY, sZ);
}

void loop() {
  // put your main code here, to run repeatedly:

}
