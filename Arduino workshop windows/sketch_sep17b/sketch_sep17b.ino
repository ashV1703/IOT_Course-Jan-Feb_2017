// Connections to pins
const int TOP_LAYER = 2;
const int BOTTOM_LAYER = 3;
const int COLUMN_1 = 11;
const int COLUMN_2 = 10;
const int COLUMN_3 = 9;
const int COLUMN_4 = 6;

//Constants
const int DELAY = 5; //Delay between cube top/bottom layer alternations, in milliseconds. 5 seems optimal for 2 layers.

//Cube Map
int cube[2][2][2];

//Setup
void setup(){
  //Setup Pin-Outputs
  pinMode(TOP_LAYER, OUTPUT);  
  pinMode(BOTTOM_LAYER, OUTPUT);  
  pinMode(COLUMN_1, OUTPUT);  
  pinMode(COLUMN_2, OUTPUT);  
  pinMode(COLUMN_3, OUTPUT);
  pinMode(COLUMN_4, OUTPUT);
  //Gets Random Seed from Analog Pin
  randomSeed(analogRead(5));
  clearCube();
}

//Main Loop - Insert patterns here, this is the 'playlist'
void loop(){
  clearCube();
  render(1000);
  patternBlinkIn();
  fillCube();
  render(2000);
  patternBlinkOut();
  render(1000);
  patternSpiralTop(8);
  patternSpiralBottom(8);
  patternSpiralTopThenBottom(10);  
  patternFacesRandom(30);
  patternSlashesAlternating(10);
  patternBlinkCube(30);
  patternRotateClockwise(20);
  patternRandomLED(20);
}

void patternBlinkIn(){
  int count, x, y, z;
  count = 8;
  clearCube();
  while(count > 0){
    x = random(2);
    y = random(2);
    z = random(2);
    if(cube[y][x][z]==0){
      cube[y][x][z]=1;
      count--;
      render(500);
    }
  }
  clearCube();
}

void patternBlinkOut(){
  int count, x, y, z;
  count = 8;
  fillCube();
  while(count > 0){
    x = random(2);
    y = random(2);
    z = random(2);
    if(cube[y][x][z]==1){
      cube[y][x][z]=0;
      count--;
      render(500);
    }
  }
  clearCube();
}

void patternSpiralTopThenBottom(int repetitions){
 int i;
 for (i=0;i<repetitions;i++){
   patternSpiralTop(1);
   patternSpiralBottom(1);
 }
}

void patternSpiralTop(int repetitions){
 int i;
 for (i=0;i<repetitions;i++){
 cube[1][0][0] = 1;
 render(100);
 clearCube();
  cube[1][1][0] = 1;
 render(100);
 clearCube();
  cube[1][1][1] = 1;
 render(100);
 clearCube();
  cube[1][0][1] = 1;
 render(100);
 clearCube();
 }
}

void patternSpiralBottom(int repetitions){
   int i;
 for (i=0;i<repetitions;i++){
 cube[0][0][0] = 1;
 render(100);
 clearCube();
  cube[0][1][0] = 1;
 render(100);
 clearCube();
  cube[0][1][1] = 1;
 render(100);
 clearCube();
  cube[0][0][1] = 1;
 render(100);
 clearCube();
 }
}

void patternFacesRandom(int repetitions){
  int i, face;
  for(i = 0; i<repetitions;i++){
    face = random(6);
    switch (face){
    case 0: //Top
      {
        cube[1][0][0] = 1;
        cube[1][1][0] = 1;
        cube[1][0][1] = 1;
        cube[1][1][1] = 1;
      }
      break;
    case 1://Bottom
      {
        cube[0][0][0] = 1;
        cube[0][1][0] = 1;
        cube[0][0][1] = 1;
        cube[0][1][1] = 1;
      }
      break;
    case 2://Left
      {
        cube[0][0][0] = 1;
        cube[1][0][0] = 1;
        cube[0][0][1] = 1;
        cube[1][0][1] = 1;
      }
      break;
    case 3://Right
      {
        cube[0][1][0] = 1;
        cube[1][1][0] = 1;
        cube[0][1][1] = 1;
        cube[1][1][1] = 1;
      }
      break;
    case 4://Front
      {
        cube[0][0][1] = 1;
        cube[0][1][1] = 1;
        cube[1][0][1] = 1;
        cube[1][1][1] = 1;
      }
      break;
    case 5://Back
      {
        cube[0][1][0] = 1;
        cube[0][0][0] = 1;
        cube[1][1][0] = 1;
        cube[1][0][0] = 1;
      }
      break;
    }
    render(400);
    clearCube();
  }
}

