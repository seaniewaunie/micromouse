#ifndef __LOCOMOTION_H__
#define __LOCOMOTION_H__

#include "Motor.h"
#include "Sensor.h"
#include "config.h"
#include "PID.h"
#include "Arduino.h"

extern Motor *lMotor;
extern Motor *rMotor;

extern Sensor* fSensor;
extern Sensor* lSensor;
extern Sensor* rSensor;

extern PID *leftEncoderPID;
extern PID *rightEncoderPID;

class Locomotion {

public:

	//static constexpr float encoderSampleTime = 50; continuous sampling

	Locomotion();
	~Locomotion();
	void goForward();
	void turnRight();
	void turnLeft();
	void makeUTurn();
};

#endif


