#include <Servo.h>
#include <SoftwareSerial.h>

//setting gobal variables
int pwmL = 5;
int pwmR = 3;
int pos1 = 6;
int pos2 = 7;
int pos3 = 4;
int pos4 = 2;
int roverCommand = 0;
int servoPin = 9; //servo pin
int servoPos = 0; //position of servo
Servo myServo; //creats servo object
SoftwareSerial mySerial(0, 1); // RX and TX

void setup() {
  // put your setup code here, to run once:

  //configuring the ports
  pinMode(pwmL, OUTPUT);
  pinMode(pwmR, OUTPUT);
  pinMode(pos1, OUTPUT);
  pinMode(pos2, OUTPUT);
  pinMode(pos3, OUTPUT);
  pinMode(pos4, OUTPUT);
  digitalWrite(pos1, LOW) ;   // Both motor with same polarity
  digitalWrite(pos2, LOW) ;
  digitalWrite(pos3, LOW) ;
  digitalWrite(pos4, LOW) ;
  analogWrite(pwmL, 0);   // Stop both motors => ValMx = 0
  analogWrite(pwmR, 0); 

  myServo.attach(servoPin); // sets servo pin
     
  mySerial.begin(9600); // starts serial
}

// put your main code here, to run repeatedly:
void loop() {
  
  if(mySerial.available() > 0) {
    shouldRoverMove();
  }

  /*
  for(servoPos = 0; servoPos <= 180; servoPos += 1) {
    shouldRoverMove(); //starts rover moving
    delay(15);
  }
  for(servoPos = 180; servoPos >= 0; servoPos -= 1) {
    myServo.write(servoPos);
    delay(15);
  }
  */
}


// starts rover moving with specific speed and direction
void driveRover(int roverSpeed, String roverDirection) {

  // prints rover speed
  String currentText = " is the current speed and the motor direction is " + roverDirection;
  mySerial.println(roverSpeed + currentText);
  mySerial.println("");

  if(roverDirection = "forward"){
    digitalWrite(pos1, LOW);
    digitalWrite(pos2, HIGH);
    digitalWrite(pos3, HIGH);
    digitalWrite(pos4, LOW);
  }else if(roverDirection = "left") {
    digitalWrite(pos1, LOW);
    digitalWrite(pos2, HIGH);
    digitalWrite(pos3, LOW);
    digitalWrite(pos4, HIGH);
  }else if(roverDirection = "right") {
    digitalWrite(pos1, HIGH);
    digitalWrite(pos2, LOW);
    digitalWrite(pos3, HIGH);
    digitalWrite(pos4, LOW);
  }else if(roverDirection = "reverse") {
    digitalWrite(pos1, HIGH);
    digitalWrite(pos2, LOW);
    digitalWrite(pos3, LOW);
    digitalWrite(pos4, HIGH);
  }else if(roverDirection = "stop") {
    digitalWrite(pos1, LOW);
    digitalWrite(pos2, LOW);
    digitalWrite(pos3, LOW);
    digitalWrite(pos4, LOW);
  }
  
  analogWrite(pwmL, roverSpeed);
  analogWrite(pwmR, roverSpeed);
}

// tree of direction choices
void shouldRoverMove() {
  // reads serial
  roverCommand = mySerial.read();

  // moves rover
  if(roverCommand == 56){
    driveRover(255, "forward"); // full speed ahead
    }
  else if(roverCommand == 52){
    driveRover(75, "left");// turns rover
  }
  else if(roverCommand == 50){
    driveRover(255, "reverse");// reverses rover
  }
  else if(roverCommand == 54){
    driveRover(75, "right"); // turns rover
  }
  else if(roverCommand == 53) {
    driveRover(0, "stop"); // stops rover
  }
}


