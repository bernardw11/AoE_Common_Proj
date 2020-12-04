#include <RGBmatrixPanel.h>

//set up the LED matrix pin thingies!
#define CLK 8 //Arduino UNO
#define OE 9
#define LAT 10
#define A A0
#define B A1
#define C A2

//set up the joystick pin thingies
#define joyX1 A3
#define joyY1 A4
#define joyX2 A3
#define joyY2 A4

/*btw, an exmplanation of the dir variable:
 * 0 is down          2
 * 1 is right      3     1
 * 2 is up            0
 * 3 is left
 */

uint8_t xcoord1 = 0;
uint8_t ycoord1 = 0;
int dir1 = 0;
int xcoords1[206];
int ycoords1[206];

uint8_t xcoord2 = 31;
uint8_t ycoord2 = 15;
int dir2 = 2;
int xcoords2[206];
int ycoords2[206];

//length of the list of coords starts at 1.
//we place the default point.
int len = 1;

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() {
  matrix.begin();
  
  xcoords1[0] = xcoord1;
  ycoords1[0] = ycoord1;
  matrix.drawPixel(xcoord1, ycoord1, matrix.Color333(0,7,0));

//  xcoords2[0] = xcoord2;
//  ycoords2[0] = ycoord2;
//  matrix.drawPixel(xcoord2, ycoord2, matrix.Color333(0,0,7));
  
  delay(500);
}

void loop() {
  movePoint1();
  //movePoint2();
  len += 1;
  //if it was a successful move, increase length by one.
  delay(250);
}
void movePoint1(){
  int xValue = analogRead(joyX1);
  int yValue = analogRead(joyY1);
  //figure out movement, given the direction already.
  //1. if currently going down: right, left, or continue down.
  if (dir1 == 0){
    if (xValue>800){
      dir1 = 1;
      xcoord1 += 1;
    }else if (xValue < 800){
      dir1 = 3;
      xcoord1 -= 1;
    }else ycoord1 += 1; //note: ycoord +=1 means ycoord goes down 1.
  //2. elif currently going right: up, down, or continue right.
  } else if (dir1 == 1){
    if (yValue>800){
      dir1 = 2;
      ycoord1 -= 1;
    } else if (yValue < 200){
      dir1 = 0;
      ycoord1 += 1;
    } else xcoord1 += 1;
  //3. elif currently going up: right, left, or continue up.
  } else if (dir1 == 2){
    if (xValue>800){
      dir1 = 1;
      xcoord1 += 1;
    }else if (xValue < 800){
      dir1 = 3;
      xcoord1 -= 1;
    }else ycoord1 -= 1;
  //4. elif currently going left: up, down, or continue left.
  } else if (dir1 == 3){
    if (yValue>800){
      dir1 = 2;
      ycoord1 -= 1;
    } else if (yValue < 200){
      dir1 = 0;
      ycoord1 += 1;
    } else xcoord1 -= 1;
  }
  
  //gotta make sure it doesn't bump into a wall.
  if (xcoord1 < 0 or xcoord1 > 31 or ycoord1 < 0 or ycoord1 > 15){
    gameOver();
  }
  //check if it doesn't bump into a previously lit point
  for (int i = 0; i < len; i ++){
    if (xcoord1 == xcoords1[i] and ycoord1 == ycoords1[i]){
      gameOver();
    }
//    if (xcoord1 = xcoords2[i] and ycoord1 = ycoords2[i]){
//      gameOver();
//    }
//    if (xcoord2 = xcoords1[i] and ycoord2 = ycoords1[i]){
//      gameOver();
//    }
//    if (xcoord2 = xcoords2[i] and ycoord2 = ycoords2[i]){
//      gameOver();
//    }
  }
//  if (xcoord1 == xcoord2 and ycoord1 == ycoord2){
//    gameOver();
//  }
  
  xcoords1[len] = xcoord1;
  ycoords1[len] = ycoord1;
  matrix.drawPixel(xcoord1, ycoord1, matrix.Color333(0,7,0));
}
void movePoint2(){
  int xValue = analogRead(joyX2);
  int yValue = analogRead(joyY2);
  //figure out movement, given the direction already.
  //1. if currently going down: right, left, or continue down.
  if (dir2 == 0){
    if (xValue>800){
      dir2 = 1;
      xcoord2 += 1;
    }else if (xValue < 800){
      dir2 = 3;
      xcoord2 -= 1;
    }else ycoord2 += 1; //note: ycoord +=1 means ycoord goes down 1.
  //2. elif currently going right: up, down, or continue right.
  } else if (dir2 == 1){
    if (yValue>800){
      dir2 = 2;
      ycoord2 -= 1;
    } else if (yValue < 200){
      dir2 = 0;
      ycoord2 += 1;
    } else xcoord2 += 1;
  //3. elif currently going up: right, left, or continue up.
  } else if (dir2 == 2){
    if (xValue>800){
      dir2 = 1;
      xcoord2 += 1;
    }else if (xValue < 800){
      dir2 = 3;
      xcoord2 -= 1;
    }else ycoord2 -= 1;
  //4. elif currently going left: up, down, or continue left.
  } else if (dir2 == 3){
    if (yValue>800){
      dir2 = 2;
      ycoord2 -= 1;
    } else if (yValue < 200){
      dir2 = 0;
      ycoord2 += 1;
    } else xcoord2 -= 1;
  }
  
  //gotta make sure it doesn't bump into a wall.
  if (xcoord2 < 0 or xcoord2 > 31 or ycoord2 < 0 or ycoord2 > 15){
    gameOver();
  }
  //check if it doesn't bump into a previously lit point
  for (int i = 0; i < len; i ++){
    if (xcoord1 == xcoords1[i] and ycoord1 == ycoords1[i]){
      gameOver();
    }
    if (xcoord1 == xcoords2[i] and ycoord1 == ycoords2[i]){
      gameOver();
    }
    if (xcoord2 == xcoords1[i] and ycoord2 == ycoords1[i]){
      gameOver();
    }
    if (xcoord2 == xcoords2[i] and ycoord2 == ycoords2[i]){
      gameOver();
    }
  }
  if (xcoord1 == xcoord2 and ycoord1 == ycoord2){
    gameOver();
  }
  
  xcoords2[len] = xcoord2;
  ycoords2[len] = ycoord2;
  matrix.drawPixel(xcoord1, ycoord1, matrix.Color333(0,7,0));
}


void gameOver(){
  Serial.print("you lost crashed homie");
  delay(1000);
  resetGame();
}
void resetGame(){
  xcoord1 = 0;
  ycoord1 = 0;
  dir1 = 0;

//xcoord2 = 31;
//ycoord2 = 15;
//dir2 = 2;
  
  len = 1;
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  xcoords1[0] = xcoord1;
  ycoords1[0] = ycoord1;
  matrix.drawPixel(xcoord1, ycoord1, matrix.Color333(0,7,0));

//  xcoords2[0] = xcoord2;
//  ycoords2[0] = ycoord2;
//  matrix.drawPixel(xcoord2, ycoord2, matrix.Color333(0,0,7));
  delay(1000);
}
