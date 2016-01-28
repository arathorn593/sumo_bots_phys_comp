#define lineThresh 1000     //lowest value from line sensor that is definitely a line
#define speed 255           //speed used when manuvering
#define rotateTime 400      //ms, time for robot to turn around
#define forwardTime 900     //ms, time for robot to go forward after turning
#define cruiseSpeed 120     //speed used when looking for line

int leftPin = D0;           //pin of left motor
int rightPin = D1;          //pin of right motor
int linePin = A0;           //pin for line sensor

void setup() {
    //set mode of all the pins
    pinMode(leftPin, OUTPUT);
    pinMode(rightPin, OUTPUT);
    pinMode(linePin, INPUT);
}

void loop() {
    //check if the line sensor sees the line
    if (analogRead(linePin) > lineThresh) {
        //if the line is seen, make the robot turn around 
        analogWrite(leftPin, 0);
        analogWrite(rightPin, speed);
        delay(rotateTime);
        
        //also, go forward after turning so the robot definitely gets inside the arena
        analogWrite(leftPin, speed);
        analogWrite(rightPin, speed);
        delay(forwardTime);
    } else {
        //if the line is not seen, move the robot forward
        analogWrite(leftPin, cruiseSpeed - 5);
        analogWrite(rightPin, cruiseSpeed);
    }
        
}
