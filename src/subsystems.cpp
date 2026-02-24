#include "customs/subsystems.hpp"
#include "customs/roboports.hpp"

//Intake op-control
void setIntakes() {
    static int lowVelocityCounter = 0;

    if (controller.get_digital(DIGITAL_L2) && controller.get_digital(DIGITAL_L1)) {
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

        double intakeVelocity = fabs(Intake.get_actual_velocity());
        if (intakeVelocity < 20) lowVelocityCounter++;
        else lowVelocityCounter = 0;

        if (lowVelocityCounter > 15)
            Intake.move_velocity(-600);
        else
            Intake.move_velocity(600);

    } else {
        Intake.move_velocity(0);
        Redirect.move_velocity(0);
        Sort.move_velocity(0);
    }
}

//Loader op-control
void setLoader() {
    static bool LoaderState = false;
    static bool lastR2 = false;
    static uint32_t cooldown = 0;
    const uint32_t delay = 10;

    bool current = controller.get_digital(DIGITAL_R2);

    if (current && !lastR2 && pros::millis() - cooldown > delay) {
        LoaderState = !LoaderState;
        LoaderState ? Loader.extend() : Loader.retract();
        cooldown = pros::millis();
    }

    lastR2 = current;
}

// Descore op-control
void setDescore() {
    static bool DescoreState = false;
    static bool lastR1 = false;
    static uint32_t cooldown = 0;
    const uint32_t delay = 10;

    bool current = controller.get_digital(DIGITAL_R1);

    if (current && !lastR1 && pros::millis() - cooldown > delay) {
        DescoreState = !DescoreState;
        DescoreState ? Descore.extend() : Descore.retract();
        cooldown = pros::millis();
    }

    lastR1 = current;
}
