// File: model_constants.scad
// Author: Aksel Thomas
// Date: 12/18/2017

/********************
LETTER KEY
W   =   WIDTH
L   =   LENGTH
H   =   HEIGHT
D   =   DIAMETER
BW  =   BETWEEN

NOTE 1:
Cylinders are defined by two dimensions: D and H.

NOTE 2:
All units are in millimeters.
********************/

// Arduino
ARDUINO_L = 70;
ARDUINO_W = 54;
ARDUINO_H = 15;

// Back wheel
BACK_WHEEL_D = 72;
BACK_WHEEL_H = 8;
BACK_WHEEL_NUB_D = 7;
BACK_WHEEL_NUB_H = 5;

// LED
LED_CASE_D = 6;
LED_CASE_H = 9;
LED_LEAD_D = 0.5;
LED_LEAD_SHORT_H = 26;
LED_LEAD_LONG_H = 28;
LED_LEAD_OFFSET = 1;

// Motor
MOTOR_SHAFT_D = 3;
MOTOR_SHAFT_H = 10;
MOTOR_BODY_L = 31;
MOTOR_BODY_W = 10;
MOTOR_BODY_H = 12;

// Plate
PLATE_L = ARDUINO_L;
PLATE_W = ARDUINO_W;
PLATE_H = 0.1;

// Sensor
SENSOR_BARREL_D = 16;
SENSOR_BARREL_H = 12;
SENSOR_PCB_L = 21;
SENSOR_PCB_W = 46;
SENSOR_PCB_H = 3;
SENSOR_TOTAL_H = SENSOR_BARREL_H + SENSOR_PCB_H;
SENSOR_DISTANCE_BW_BARREL_FOCI = 30;