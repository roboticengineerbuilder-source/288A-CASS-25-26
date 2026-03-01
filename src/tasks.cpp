#include "main.h"
#include "customs/roboports.hpp"
#include "customs/tasks.hpp"

bool antiJamEnabled = true;

void antiJamTask(void*) {
    int lowVelocityCounter = 0;

    while (true) {
        // If intake is reversed, DO NOT anti-jam
        if (controller.get_digital(DIGITAL_L2)) {
            lowVelocityCounter = 0;
            pros::delay(10);
            continue;
        }

        // Intake always runs forward unless jammed
        double intakeVelocity = fabs(Intake.get_actual_velocity());
        if (intakeVelocity < 20)
            lowVelocityCounter++;
        else
            lowVelocityCounter = 0;
        if (lowVelocityCounter > 15) {
            Intake.move_velocity(-600);
        } else {
            Intake.move_velocity(600);
        }
        pros::delay(50);
    }
}

void startAntiJam() { 
    antiJamEnabled = true; 
} 

void stopAntiJam() {
    antiJamEnabled = false; 
}
