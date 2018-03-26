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

const int Encoder::getEncoderAPin() {
	return encoderAPin;
}

const int Encoder::getEncoderBPin() {
	return encoderBPin;
}

signed long int Encoder::getEncoderPosition() {
	return encoderPos;
}

void Encoder::resetEncoderPosition() {
	encoderPos = 0;
}

void Encoder::encoderEventA_ISR() {
	if((PIND & inputMask) == inputMask) {
		this->encoderPos--;	//counter clockwise
	}
	else {
		this->encoderPos++;	//clockwise
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

namespace encoder_interrupt_functions {

	void leftEncoderEventA_ISR_Wrapper() {
		lMotor->encoder.encoderEventA_ISR();
	}

	void leftEncoderEventB_ISR_Wrapper() {
		lMotor->encoder.encoderEventB_ISR();
	}

	void rightEncoderEventA_ISR_Wrapper() {
		rMotor->encoder.encoderEventA_ISR();
	}

	void rightEncoderEventB_ISR_Wrapper() {
		rMotor->encoder.encoderEventB_ISR();
	}
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
	this->inputValueToPin1 = 1;
	this->inputValueToPin2 = 0;

	digitalWrite(inputPin1,inputValueToPin1);
	digitalWrite(inputPin2,inputValueToPin2);

	encoder = Encoder();
}

Motor::Motor(int enablePin, int inputPin1, int inputPin2, int APin, int BPin) {
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

	encoder = Encoder(APin,BPin);
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




