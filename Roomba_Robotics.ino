#include <NewPing.h>
#define TRIGGER_PIN 7
#define ECHO_PIN 6
#define MAX_DISTANCE 200

#define CW 0
#define CCW 1

// Motor Definitions
#define MOTOR_A 0
#define MOTOR_B 1

//Pin assignments
//do not alter pin numbers

//Ardumoto
const byte PWMA = 3;  //PWM control (speed) for motor A
const byte PWMB = 11; //PWM control (speed) for motor B
const byte DIRA = 12; //Direction control for motor A
const byte DIRB = 13; //Direction control for motor B

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
  setupArdumoto();  //Set all pins as outputs and initialize them to LOW
  }
void loop()
{
  delay(50);
  unsigned int uS = sonar.ping();
  if( uS / US_ROUNDTRIP_CM > 25 || uS / US_ROUNDTRIP_CM == 0)
  {
    // Move forward
    forward(220);
    }else if( uS / US_ROUNDTRIP_CM < 25)
    {
      turnRight(200);
      delay(900);
      }
  }

void driveArdumoto(byte motor, byte dir, byte spd)
{
  if( motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
    }else if( motor == MOTOR_B)
    {
      digitalWrite(DIRB, dir);
      analogWrite(PWMB, spd);
      }
  }

void forward( byte spd)
{
  driveArdumoto(MOTOR_A, CW, spd);
  driveArdumoto(MOTOR_B, CW, spd);
  }

void turnRight( byte spd)
{
  stopArdumoto(MOTOR_B);
  driveArdumoto(MOTOR_A, CW, spd);
  }

void stopArdumoto( byte motor)
{
  driveArdumoto(motor, 0, 0);
  }


// set up ardumoto initialize all the pins
void setupArdumoto()
{
  //pins set as outputs
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  //initialize pins as low
  pinMode(PWMA, LOW);
  pinMode(PWMB, LOW);
  pinMode(DIRA, LOW);
  pinMode(DIRB, LOW);
  }
