#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <wiringSerial.h>
#include <softPwm.h>

#define PIN 27	
#define IO digitalRead(PIN)
unsigned char i,idx,cnt;
unsigned char count;
unsigned char data[4];
char a;
long  up  = 0x46;
long  back = 0x15;
long  stop = 0x40;
long  left = 0x44;
long  right= 0x43;
long  esc= 0x4a;
#define ENA 22 
#define ENB 30

int main()
{
    wiringPiSetup();
    pinMode(PIN, INPUT);
    pullUpDnControl(PIN, PUD_UP);
    pinMode(1,OUTPUT);
    int fd ;
    pinMode(26,OUTPUT);
    pinMode(21,OUTPUT);
    pinMode(22,OUTPUT);
    pinMode(30,OUTPUT);
    softPwmCreate(ENA, 0, 100); 
    softPwmCreate(ENB, 0, 100); 
    printf("L298P test......\n");

// note that the delay function is for second count, example: 2000 = 2 seconds that the above functions will run for.
//digitalWrite = 21 and 26 are the motors 

void optionw() {
    printf("Moving forward\n");
    /*digitalWrite(21, HIGH);
      digitalWrite(26, HIGH);
      softPwmWrite(ENA, 100);
      softPwmWrite(ENB, 100);
      delay(1000);*/
}
//both wheels move forward 
void optiona() {
    printf("Moving right \n");
    /*digitalWrite(21, HIGH);
      digitalWrite(26, LOW);
      softPwmWrite(ENA, 50);
      softPwmWrite(ENB, 50);
      delay(1000);*/
}
// lock the right wheel and move forward the left wheel 
void options() {
    printf("Moving backwards \n");
   /*digitalWrite(21, LOW);
     digitalWrite(26, LOW);
      // digital write codes make the direction go backwards 
     softPwmWrite(ENA, 100); // motor a moving at 100% speed
     softPwmWrite(ENB, 100); //motor b moving at 100% speed
     delay(1000); */
}
//both wheels rotate backwards
void optiond() {
    printf("Moving left \n");
    /*digitalWrite(21, LOW);
    digitalWrite(26, HIGH);
    softPwmWrite(ENA, 90);
    softPwmWrite(ENB, 90);
    delay(1000);*/
}
//lock the left wheel and move forward the right wheel 
void optionx() {
    printf("Stopping \n");

   /*softPwmWrite(ENA, 0);
     softPwmWrite(ENB, 0); 
       // setting the speed to 0 
     delay(2000); */
}
// put brakes on||stop the motors

int main() {
    char choice;

    do {
        printf("\n===== MENU =====\n");
        printf("w - move forward\n");
        printf("a - move left\n");
        printf("s - move back\n");
        printf("d - move right\n");
        printf("spacebar - stop\n");
        printf(". - exit program\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'w': optionw(); break;
            case 'a': optiona(); break;
            case 's': options(); break;
            case 'd': optiond(); break;
            case 'x': optionx(); break;
            case '.': printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != '.');

    return 0;
}
