// code not complete, this is an example for when we add three senros, one front, and one on each side
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>

// Define Motor Pins
#define ENA 1     // PWM for Motor A
#define ENB 2     // PWM for Motor B
#define IN1 21    // Motor A Direction
#define IN2 26    // Motor B Direction

// Define Ultrasonic Sensor Pins
#define TRIG_FRONT 23
#define ECHO_FRONT 24
#define TRIG_LEFT 27
#define ECHO_LEFT 28
#define TRIG_RIGHT 29
#define ECHO_RIGHT 30

// Function to get distance from ultrasonic sensor
int getDistance(int trigPin, int echoPin) {
    long startTime, stopTime;
    int distance;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    while (digitalRead(echoPin) == LOW);
    startTime = micros();

    while (digitalRead(echoPin) == HIGH);
    stopTime = micros();

    distance = (stopTime - startTime) * 0.0343 / 2;
    return distance;
}

// Movement functions
void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    softPwmWrite(ENA, 80);
    softPwmWrite(ENB, 80);
}

void stopMotors() {
    softPwmWrite(ENA, 0);
    softPwmWrite(ENB, 0);
}

void moveBackward() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    softPwmWrite(ENA, 60);
    softPwmWrite(ENB, 60);
    delay(1000);
    stopMotors();
}

void turnRight() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    softPwmWrite(ENA, 80);
    softPwmWrite(ENB, 40);
    delay(500);
}

void turnLeft() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    softPwmWrite(ENA, 40);
    softPwmWrite(ENB, 80);
    delay(500);
}

int main() {
    wiringPiSetup();

    // Configure motor control pins
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    // Configure ultrasonic sensor pins
    pinMode(TRIG_FRONT, OUTPUT);
    pinMode(ECHO_FRONT, INPUT);
    pinMode(TRIG_LEFT, OUTPUT);
    pinMode(ECHO_LEFT, INPUT);
    pinMode(TRIG_RIGHT, OUTPUT);
    pinMode(ECHO_RIGHT, INPUT);

    // Enable software PWM for speed control
    softPwmCreate(ENA, 0, 100);
    softPwmCreate(ENB, 0, 100);

    printf("Advanced Obstacle Avoidance Robot Starting...\n");

    while (1) {
        int frontDist = getDistance(TRIG_FRONT, ECHO_FRONT);
        int leftDist = getDistance(TRIG_LEFT, ECHO_LEFT);
        int rightDist = getDistance(TRIG_RIGHT, ECHO_RIGHT);

        printf("Front: %d cm, Left: %d cm, Right: %d cm\n", frontDist, leftDist, rightDist);

        if (frontDist < 20) { // Obstacle in front
            printf("Obstacle detected in front!\n");
            stopMotors();
            delay(500);

            if (leftDist > 20) {
                printf("Turning Left...\n");
                turnLeft();
            } else if (rightDist > 20) {
                printf("Turning Right...\n");
                turnRight();
            } else {
                printf("Both sides blocked, moving backward...\n");
                moveBackward();
            }
        } else {
            moveForward();
        }

        delay(100);
    }

    return 0;
}
