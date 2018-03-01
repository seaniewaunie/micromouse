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

	void encoderEventA_ISR();		//Interrupt Service Routine for event on encoder A pin
	void encoderEventB_ISR();		//Interrupt Service Routine for event on encoder B pin

	inline const int getEncoderAPin() { return encoderAPin; }
	inline const int getEncoderBPin() { return encoderBPin; }

	signed long int getEncoderPosition();

private:

	int encoderAPin;		//digital input on Arduino for which encoder A input is connected
	int encoderBPin;		//digital input on Arduino for which encoder B input is connected

	volatile signed long int encoderPos = 0;		//variable to keep track of encoder position
	volatile unsigned char inputMask = 0;									//mask to extract vital bits from the poll bytes

};


class Motor {
public:

	static const float wheel_radius = 0.40;
	static const float wheel_circum = 2 * PI * wheel_radius;

	Motor();
	Motor(int,int,int);							//Motor w/o encoder
	Motor(int,int,int,int,int);			//Motor with encoder
	virtual ~Motor();

	void spinMotor(int);
	/*Control Interface to Outside World */
	void moveStraight(float distance = 18.0);
	void turnLeft(float distance = 6.4);
	void turnRight(float distance = 6.4);
	inline void makeUTurn() { turnRight(); turnRight(); }

	inline const bool getPolarity() { return polarity; }
	void reversePolarity();

	Encoder encoder;
private:

	int enablePin;
	int inputPin1;
	int inputValueToPin1;
	int inputPin2;
	int inputValueToPin2;

	bool polarity;		//0 for positive, 1 for negative
};




#endif /* MOTOR_H_ */
