#define leftFor 1
#define leftBack 0
#define rightFor 0
#define rightBack 1

int leftDir = D0;
int leftStep = D1;
int rightDir = D2;
int rightStep = D3;
int distPin = A0;
int linePin = A1;

unsigned long leftPeriod;
unsigned long rightPeriod;
unsigned long leftNext;
unsigned long rightNext;
int leftRemaining;
int rightRemaining;
int leftDirVal;
int rightDirVal;
unsigned long curTime;

void setup() {
    //motor pins (digital)
    pinMode(leftDir, OUTPUT);
    pinMode(leftStep, OUTPUT);
    pinMode(rightDir, OUTPUT);
    pinMode(rightStep, OUTPUT);
    
    //sensor pins (analog)
    pinMode(distPin, INPUT);
    pinMode(linePin, INPUT);

    leftPeriod = 0;
    rightPeriod = 0;
    leftNext = 0;
    rightNext = 0;
    leftRemaining = 0;
    rightRemaining = 0;
    leftDirVal = 0;
    rightDirVal = 0;
    //Serial.begin(9600);
    //Serial.println("hello world");
}

//sets the motors
//  values are -1: backward
//              0: stopped
//              1: forward
void setMotors(int leftVal, int rightVal) {
    //reset variables used in timing based motor use so 
    //there is no confusion with setting PWMing pins.
    leftRemaining = 0;
    rightRemaining = 0;
    leftNext = 0;
    rightNext = 0;
    leftPeriod = 0;
    rightPeriod = 0;
    
    if (leftVal < 0) {
        digitalWrite(leftDir, leftBack);
        analogWrite(leftStep, 127); //arbitrary pwm value
    } else if (leftVal > 0) {
        digitalWrite(leftDir, leftFor);
        analogWrite(leftStep, 127);
    } else {
        analogWrite(leftStep, 0);
    }
    
    if (rightVal < 0) {
        digitalWrite(rightDir, rightBack);
        analogWrite(rightStep, 127); //arbitrary pwm value
    } else if (rightVal > 0) {
        digitalWrite(rightDir, rightFor);
        analogWrite(rightStep, 127);
    } else {
        analogWrite(rightStep, 0);
    }
}

void updateMotors(){
    curTime = millis();
    if(leftRemaining > 0 && curTime >= leftNext){
        digitalWrite(leftStep, 1);
        leftRemaining--;
        leftNext = curTime + leftPeriod;
    }
    if(rightRemaining > 0 && curTime >= rightNext){
        digitalWrite(rightStep, 1);
        rightRemaining--;
        rightNext = curTime + rightPeriod;
    }
    delay(1);
    digitalWrite(leftStep, 0);
    digitalWrite(rightStep, 0);
}

/* 
period is in ms, period = 2 is the fastest possible
*/
void moveLeftMotor(int dir, int steps, int period){
    if(period < 2){
        period = 2;
    }
    if(leftPeriod == period && leftDirVal == dir){
        leftRemaining += steps;
    } else {
        leftRemaining = steps;
        leftPeriod = period;
        leftNext = millis() + leftPeriod;
        digitalWrite(leftStep, 0);
        digitalWrite(leftDir, dir);
    }
}

void moveRightMotor(int dir, int steps, int period){

    if(period < 2){
        period = 2;
    }
    if(rightPeriod == period && rightDirVal == dir){
        rightRemaining += steps;
    } else {
        rightRemaining = steps;
        rightPeriod = period;
        rightNext = millis() + rightPeriod;
        digitalWrite(rightStep, 0);
        digitalWrite(rightDir, dir);
    }
}

void loopMoveMotors(int lDir, int lSteps, int rDir, int rSteps, int period) {
    if(period < 2){
        period = 2;
    }
    digitalWrite(leftDir, lDir);
    digitalWrite(rightDir, rDir);
    
    while (lSteps > 0 || rSteps > 0) {
        if (lSteps > 0) {
            lSteps--;
            digitalWrite(leftStep, 1);
        }
        if (rSteps > 0) {
            rSteps--;
            digitalWrite(rightStep, 1);
        }
        delay(1);
        digitalWrite(leftStep, 0);
        digitalWrite(rightStep, 0);
        delay(period - 1);
    }
    
}

unsigned long oldTime = 0;
unsigned long total = 0;
unsigned long incs = 0;
unsigned long lastLoop = 0;
bool start = true;
void loop() {
    int distVal = analogRead(distPin);
    int lineVal = analogRead(linePin);
    
    //Serial.print("dist: "); Serial.print(distVal);
    //Serial.print(" line: "); Serial.println(lineVal);
    //digitalWrite(leftDir, 0);
    //analogWrite(leftStep, 127);
    //digitalWrite(rightDir, 0);
    //analogWrite(rightStep, 127);
    //delay(1000);
    /*while(abs(distVal - analogRead(distPin)) < 500){
        setMotors(-1, 1);
    }*/
    setMotors(-1, 1);
    delay(3000);
    //loopMoveMotors(0, 200, 0, 400, 6);
    //delay(2000);
    //setMotors(1, 1);
    //delay(2000);
    /*
    setMotors(-1, 1);
    delay(2000);
    setMotors(-1, -1);
    delay(2000);
    setMotors(0, -1);
    delay(2000);
    setMotors(0, 0);
    delay(2000);
    
    /*
    incs++;
    
    unsigned long curTime = micros();
    if(curTime - lastLoop > 1000000){
        unsigned long loopTime = total / incs;
        Serial.println(curTime - oldTime);
        total = 0;
        incs = 0;
        lastLoop = curTime;
    }
    total += curTime - oldTime;
    oldTime = curTime;
    */
}
