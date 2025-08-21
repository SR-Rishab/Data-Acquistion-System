#include<avr/io.h>
#include"USART_PWM_ATmega328P.c"
#include<string.h>

/*
 P O*RTB is for stepper and dc motors
 PORTB.4 and PORTB.6 are for DC motors
 PORTB.0 - PORTB.3 are for stepper motors
 PORTC.0 DHT sensor input
 PORTC.1 MQ(sensor) input
 PORTC.2 Infrared sensor
 */

// Message strings
char intial_message[] = "Enter mode: Manual(0) Auto(1)";
char motor_select_message[] = "Enter motor: DC(0) Stepper(1)";
char dc_speed[] = "DC speed: 3 digits";
char stepper_rot[] = "Enter angle";
char sensor_select[] = "Select sensor: (1)DHT (2)Gas (3)Infrared";
char dht_output[] = "Temperature is: ";
char gas_output[] = "Gas output is: ";
char infra_detected[] = "Object detected";
char infra_not[] = "No object detected\n";

void Manual();
void Auto();
// Manual mode functions
void StartDCMotor(); // Start DC motor when key is pressed or Sensor data
void StartStepperMotor(); // Start Stepper motor on key press or sensor data
void RotateStepperMotor(int angle); // Rotate stepper motor on key press or sensor data

// Auto mode functions
void DHTFunction();
void GasFunction();
void InfraredFunction();
// String function
void TransmitString(char* string); // Function to transmit string
void ReceiveString(char* string); // Function to receive string of length 3
