#include "main.h"
#include "customs/roboports.hpp"
#include "customs/autons.hpp"
#include "customs/autonselector.hpp"
#include "customs/subsystems.hpp"
#include "customs/RCL.hpp"

// Where Do You want the robot to end? (This is static for position logging)
double desiredX = 28;
double desiredY = 47;
double desiredTheta = 90;

// Initialize the robot code
void initialize() {
    pros::lcd::initialize(); // Initialize brain screen
    chassis.calibrate(); // calibrate sensors
    RclMain.startTracking(); // start RCL tracking

// Thread to for brain screen and position logging
pros::Task screenTask([&]() {
    while (true) {
        // Set background
        pros::screen::set_pen(pros::c::COLOR_BLACK);
        pros::screen::fill_rect(0, 0, 480, 240);
        // Desired vs current position text
        pros::screen::set_pen(pros::c::COLOR_WHITE);
        pros::screen::print(TEXT_MEDIUM, 10, 10,  "Desired pose            Current pose");
        pros::screen::print(TEXT_MEDIUM, 10, 40,  "X: %.3f               X: %.3f", desiredX, chassis.getPose().x);
        pros::screen::print(TEXT_MEDIUM, 10, 70,  "Y: %.3f               Y: %.3f", desiredY, chassis.getPose().y);
        pros::screen::print(TEXT_MEDIUM, 10, 100, "Theta: %.3f           Theta: %.3f", desiredTheta, chassis.getPose().theta);
        // Delay to prevent cpu overload
        pros::delay(50);
    }
});
}

// Disabled
void disabled() {}

// Competition initialize
void competition_initialize() { 
    const char* autons[] = {
        "10 Ball Right",
        "6 Ball Right",
        "6 Ball Left",
        "Skills",
        ""
    };
    selector::init(360, 1, autons);
}

//Declare path assets (located in the static folder)
ASSET(PathLoader_txt); // The ASSET (PathLoader_txt) '.' replaced with "_" to make c++ happy

// Autonomous
void autonomous() {
    tenBR(chassis); 
    // int a = selector::getAuton();
    // switch (a) {
    //     case 1:  tenBR(chassis); break;
    //     case 2:  sixBR(chassis); break;
    //     case 3:  sixBL(chassis); break;
    //     case 0:  skillsA(chassis); break;
    //     case -1: tenBR(chassis); break;
    //     case -2: sixBR(chassis); break;
    //     case -3: sixBL(chassis); break;
    // }
}

// Operator Control
void opcontrol() {
    while (true) {
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        chassis.arcade(leftY, rightX);
            setIntakes(); 
            setLoader(); 
            setDescore();
        pros::delay(10);
    }
}