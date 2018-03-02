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

// dowels
DOWEL_L = 3.175;
DOWEL_W = 3.175;
DOWEL_H = 10;
DOWEL_XY_BUFFER_ZONE = 5.175;

// Arduino
ARDUINO_L = 68.961;
ARDUINO_W = 53.594;
ARDUINO_H = 15.1892; // height from usb input to lowest soldering on bottom

ARDUINO_PCB_L = 68.961;
ARDUINO_PCB_W = 53.594;
ARDUINO_PCB_H = 5.588;

ARDUINO_BOLT_HOLE_D = 3.10;
ARDUINO_BOLT_HOLE_1_X_OFFSET = 6.15 + ARDUINO_BOLT_HOLE_D / 2;
ARDUINO_BOLT_HOLE_1_Y_OFFSET = 0.91 + ARDUINO_BOLT_HOLE_D / 2;
ARDUINO_BOLT_HOLE_2_X_OFFSET = 1.09 + ARDUINO_BOLT_HOLE_D / 2;
ARDUINO_BOLT_HOLE_2_Y_OFFSET = ARDUINO_PCB_L - 12.27 - ARDUINO_BOLT_HOLE_D / 2;
ARDUINO_BOLT_HOLE_3_X_OFFSET = 34.1376 + ARDUINO_BOLT_HOLE_D / 2;
ARDUINO_BOLT_HOLE_3_Y_OFFSET = 1.09 + ARDUINO_BOLT_HOLE_D / 2;


ARDUINO_PINS_H = 10.3886-ARDUINO_PCB_H; // height of pins coming off board
ARDUINO_PINS_L = 47.752; // this is the longest length for the pins on the right side

// the pins and pcb measurements are there just in case you need them for the arduino

// 32 mm wheel
32_MM_WHEEL_D = 32.309;
32_MM_WHEEL_H = 6.477;
32_MM_WHEEL_NUB_H = 2.286;
32_MM_WHEEL_NUB_D = 6.071;

// LED
LED_CASE_D = 5.334;
LED_CASE_H = 8.89;
LED_LEAD_D = 0.508;
LED_LEAD_SHORT_H = 26;
LED_LEAD_LONG_H = 28;
LED_LEAD_OFFSET = 1;

MODIFIED_LED_LEAD_D = 1;

// Motor
MOTOR_SHAFT_D = 3;
MOTOR_SHAFT_H = 9.96;
MOTOR_BODY_L = 29.01;
MOTOR_BODY_W = 9.9;
MOTOR_BODY_H = 11.96;

// Plate
PLATE_L = ARDUINO_L;
PLATE_W = ARDUINO_W;
PLATE_H = 0.1;

// Sensor
SENSOR_BARREL_D = 16.002;
SENSOR_BARREL_H = 12.2682;
SENSOR_PCB_L = 20.574;
SENSOR_PCB_W = 45.339;
SENSOR_PCB_H = 3.302;

SENSOR_CAP_L = 10.77;
SENSOR_CAP_W = 4.98;
SENSOR_CAP_H = 3.35;

SENSOR_SOLDER_JOINT_L = 9.75;
SENSOR_SOLDER_JOINT_W = 3.05;
SENSOR_SOLDER_JOINT_H = 1.83;

SENSOR_TOTAL_H = SENSOR_BARREL_H + SENSOR_PCB_H;
// 41.8084 is the length from the left barrel to the right barrel
// subtract 1/2 D from both sides to get the foci.
SENSOR_DISTANCE_BW_BARREL_FOCI = 41.8084 - SENSOR_BARREL_D;

// Sensor Pins
SENSOR_PINS_H = 4.4196-SENSOR_PCB_H;
SENSOR_PINS_L = 8.6106;
SENSOR_PINS_W = 10.2362;
SENSOR_PINS_OFFSET = 3; // amount that pins overlap PCB

// Tenergy battery
TENERGY_W = 36.500;
TENERGY_H = 18.948;
TENERGY_L = 69.698;

// Pushbutton
PUSHBUTTON_BODY_L = 6;
PUSHBUTTON_BODY_W = PUSHBUTTON_BODY_L;
PUSHBUTTON_BODY_H = 3;
PUSHBUTTON_CYLINDER_D = 3.5;
PUSHBUTTON_CYLINDER_H = 1;

// H-bridge
H_BRIDGE_LOWER_L = 43.256;
H_BRIDGE_LOWER_W = H_BRIDGE_LOWER_L;
H_BRIDGE_LOWER_H = 14.376;
H_BRIDGE_UPPER_W = 23.012;
H_BRIDGE_UPPER_L = 15.951;
H_BRIDGE_UPPER_H = 28.93;

// Caster ball
CASTER_BALL_HOUSING_L = 19.152;
CASTER_BALL_HOUSING_W = 12.217;
CASTER_BALL_TOTAL_H = 10.084;
CASTER_BALL_HOUSING_H = 7.417;
CASTER_BALL_D = 9.525;
CASTER_BALL_SCREW_HOLE_D = 2.5;
CASTER_BALL_EDGE_TO_HOLE_L = 1.85;

// Wall segment
WALL_SEGMENT_H = 50;
WALL_SEGMENT_L = 167;
WALL_SEGMENT_W = 8;
