// File: h_bridge.scad
// Author: Aksel Thomas
// Date: 1/31/2018

include <model_constants.scad>;

module h_bridge(xt = 0, yt = 0, zt = 0) {
    color([0.2, 0.2, 0.2,]) {
        translate([xt, yt, zt]) {
            cube([H_BRIDGE_LOWER_L, H_BRIDGE_LOWER_W, H_BRIDGE_LOWER_H]);
            translate([H_BRIDGE_LOWER_L - H_BRIDGE_UPPER_L, H_BRIDGE_LOWER_W / 2 - H_BRIDGE_UPPER_W / 2, 0]) {
                cube([H_BRIDGE_UPPER_L, H_BRIDGE_UPPER_W, H_BRIDGE_UPPER_H]);
            }
        }
    }
}
