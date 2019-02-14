#include "lmain.h"

pros::Motor leftF(LeftF);
pros::Motor leftB(LeftB);
pros::Motor rightF(RightF,true);
pros::Motor rightB(RightB,true);
pros::Motor catapult(Cata);
pros::Motor catapult2(Cata2);
pros::Motor flipper(Flipper);
pros::Controller master (CONTROLLER_MASTER);
pros::Motor roller(Roller);
pros::Motor uptake(Uptake);
pros::Motor pokeBar(PokeBar);

bool rollToggle = true;
bool flipperDown = true;
bool flipToggle = true;
bool upToggle = true;
bool uptakeOn = false;
int power = 127;
void Roll(){
    if(master.get_digital(DIGITAL_Y) && rollToggle){
        rollToggle = false;
        power = -power;
        roller.move(power);
    }else if(!master.get_digital(DIGITAL_Y)){
      rollToggle = true;
    }
}

void waitUntil(){
  while(leftF.get_position() != leftF.get_target_position() && leftB.get_position() != leftB.get_target_position() && rightF.get_position() != rightF.get_target_position() && rightB.get_position() != rightB.get_target_position()){
      pros::delay(2);
  }
}

void move(double distance){
  double speed = 100;
  leftF.move_relative(distance,speed);
  leftB.move_relative(distance,speed);
  rightF.move_relative(distance,speed);
  rightB.move_relative(distance,speed);
  waitUntil();
}

 void moveTiles(int numTiles){
    int tileLength = 20;
    move(numTiles*tileLength);
 }
 void turnDegrees(int angle){
    int rightAngle = 750;
    int speed = 100;
    leftF.move_relative(angle*rightAngle/90,speed);
    leftB.move_relative(angle*rightAngle/90,speed);
    rightF.move_relative(-angle*rightAngle/90,speed);
    rightB.move_relative(-angle*rightAngle/90,speed);
    waitUntil();
 }

void flipFlip(){
  if(master.get_digital(DIGITAL_X) && flipToggle){
    flipperDown = !flipperDown;
    flipper.move_relative(flipperDown * 150, 100);
    flipToggle = false;
  }else if(!master.get_digital(DIGITAL_X)){
    flipToggle = true;
  }
}

 void drive(){
   int power = master.get_analog(ANALOG_LEFT_Y);
   int turn = master.get_analog(ANALOG_RIGHT_X);
   int left = power + turn;
   int right = power - turn;
   leftF.move(left);
   leftB.move(left);
   rightF.move(right);
   rightB.move(right);
 }
 void lift(bool auton){
    if((master.get_digital(DIGITAL_B) && upToggle) ){
      upToggle = false;
      uptakeOn = !uptakeOn;
      uptake.move(127*uptakeOn);
    }else if(!master.get_digital(DIGITAL_B)){
      upToggle = true;
    }
 }
 void runCatapult(){
   int speed = 100;
   if(master.get_digital(DIGITAL_R1)){
     catapult.move(speed);
     catapult2.move(speed);
     pros::lcd::set_text(1, "R1");
   }
   if(master.get_digital(DIGITAL_R2)){
     catapult.move(-speed);
     catapult2.move(-speed);
     pros::lcd::set_text(1, "R2");
   }
 }
 void shoot(){

 }