void patternSlashesAlternating(int repetitions){
  int i;
  for(i=0;i<repetitions;i++){
    cube[0][0][0] = 1;  
    cube[1][0][0] = 1;
    cube[0][1][1] = 1;
    cube[1][1][1] = 1;
    render(350);
    clearCube();
    cube[0][1][0] = 1;  
    cube[1][1][0] = 1;
    cube[0][0][1] = 1;
    cube[1][0][1] = 1;
    render(350);
    clearCube();
  } 
}

void patternBlinkCube(int repetitions){
  int i;
  for(i=0;i<repetitions;i++){
    fillCube();
    render(100);
    clearCube();
    render(100);
  } 
}

void patternRandomLED(int repetitions){
  int i, x, y, z;
  for(i=0;i<repetitions;i++){
    x = random(2);
    y = random(2);
    z = random(2);
    cube[y][x][z]=1;
    render(250);
    clearCube();
  }
}

void patternRotateClockwise(int repetitions){
  int i;
  int speedDelay = 125;
  for (i = 0;i<repetitions;i++){
    cube[0][0][0] = 1; 
    cube[1][0][0] = 1;
    render(speedDelay);
    clearCube();
    cube[0][1][0] = 1; 
    cube[1][1][0] = 1;
    render(speedDelay);
    clearCube();
    cube[0][1][1] = 1; 
    cube[1][1][1] = 1;
    render(speedDelay);
    clearCube();
    cube[0][0][1] = 1; 
    cube[1][0][1] = 1;
    render(speedDelay);
    clearCube();
  }
}

//Function to draw cube map for specified number of milliseconds. 
//Automatically alternates between top and bottom layer for illusion
//Draws the current binary cube matrix to the Arduino for 'pausetime' milliseconds.
void render(int pauseTime){
  long timer = 0;
  while(timer<=pauseTime){
    //**** Draw Top ****
    digitalWrite(TOP_LAYER, HIGH);
    if(cube[1][0][0] == 1){
      digitalWrite(COLUMN_1, HIGH);
    }
    else{
      digitalWrite(COLUMN_1, LOW);
    };
    if(cube[1][1][0] == 1){
      digitalWrite(COLUMN_2, HIGH);
    }
    else{
      digitalWrite(COLUMN_2, LOW);
    };
    if(cube[1][0][1] == 1){
      digitalWrite(COLUMN_3, HIGH);
    }
    else{
      digitalWrite(COLUMN_3, LOW);
    };
    if(cube[1][1][1] == 1){
      digitalWrite(COLUMN_4, HIGH);
    }
    else{
      digitalWrite(COLUMN_4, LOW);
    };
    delay(DELAY);
    digitalWrite(TOP_LAYER, LOW);
    //**** Draw Bottom ****
    digitalWrite(BOTTOM_LAYER, HIGH);
    if(cube[0][0][0] == 1){
      digitalWrite(COLUMN_1, HIGH);
    }
    else{
      digitalWrite(COLUMN_1, LOW);
    };
    if(cube[0][1][0] == 1){
      digitalWrite(COLUMN_2, HIGH);
    }
    else{
      digitalWrite(COLUMN_2, LOW);
    };
    if(cube[0][0][1] == 1){
      digitalWrite(COLUMN_3, HIGH);
    } 
    else{
      digitalWrite(COLUMN_3, LOW);
    };
    if(cube[0][1][1] == 1){
      digitalWrite(COLUMN_4, HIGH);
    } 
    else{
      digitalWrite(COLUMN_4, LOW);
    };
    delay(DELAY);
    digitalWrite(BOTTOM_LAYER, LOW);
    timer += DELAY * 2;
  }
}

//Function to turn all LEDs in the cube off
void clearCube(){
  int i, j, k;
  for(i=0;i<2;i++)
  {
    for(j=0;j<2;j++)
    {
      for(k=0;k<2;k++)
      {
        cube[i][j][k] = 0;
      }
    }
  }
}

//Function to turn all LEDs in the cube on
void fillCube(){
  int i, j, k;
  for(i=0;i<2;i++)
  {
    for(j=0;j<2;j++)
    {
      for(k=0;k<2;k++)
      {
        cube[i][j][k] = 1;
      }
    }
  }
}
