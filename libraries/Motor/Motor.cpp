/*
 * Motor.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Erfan
 */

#include "Motor.h"

Encoder::Encoder() {
	//do nothing
}

Encoder::Encoder(int APin, int BPin) {

	this->encoderAPin = APin;
	this->encoderBPin = BPin;

	/* Arduino Setting Code */
	pinMode(encoderAPin, INPUT_PULLUP);
	pinMode(encoderBPin, INPUT_PULLUP);

	/* Add Interrupts in Arduino Setup! */

	encoderPos = 0;
	inputMask = (1 << encoderAPin) | (1 << encoderBPin);
}

Encoder::~Encoder() {
	//do nothing
}

void Encoder::encoderEventA_ISR() {

	if((PIND & inputMask) == inputMask) {
		encoderPos++;	//counter clockwise
	}
	else {
		encoderPos--;	//clockwise
	}
}

void Encoder::encoderEventB_ISR() {
	if((PIND & inputMask) == inputMask) {
		encoderPos--;
	}
	else {
		encoderPos++;
	}
}

signed long int Encoder::getEncoderPosition() {
	return encoderPos;
}

Motor::Motor() {
	//do nothing
}

Motor::Motor(int enablePin, int inputPin1, int inputPin2) {

	this->enablePin = enablePin;
	this->inputPin1 = inputPin1;
	this->inputPin2 = inputPin2;

	/*Arduino Setting */
	pinMode(enablePin, OUTPUT);
	pinMode(inputPin1, OUTPUT);
	pinMode(inputPin2, OUTPUT);

	//default direction of motor is clockwise
	this->inputValueToPin1 = HIGH;
	this->inputValueToPin2 = LOW;
	this->polarity = 0;
}

Motor::Motor(int enablePin, int inputPin1, int inputPin2, int APin, int BPin) {
	Motor(enablePin,inputPin1,inputPin2);
	encoder = Encoder(APin,BPin);
}

Motor::~Motor() {
	//do nothing
}

void Motor::spinMotor(int dutyCycle) {
	digitalWrite(inputPin1,inputValueToPin1);
	digitalWrite(inputPin2,inputValueToPin2);
	analogWrite(enablePin,dutyCycle);
}

void Motor::moveStraight(float distance = 18.0) {
	/*call to PID and PWM */

}

void Motor::turnLeft(float distance = 6.4) {
	/*call to PID and PWM */
}

void Motor::turnRight(float distance = 6.4) {
	/*call to PID and PWM */
}

void Motor::reversePolarity()  {

	int T = inputValueToPin1;
	inputValueToPin1 = inputValueToPin2;
	inputValueToPin2 = T;
	polarity = !polarity;
}
