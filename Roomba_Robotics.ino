//UltraSonic Sensor 
#include <NewPing.h>

#define TRIGGER_PIN  7
#define ECHO_PIN     6
#define MAX_DISTANCE 200

#define CW 0
#define CCW 1
//Motor Definitions
#define MOTOR_A 0
#define MOTOR_B 1

// Pin Assignments
// Don’t change these! These pins are statically defined by the shield layout 
const byte PWMA = 3; // PWM control (speed) for motor A
const byte PWMB = 11; // PWM control (speed) for motor B
const byte DIRA = 12; // Direction control for motor A
const byte DIRB = 13; // Direction control for motor B
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum // distance.
void setup() {
  setupArdumoto(); // Set all pins as outputs
  }
  
void loop() {
  delay(50);
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS). 
  if ( uS / US_ROUNDTRIP_CM > 50 || uS / US_ROUNDTRIP_CM == 0)
{
// Move forward
forward(150);
}
else if (uS / US_ROUNDTRIP_CM < 50)
{
turnRight(100);
delay(500);
}
}

// driveArdumoto drives ’motor’ in direction ’dir’ at speed ’spd’ 
void driveArdumoto(byte motor, byte dir, byte spd)
{
if (motor == MOTOR_A) 
{
  digitalWrite(DIRA, dir);
  analogWrite(PWMA, spd); 
}
else if (motor == MOTOR_B)
{
  digitalWrite(DIRB, dir); analogWrite(PWMB, spd);
} 
}

void forward(byte spd) // Runs both motors at speed ’spd’ 
{
  driveArdumoto(MOTOR_A, CW, spd); 
  driveArdumoto(MOTOR_B, CW, spd);
}

void turnRight(byte spd) 
{
  stopArdumoto(MOTOR_B); 
  driveArdumoto(MOTOR_A, CW, spd);
// stopArdumoto makes a motor stop 
}

void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0); 
}
 

// setupArdumoto initializes all pins 
void setupArdumoto()
{
// All pins should be set up as outputs: 
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
