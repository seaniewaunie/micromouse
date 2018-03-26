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

	Encoder();								//default constructor
	Encoder(int, int);					//constructor with arguments to specify digital pins
	virtual ~Encoder();

	const int getEncoderAPin();
	const int getEncoderBPin();

	void setEncoderAPin(int);
	void setEncoderBPin(int);

	signed long int getEncoderPosition();
	void resetEncoderPosition();

	void encoderEventA_ISR();		//Interrupt Service Routine for event on encoder A pin
	void encoderEventB_ISR();		//Interrupt Service Routine for event on encoder B pin

private:

	int encoderAPin;		//digital input on Arduino for which encoder A input is connected
	int encoderBPin;		//digital input on Arduino for which encoder B input is connected

	volatile signed long int encoderPos = 0;		//variable to keep track of encoder position
	volatile unsigned char inputMask = 0;									//mask to extract vital bits from the poll bytes
};

namespace encoder_interrupt_functions {

	void leftEncoderEventA_ISR_Wrapper();
	void leftEncoderEventB_ISR_Wrapper();
	void rightEncoderEventA_ISR_Wrapper();
	void rightEncoderEventB_ISR_Wrapper();

}

class Motor {
public:

	static constexpr float wheel_radius = 1.6;
	static constexpr float wheel_circum = 2 * PI * wheel_radius;

	Motor();
	Motor(int,int,int);							//Motor w/o encoder
	Motor(int,int,int,int,int);			//Motor with encoder
	virtual ~Motor();

	void spinMotor(int);
	void reverseDirection();
	void resetDirection();

	Encoder encoder;

private:

	int enablePin;
	int inputPin1;
	int inputPin2;
	int inputValueToPin1;
	int inputValueToPin2;

};

#endif /* MOTOR_H_ */
