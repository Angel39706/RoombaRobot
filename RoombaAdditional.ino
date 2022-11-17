#include <NewPing.h>
#define TRIGGER_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 200

// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define FORWARD  0
#define REVERSE 1

// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1

// Pin Assignments //
//Default pins:
#define DIRA 2 // Direction control for motor A
#define PWMA 3  // PWM control (speed) for motor A
#define DIRB 4 // Direction control for motor B
#define PWMB 11 // PWM control (speed) for motor B

int LED1 = 13; //LED1 pin 13
int LED2 = 12; //LED2 pin 12
const int buzzerPin = 5; //active buzzer pin 5

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
  setupArdumoto(); // Set all pins as outputs
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
unsigned int uS = sonar.ping();
  if( uS / US_ROUNDTRIP_CM > 40 || uS / US_ROUNDTRIP_CM == 0)
  {
    
    forward(200);
  }
   else if( uS / US_ROUNDTRIP_CM < 40)
    {
      reverse(150);
      delay( 900);
      if (random(2) == 1)
      {
        left(250);
        delay(400);
      }      
      else
      {
        right(250);
        delay(400);      
        }
      }
}
void forward(byte spd)
{
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  digitalWrite(buzzerPin, LOW);
  driveArdumoto(MOTOR_A, FORWARD, spd);  // Motor A at max speed.
  driveArdumoto(MOTOR_B, FORWARD, spd); 
}

void reverse( byte spd)
{
   digitalWrite(LED1, HIGH);
   digitalWrite(LED2, LOW);
   digitalWrite(buzzerPin, HIGH);
   driveArdumoto(MOTOR_A, REVERSE, spd);  // Motor A at max speed.
   driveArdumoto(MOTOR_B, REVERSE, spd); 
}

void left(byte spd)
{
  
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(buzzerPin, LOW);
  driveArdumoto(MOTOR_A, FORWARD, spd);  // Motor A at max speed.
  driveArdumoto(MOTOR_B, REVERSE, spd); 
}


void right(byte spd)
{
  
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(buzzerPin, LOW);
  driveArdumoto(MOTOR_A, REVERSE, 100);  // Motor A at max speed.
  driveArdumoto(MOTOR_B, FORWARD, 255); 
}
// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}

// stopArdumoto makes a motor stop
void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}

// setupArdumoto initialize all pins
void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}
