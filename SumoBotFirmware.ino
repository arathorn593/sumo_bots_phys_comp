#define lineThresh 1000
#define speed 255
#define rotateTime 400
#define forwardTime 900
#define cruiseSpeed 120

int leftPin = D0;
int rightPin = D1;
int linePin = A0;

void setup() {
    pinMode(leftPin, OUTPUT);
    pinMode(rightPin, OUTPUT);
    pinMode(linePin, INPUT);
}

void loop() {
    if (analogRead(linePin) > lineThresh) {
        analogWrite(leftPin, 0);
        analogWrite(rightPin, speed);
        delay(rotateTime);
        analogWrite(leftPin, speed);
        analogWrite(rightPin, speed);
        delay(forwardTime);
    } else {
        analogWrite(leftPin, cruiseSpeed - 5);
        analogWrite(rightPin, cruiseSpeed);
    }
        
}
