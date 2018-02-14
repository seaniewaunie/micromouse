// File: side_sensor_system.scad
// Author: Aksel Thomas
// Date: 2/13/2018

// This file contains the side sensors.

include <model_constants.scad>
include <sensor.scad>

SIDE_SENSOR_HEIGHT_OFFSET = 25;
SIDE_SENSOR_FORE_AFT_OFFSET = -7;

module side_sensor_system(xt = 0, yt = 0, zt = 0) {
    translate([xt, yt, zt]) {
        // Right sensor
        rotate([90, 180, 0]) {
            sensor(xt = -SIDE_SENSOR_FORE_AFT_OFFSET, yt = -SIDE_SENSOR_HEIGHT_OFFSET, zt = 22);
        }

        // Left sensor
        rotate([270, 0, 0]) {
            sensor(xt = SIDE_SENSOR_FORE_AFT_OFFSET, yt = -SIDE_SENSOR_HEIGHT_OFFSET, zt = 22);
        }
    }
}
