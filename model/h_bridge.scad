// File: h_bridge.scad
// Author: Aksel Thomas
// Date: 1/31/2018

include <model_constants.scad>;

module h_bridge(xt = 0, yt = 0, zt = 0) {
    color([0.2, 0.2, 0.2,]) {
        translate([xt, yt, zt]) {
            cube([H_BRIDGE_L, H_BRIDGE_W, H_BRIDGE_H]);
        }
    }
}