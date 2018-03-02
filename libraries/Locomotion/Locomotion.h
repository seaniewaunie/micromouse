#ifndef __LOCOMOTION_H__
#define __LOCOMOTION_H__

#include "Motor.h"
#include "Sensor.h"
#include "config.h"
#include "PID.h"
#include "Arduino.h"

extern Motor *lMotor;
extern Motor *rMotor;

extern Sensor* lSensor;
extern Sensor* rSensor;

extern PID *encoderPID;
extern PID *sensorPID;

class Locomotion {

public:

	static constexpr float encoderSampleTime = 300;
	static constexpr float sensorSampleTime = 500;

	Locomotion();
	~Locomotion();
	void goForward();
	void turnRight();
	void turnLeft();
	void makeUTurn();

};

#endif
