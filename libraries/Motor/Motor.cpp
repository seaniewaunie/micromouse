/*
 * Motor.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Erfan
 */

#include "Motor.h"
#include "Locomotion.h"

Encoder::Encoder() {
	//do nothing
}

Encoder::Encoder(int pin) {

	this->encoderPin = pin;
	/* Arduino Setting Code */
	pinMode(encoderPin, INPUT_PULLUP);
	/* Add Interrupts in Arduino Setup! */
	encoderPos = 0;
}

Encoder::~Encoder() {
	//do nothing
}

signed long int Encoder::getEncoderPosition() {
	return encoderPos;
}

void Encoder::resetEncoderPosition() {
	encoderPos = 0;
}

void Encoder::encoderEvent_ISR() {
	this->encoderPos++;
}

namespace encoder_interrupt_functions {

	void leftEncoderEvent_ISR_Wrapper() {
		lMotor->encoder.encoderEvent_ISR();
	}

	void rightEncoderEvent_ISR_Wrapper() {
		rMotor->encoder.encoderEvent_ISR();
	}

}


Motor::Motor() {
	//do nothing
}

Motor::Motor(int enablePin, int inputPin1, int inputPin2, int ePin) {
	this->enablePin = enablePin;
	this->inputPin1 = inputPin1;
	this->inputPin2 = inputPin2;

		/*Arduino Setting */
	pinMode(enablePin, OUTPUT);
	pinMode(inputPin1, OUTPUT);
	pinMode(inputPin2, OUTPUT);

		//default direction of motor is clockwise
	this->inputValueToPin1 = 1;
	this->inputValueToPin2 = 0;

	digitalWrite(inputPin1,inputValueToPin1);
	digitalWrite(inputPin2,inputValueToPin2);

	encoder = Encoder(ePin);
}

Motor::~Motor() {
	//do nothing
}

void Motor::spinMotor(int dutyCycle) {
	analogWrite(this->enablePin,dutyCycle);
}

void Motor::reverseDirection()  {
	int T = inputValueToPin1;
	inputValueToPin1 = inputValueToPin2;
	inputValueToPin2 = T;

	digitalWrite(inputPin1,inputValueToPin1);
	digitalWrite(inputPin2,inputValueToPin2);
}

void Motor::resetDirection() {
	inputValueToPin1 = 1;
	inputValueToPin2 = 0;
	digitalWrite(inputPin1,inputValueToPin1);
	digitalWrite(inputPin2,inputValueToPin2);
}




