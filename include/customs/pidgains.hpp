#pragma once
#include "lemlib/chassis/chassis.hpp"

// PID
extern lemlib::ControllerSettings linearController;
extern lemlib::ControllerSettings angularController;

// ExpoGains
extern lemlib::ExpoDriveCurve throttleCurve;
extern lemlib::ExpoDriveCurve steerCurve;