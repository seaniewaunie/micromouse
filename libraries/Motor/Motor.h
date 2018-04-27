/*
 * Motor.h
 *
 *  Created on: Feb 19, 2018
 *      Author: Erfan
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "Arduino.h"

class Encoder {

public:

	static const int CPR = 297;	//cycles per revolution
	static const int EPC = 4; //events per cycle
	static const int EPR = CPR*EPC; //events per revolution

	int encoderPin;		//digital input on Arduino for which encoder A input is connected
	volatile signed long int encoderPos = 0;		//variable to keep track of encoder position

	Encoder();								//default constructor
	Encoder(int);				//constructor with arguments to specify digital pins
	virtual ~Encoder();
	signed long int getEncoderPosition();
	void resetEncoderPosition();
	void encoderEvent_ISR();		//Interrupt Service Routine for event on encoder A pin
};

namespace encoder_interrupt_functions {
	void leftEncoderEvent_ISR_Wrapper();
	void rightEncoderEvent_ISR_Wrapper();
}

class Motor {

public:

	static constexpr float wheel_diameter = 3.2;
	static constexpr float wheel_circum = PI * wheel_diameter;

	Encoder encoder;

	Motor();
	Motor(int,int,int,int);			//Motor with encoder
	virtual ~Motor();
	void spinMotor(int);
	void reverseDirection();
	void resetDirection();

private:

	int enablePin;
	int inputPin1;
	int inputPin2;
	int inputValueToPin1;
	int inputValueToPin2;
};

#endif /* MOTOR_H_ */
