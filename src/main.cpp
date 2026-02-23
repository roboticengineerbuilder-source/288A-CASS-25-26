#include "main.h"
#include "customs/roboports.hpp"
#include "customs/autons.hpp"
#include "customs/autonselector.hpp"
#include "customs/RCL.hpp"

// Where Do You want the robot to end? (This is static for position logging)
double desiredX = 28;
double desiredY = 47;
double desiredTheta = 90;

// Initialize the robot code
void initialize() {
    pros::lcd::initialize(); // Initialize brain screen
chassis.calibrate(); // calibrate sensors
    // RclMain.startTracking();

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
    RCLTest(chassis); 
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

// Piston State memory
    bool LoaderState = false; // variable to keep track of Loader state
	bool DescoreState = false; // variable to keep track of Descore state

// Controller edge detection memory
    bool lastR2 = false; // last state of R2 button
    bool lastR1 = false; // last state of R1 button

// Cooldown timers (non-blocking)
    uint32_t loaderCooldown = 0;
    uint32_t descoreCooldown = 0;
    const uint32_t toggleDelay = 10;

    while (true) {
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        chassis.arcade(leftY, rightX);
    if (controller.get_digital(DIGITAL_L2 ) && controller.get_digital(DIGITAL_L1)) {
            Intake.move_velocity(600);
			Redirect.move_velocity(-600);
			Sort.move_velocity(600);
    } else if (controller.get_digital(DIGITAL_L2)) {
            Intake.move_velocity(-600);
			Redirect.move_velocity(600);
			Sort.move_velocity(Redirect.get_actual_velocity());
    } else if (controller.get_digital(DIGITAL_L1)) {
			Redirect.move_velocity(Sort.get_actual_velocity());
			Sort.move_velocity(-600);
            static int lowVelocityCounter = 0;
            double intakeVelocity = fabs(Intake.get_actual_velocity());
            if (intakeVelocity < 20) { 
            lowVelocityCounter++;
            } else {
            lowVelocityCounter = 0;
            }
            if (lowVelocityCounter > 15) {  // If velocity is low for 150ms, intake jammed
            Intake.move_velocity(-600);  // reverse intake to clear jam
            } else {
            Intake.move_velocity(600);   // intake
        }
    } else {
            Intake.move_velocity(0);
			Redirect.move_velocity(0);
			Sort.move_velocity(0);
    }
    bool currentR2 = controller.get_digital(DIGITAL_R2);
        if (currentR2 && !lastR2 && pros::millis() - loaderCooldown > toggleDelay) {
            LoaderState = !LoaderState;
        if (LoaderState)
            Loader.extend();
        else
            Loader.retract();
        loaderCooldown = pros::millis();
    }
        lastR2 = currentR2;
    bool currentR1 = controller.get_digital(DIGITAL_R1);
        if (currentR1 && !lastR1 && pros::millis() - descoreCooldown > toggleDelay) {
            DescoreState = !DescoreState;
        if (DescoreState)
            Descore.extend();
        else
            Descore.retract();
        descoreCooldown = pros::millis();
    }
        lastR1 = currentR1;
        pros::delay(10);
    }
}