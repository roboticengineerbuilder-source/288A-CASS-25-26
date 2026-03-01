#pragma once

#include "pros/motors.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "lemlib/api.hpp"
#include "pros/distance.hpp"
#include "customs/RCL.hpp"

// Controller
extern pros::Controller controller;

// Drivetrain motors
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

// Distance Sensors
extern pros::Distance back_dist;
extern pros::Distance right_dist;
extern pros::Distance front_dist;
extern pros::Distance left_dist;

// RCL setup
extern RclSensor front_rcl;
extern RclSensor right_rcl;
extern RclSensor back_rcl;
extern RclSensor left_rcl;
extern RclTracking RclMain;

// Loaders (Push-Back VEX)
extern Circle_Obstacle redUpLoader;
extern Circle_Obstacle redDownLoader;
extern Circle_Obstacle blueUpLoader;
extern Circle_Obstacle blueDownLoader;

// Goal legs (Push-Back VEX)
extern Circle_Obstacle upLongGoalLeft;
extern Circle_Obstacle upLongGoalRight;
extern Circle_Obstacle downLongGoalLeft;
extern Circle_Obstacle downLongGoalRight;
extern Circle_Obstacle centerGoals;

// Disable Line for the autonomous period
extern Line_Obstacle disableLine;

// Intake motors
extern pros::Motor Intake;
extern pros::Motor Redirect;
extern pros::Motor Sort;

// Pneumatics
extern pros::adi::Pneumatics Loader;
extern pros::adi::Pneumatics Descore;

// Tracking wheels
extern pros::Rotation verticalEnc1;
extern pros::Rotation verticalEnc2;
extern pros::Rotation horizontalEnc2;

extern lemlib::TrackingWheel vertical1;
extern lemlib::TrackingWheel vertical2;
extern lemlib::TrackingWheel horizontal1;

// Drivetrain and controllers
extern lemlib::Drivetrain drivetrain;
extern lemlib::ControllerSettings linearController;
extern lemlib::ControllerSettings angularController;
extern lemlib::OdomSensors sensors;
extern lemlib::ExpoDriveCurve throttleCurve;
extern lemlib::ExpoDriveCurve steerCurve;
extern lemlib::Chassis chassis;