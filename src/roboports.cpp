#include "customs/roboports.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/distance.hpp"
#include "customs/RCL.hpp"

// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Drivetrain Motor Groups
pros::MotorGroup leftMotors({11, -12, 13}, pros::MotorGearset::blue); // left motor group - ports 11 (forward), 12 (reversed), 13 (forward)
pros::MotorGroup rightMotors({-14, 15, -16}, pros::MotorGearset::blue); // right motor group - ports 14 (reversed), 15 (forward), 16 (reversed)

// Inertial Sensor
pros::Imu imu(2); // Inertial sensor, port 2

// Distance Sensors
inline pros::Distance back_dist(4);
inline pros::Distance right_dist(18);
inline pros::Distance front_dist(3);
inline pros::Distance left_dist(7);

// Rcl setup
inline RclSensor front_rcl(&front_dist, -6.75, 3.75, 0.0, 15.0);  // 6.75 inch to the left; 3.75 inches to the front; facing front
inline RclSensor right_rcl(&right_dist, 5, 4.25, 90.0, 15.0);  // 5 inches to the right; 4.25 vertical offset; facing right
inline RclSensor back_rcl(&back_dist, -5.25, -3.5, 180.0, 15.0);   // 5.25 inches to the left; 3.5 inches to the back; facing back
inline RclSensor left_rcl(&left_dist, -5, 4.25, 270.0, 15.0);   // 5 inches to the left; 4.25 vertical offset, facing left
inline RclTracking RclMain(&chassis, 30, true, 0.5, 4.0, 10.0, 6.0, 20);

// loaders (Push-Back)
inline Circle_Obstacle redUpLoader(-67.5, 46.5, 3);
inline Circle_Obstacle redDownLoader(-67.5, -46.5, 3);
inline Circle_Obstacle blueUpLoader(67.5, 46.5, 3);
inline Circle_Obstacle blueDownLoader(67.5, -46.5, 3);

// Goal legs (Push-Back)
inline Circle_Obstacle upLongGoalLeft(-21, 47.5, 4);
inline Circle_Obstacle upLongGoalRight(21, 47.5, 4);
inline Circle_Obstacle downLongGoalLeft(-21, -47.5, 4);
inline Circle_Obstacle downLongGoalRight(21, -47.5, 4);
inline Circle_Obstacle centerGoals(0, 0, 5);

// Disable Line for the autonomous period
inline Line_Obstacle disableLine(0, FIELD_NEG_HALF_LENGTH, 0, FIELD_HALF_LENGTH);

// Motors
pros::Motor Intake((17)); // Intake motor, port 17
pros::Motor Redirect((19)); // Intake motor, port 19
pros::Motor Sort((20)); // Intake motor, port 20

//Pneumatics
pros::adi::Pneumatics Loader('B',false); // Loader piston, starts retracted, extends when the ADI port is high
pros::adi::Pneumatics Descore('C',false); // Descore piston, starts retracted, extends when the ADI port is high

// vertical tracking wheel encoder
pros::Rotation verticalEnc1(1); // Rotation sensor, port 1

// horizontal tracking wheel encoder
pros::Rotation horizontalEnc1(10); // Rotation sensor, port 10

// vertical tracking wheel
lemlib::TrackingWheel vertical1(&verticalEnc1, lemlib::Omniwheel::NEW_2, 1.375); //  2.00" diameter, 1.375" offset, left of the robot (negative)

// vertical tracking wheel
lemlib::TrackingWheel horizontal1(&horizontalEnc1, lemlib::Omniwheel::NEW_2, -4.25); //  2.00" diameter, 4.25" offset, back of the robot (negative)

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              12, // 12 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 2.75" omnis
                              600, // drivetrain rpm is 600
                              8 // horizontal drift is 8. If we did not have traction wheels, it would have been 2
);

// sensors for odometry
lemlib::OdomSensors sensors(&vertical1, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal1, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

// angle calculation
    // theda = (change in l - change in r)/(t1 + tr)

// global transformation
    // x1 = x0 + change in x * cos(theda0) - change in y * sin(theda0)
    // y1 = y0 + change in y * sin(theda0) + change in y * cos(theda0)

// tracking wheel delta
    //change in s = (rotation * wheel diamether * pi)/ gear ratio

// heading
    // theda(new) = theda(old) + change in theda