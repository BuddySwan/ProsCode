#include "lmain.h"

void autonomous(){
  move(-1000);
  shoot();
  move(-2000);
  pros::delay(50);
  move(5000);
  pros::delay(50);
  turnDegrees(90);
  pros::delay(50);
  move(3000);
}
