#include "customs/autons.hpp"
#include "customs/roboports.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "customs/RCL.hpp"
#include "pros/rtos.hpp"

void tenBR(lemlib::Chassis &chassis) {
 // First set the robot's starting pose
    chassis.setPose(46, 14, 0);
    RclMain.setRclPose( lemlib::Pose(46,14,0));
    // Robot moves to a pose in between the loader and long goal
    chassis.moveToPose(46,38,0, 1000); // moves to (46, 40) with a 1.5 second timeout
    // Robot waits for .2 seconds to avoid cpu overload
        pros::delay(200); 
    Descore.extend();
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
    // Robot waits for .2 seconds to avoid cpu overload
        pros::delay(200);
    Loader.extend();
    // Robot turns to face the loader
    chassis.swingToHeading(90,lemlib::DriveSide::RIGHT,400);
    // Robot moves to the loader and constantly drives into it to ensure proper loading
    chassis.moveToPoint(80,46, 800,  {.maxSpeed = 60, .minSpeed = 30}, false); // move to (80, 46) with a 1 second timeout
    RclMain.updateBotPose();
    // Robot moves backwards to the goal
    chassis.moveToPose(20,47, 90, 2000,  {.forwards=false, .maxSpeed = 100, .minSpeed = 20}); // move back to (20, 47) with a 2 second timeout
    // Robot waits for .8 seconds to avoid losing blocks
        pros::delay(800);
    // Robot scores the blocks in the long goal
    Descore.retract();
    Loader.retract();
    // reverse intake to unjam any blocks
    Intake.move_velocity(-100);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(50);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
    RclMain.startAccumulating();
    // Robot waits for 1.5 seconds to ensure scoring is complete
        pros::delay(1500);
    RclMain.stopAccumulating();
    RclMain.updateBotPose();
    Descore.extend();
    Loader.retract();
    // Robot turns to face center blocks
    chassis.turnToPoint(24,24,800,{.minSpeed = 40}); // swing to (24, 24) with a .8 second timeout
    // Robot moves to pick up center blocks
    chassis.moveToPose(24,24,180, 2000,  {.maxSpeed = 80, .minSpeed = 5}); // move to (20, 20) with a 3 second timeout
    RclMain.updateBotPose();
    // Robot moves to other side to pick up center blocks
    chassis.moveToPoint(24,-24, 2000); // move to (25,-25) with a 2 second timeout
        pros::delay(900);
    Loader.extend();
    // Robot moves backwards to mid goal
    RclMain.updateBotPose();
        pros::delay(200);
    chassis.moveToPose(8.5,-9.5,135, 2000,  {.forwards=false}); // move to (8.5, -8.5) with a 2 second timeout
        pros::delay(850);
   // Sort reverse to score
    Descore.retract();
    Sort.move_velocity(-200);
        pros::delay(150);
    Redirect.move_velocity(-100);
    Sort.move_velocity(300);
        pros::delay(400);
    RclMain.updateBotPose();
    chassis.moveToPoint(46,-46,2500); // move to (46, -46) with a 2.5 second timeout
    Redirect.move_velocity(600);
    Sort.move_velocity(-600);
    Descore.extend();
        pros::delay(400);
    Redirect.move_velocity(-200);
    Sort.move_velocity(-200);
    // Robot moves to the loader and constantly drives into it to ensure proper loading
    chassis.moveToPose(80,-46,90, 1200,  {.maxSpeed = 60,.minSpeed = 30}, false); // move to (80, 46) with a 1 second timeout
    // Robot moves backwards to the goal
    chassis.moveToPose(20,-47, 90, 1800,  {.forwards=false, .minSpeed = 20}); // move back to (20, 47) with a 2 second timeout
    // Robot waits for .7 seconds to avoid losing blocks
        pros::delay(700);
    Intake.move_velocity(-600);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(200);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
    // Robot scores the blocks in the long goal
    Descore.retract();
    Loader.retract();
}

void sixBR(lemlib::Chassis &chassis) {
    // First set the robot's starting pose
    chassis.setPose(46, 14, 0);
    RclMain.setRclPose( lemlib::Pose(46,14,0));
    // Robot waits for .2 seconds to avoid miscalibration
        // pros::delay(200);
    // Robot moves to a pose in between the loader and long goal
    chassis.moveToPose(46,38,0, 1500); // moves to (46, 40) with a 1.5 second timeout
    // Robot waits for .2 seconds to avoid cpu overload
        pros::delay(200); 
    Descore.extend();
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
    // Robot waits for .2 seconds to avoid cpu overload
        pros::delay(200);
    Loader.extend();
    // Robot turns to face the loader
    chassis.swingToHeading(90,lemlib::DriveSide::RIGHT,500);
    // Robot moves to the loader and constantly drives into it to ensure proper loading
    chassis.moveToPoint(65,46, 800,  {.forwards=true, .maxSpeed = 65, .minSpeed = 30}, false); // move to (80, 46) with a 1 second timeout
    // Robot moves backwards to the goal
    chassis.moveToPose(20,47, 90, 2000,  {.forwards=false}); // move back to (20, 47) with a 2 second timeout
    // Robot waits for .7 seconds to avoid losing blocks
        pros::delay(700);
    // Robot scores the blocks in the long goal
    Descore.retract();
    Loader.retract();
    // reverse intake to unjam any blocks
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(100);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
    RclMain.startAccumulating();
    // Robot waits for 1.5 seconds to ensure scoring is complete
        pros::delay(1500);
    RclMain.stopAccumulating();
    RclMain.updateBotPose();
    // Robot turns to face center blocks
    chassis.turnToPoint(24,24,800,{.minSpeed = 40}); // swing to (24, 24) with a .8 second timeout
    // Robot moves to center goal
    chassis.moveToPoint(20,20, 3000,  {.forwards=true, .maxSpeed = 70}); // move to (20, 20) with a 3 second timeout
        pros::delay(200);
    Loader.extend();
        pros::delay(200);
    Loader.retract();
    chassis.moveToPose(11,13,225,2500,  {.forwards=true, .maxSpeed = 80}); // move to (12, 12) with a 2.5 second timeout
        pros::delay(500);  
    // Intake (backwards)
    Intake.move_velocity(-600);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
    // sixBRush-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
        pros::delay(1200);
    chassis.moveToPose(46,38,110, 1500, {.forwards = false, .maxSpeed = 90, .minSpeed = 20}); // moves to (46, 40) with a 1.5 second timeout
    Descore.retract();
    Intake.move_velocity(0);
    Redirect.move_velocity(0);
    Sort.move_velocity(0);
    chassis.moveToPose(10,57, 90, 2000,  {.forwards=false}); // move back to (28, 60) with a 2 second timeout

}

void sixBL(lemlib::Chassis &chassis)  {
    // First set the robot's starting pose
    chassis.setPose(46, -14, 180);
    RclMain.setRclPose( lemlib::Pose(46,-14,180));
    // Robot waits for .2 seconds to avoid miscalibration
    pros::delay(200);
    // Robot moves to a pose in between the loader and long goal
    chassis.moveToPose(46,-38,180, 1800); // moves to (47, 47) with a 1.8 second timeout
    // Robot waits for .2 seconds to avoid cpu overload
        pros::delay(200); 
    // Extend descore to hold blocks in place
    Descore.extend();
    // Intake (forwards)
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
    // Robot waits for .2 seconds to avoid cpu overload
        pros::delay(250);
    // Extend loader to pick up blocks
    Loader.extend();
    // Robot waits for .9 second to allow the loader to extend
        pros::delay(900);
    // Robot turns to face the loader
    chassis.swingToHeading(90,lemlib::DriveSide::LEFT,400);
    // Robot moves to the loader and constantly drives into it to ensure proper loading
    chassis.moveToPoint(80,-46, 800,  {.forwards=true, .maxSpeed = 65, .minSpeed = 30}, false); // move to (80, 47) with a 1 second, wait until done
    RclMain.updateBotPose();
    // Robot moves backwards to the goal
    chassis.moveToPose(20,-47, 90, 2000,  {.forwards=false, .maxSpeed = 80, .minSpeed = -10}); // move back to (20, -47) with a 3000 second timeout
    // Robot waits for .8 seconds to avoid losing blocks
        pros::delay(800);
    // Robot scores the blocks in the long goal
    Descore.retract();
    Loader.retract();
    // reverse intake to unjam any blocks
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(50);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
    RclMain.startAccumulating();
    // Robot waits for 1.5 seconds to ensure scoring is complete
        pros::delay(1500);
    RclMain.stopAccumulating();
    RclMain.updateBotPose();
    Descore.extend();
    // Robot turns to face center blocks
    chassis.turnToPoint(24,-24,800,{.minSpeed = 40}); // swing to (24, 24) with a .8 second timeout
    RclMain.updateBotPose();
    // Robot moves to center goal
    chassis.moveToPoint(20,-20, 3000,  {.forwards=true, .maxSpeed = 70}); // move to (20, 20) with a 3 second timeout
        pros::delay(300);
    Loader.extend();
    pros::delay(500);
    RclMain.updateBotPose();
    // Robot moves back to center goal to score
    chassis.moveToPose(9,-9,135,2800,  {.forwards=false, .maxSpeed = 70}); // move to (12, 10) with a 5 second timeout
    chassis.waitUntilDone();
    Loader.retract();
    Descore.retract();
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(50);
    Redirect.move_velocity(-600);
    Sort.move_velocity(600);
}

void skillsA(lemlib::Chassis &chassis) {
    // First set the robot's starting pose
    chassis.setPose(47, 13.75, 0);
    // Robot moves to a pose in between the loader and long goal
    chassis.moveToPoint(47,47, 1500); // move to (47, 47) with a 1.5 second timeout
    // Robot waits for .2 seconds to avoid cpu overload
        pros::delay(200);
    Descore.extend();
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
    // Robot waits for .2 seconds to avoid cpu overload
        pros::delay(200);
    Loader.extend();
    // Robot waits for 1.5 second to allow the loader to extend
        pros::delay(1500);
    // Robot turns to face the loader (heading is 85 to avoid oversteering)
    chassis.turnToHeading(90, 1000);
    // Robot moves to the loader and constantly drives into it to ensure proper loading
    chassis.moveToPoint(70,47, 4000,  {.forwards=true, .maxSpeed = 60, .minSpeed = 50}); // move to (70, 47) with a 4 second timeout
    // Robot moves backwards to the goal
    chassis.moveToPoint(28,47, 1800,  {.forwards=false, .maxSpeed = 70}); // move back to (28, 49.5) with a 1.8 second timeout
    // Robot waits for .8 seconds to ensure alignment
    pros::delay(800);
    Descore.retract();
    Loader.retract();
    Intake.move_velocity(-300);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(400);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
    // Robot waits for 3 seconds to ensure scoring is complete
        pros::delay(3000);
    // Robot moves a safe distance away from the goal
    chassis.moveToPoint(40,47, 2000,  {.forwards=true, .maxSpeed = 50}); // move to (40, 47) with a 2 second timeout
    // Robot waits for .5 seconds to avoid missreading odom during turn
        pros::delay(500);
    // Robot turns to drive towards the other side of the field
    chassis.turnToHeading(180, 1000);
    // Robot moves to other side of the field
    chassis.moveToPoint(47,-47, 5000, {.maxSpeed = 60}); // move to (47, -51) with a 5 second timeout
    pros::delay(1000);
    Descore.extend();
    pros::delay(1000);
    Loader.extend();
    // Robot turns to face the loader (heading is 90 since no oversteering needed)
    chassis.turnToHeading(90, 1000);
    // Robot moves to the loader and constantly drives into it to ensure proper loading
    chassis.moveToPoint(70,-47, 4000,  {.forwards=true, .maxSpeed = 60, .minSpeed = 50}); // move to (70, -51) with a 4 second timeout
    // Robot moves backwards to the goal
    chassis.moveToPoint(28,-47, 1800,  {.forwards=false, .maxSpeed = 70}); // move back to (28, -50) with a 1.8 second timeout
    // Robot waits for .8 seconds to ensure alignment
        pros::delay(800);
    Descore.retract();
    Loader.retract();
    Intake.move_velocity(-300);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(400);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
    // Robot waits for 3.4 seconds to ensure scoring is complete
        pros::delay(3400);
    // Robot moves a safe distance away from the goal
    chassis.moveToPoint(40,-47, 2000); // move to (40, -48) with a 2 second timeout
        pros::delay(500);
    // Robot turns to face center field
    chassis.turnToHeading(0, 1000);
    // Robot drives to center field 
    chassis.moveToPoint(40,0, 3000,  {.forwards=true, .maxSpeed = 70}); // move to (40, -5) with a 3 second timeout
    //  Robot waits for 1.4 seconds to avoid missreading odom during turn
        pros::delay(1400);
    //  Robot turns to face parking zone
    chassis.turnToHeading(90, 2000);
    // Robot drives to parking zone
    chassis.moveToPoint(59.5,0, 1000,  {.forwards=true, .minSpeed = 80}); // move to (59.5, -5) with a 1 second timeout
    // Robot block anti-jam code
    chassis.moveToPoint(100.5,0, 600,  {.forwards=true, .maxSpeed = 90, .minSpeed = 80}); // move to (100.5, -5) with a .6 second timeout
    chassis.moveToPoint(50.5,0, 200,  {.forwards=true, .maxSpeed = 50, .minSpeed = 40}); // move to (50.5, -5) with a .2 second timeout
    chassis.moveToPoint(100,0, 600,  {.forwards=true,.maxSpeed = 50, .minSpeed = 40}); // move to (100, -5) with a .6 second timeout
    chassis.moveToPoint(50.5,0, 200,  {.forwards=true, .maxSpeed = 50, .minSpeed = 40}); // move to (50.5, -5) with a .2 second timeout
    chassis.moveToPoint(100,0, 600,  {.forwards=true,.maxSpeed = 50, .minSpeed = 40}); // move to (100, -5) with a .6 second timeout
    chassis.moveToPoint(50.5,0, 200,  {.forwards=true, .maxSpeed = 50, .minSpeed = 40}); // move to (50.5, -5) with a .2 second timeout
    chassis.moveToPoint(100,0, 1000,  {.forwards=true,.maxSpeed = 70, .minSpeed = 40}); // move to (100, -5) with a .6 second timeout
}

void skillsB(lemlib::Chassis &chassis){
    // First set the robot's starting pose
    chassis.setPose(46, 14, 0);
    RclMain.setRclPose( lemlib::Pose(46,14,0));
    RclMain.updateBotPose();
    // Delay to ensure robot pose is calculated
        pros::delay(200);
    // Robot moves to a pose in between the loader and long goal
    chassis.moveToPose(46,46,0, 1000, {.maxSpeed = 80}); // moves to (46, 46) with a 1 second timeout
    // Robot waits for .2 seconds to avoid cpu overload
        pros::delay(200); 
    Descore.extend();
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
    // Robot waits for .2 seconds to avoid cpu overload
        pros::delay(200);
    Loader.extend();
    // Robot turns to face the loader
    chassis.turnToHeading(90,1000);
    // Robot moves to the loader and constantly drives into it to ensure proper loading
    chassis.moveToPose(80,46, 90, 3000,  {.maxSpeed = 50, .minSpeed = 5}, false); // move to (80, 46) with a 2 second timeout
    RclMain.updateBotPose();
    // Intake 0 velocity to prevent jams
    Intake.move_velocity(0);
    Redirect.move_velocity(0);
    Sort.move_velocity(0);
    // Robot move to pose between wall and long goal to go to the other side of the field
    chassis.moveToPose(28,60, 90, 2000,  {.forwards=false, .minSpeed = 10}); // move back to (28, 60) with a 2 second timeout
        pros::delay(500);
    RclMain.updateBotPose();
    // Robot moves to pose on the other side of the field
    chassis.moveToPose(-40,60,90, 2000,  {.forwards=false, .maxSpeed = 60}); // move back to (-40, 60) with a 2 second timeout
    Loader.retract();
    RclMain.updateBotPose();
    chassis.turnToHeading(0, 1000);
    chassis.moveToPoint(-40,47, 2000,  {.forwards=false}); // move back to (-20, 47) with a 2 second timeout
    RclMain.updateBotPose();
    chassis.turnToHeading(270, 1000);
    chassis.moveToPoint(-20,47, 2000,  {.forwards=false}); // move back to (-20, 47) with a 2 second timeout
    // Robot waits for .6 seconds to avoid losing blocks
        pros::delay(600);
    // score with ani-jam
    Descore.retract();
    Intake.move_velocity(-600);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(100);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
        pros::delay(500);
    Intake.move_velocity(-600);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(100);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
        pros::delay(2000);
    RclMain.updateBotPose();
    Descore.extend();
    Loader.extend();
    // Robot moves to the loader and constantly drives into it to ensure proper loading
    chassis.moveToPoint(-80,46, 4000,  {.maxSpeed = 50, .minSpeed = 5}, false); // move to (-80, 46) with a 4 second timeout
    RclMain.updateBotPose();
    // Robot moves backwards to the goal
    chassis.moveToPose(-25,47,270, 2000,  {.forwards=false, .maxSpeed = 80}); // move back to (-25, 47) with a 2 second timeout
    // Robot waits for .9 seconds to avoid losing blocks
        pros::delay(900);
    // score with ani-jam
    Descore.retract();
    Intake.move_velocity(-600);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(100);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
        pros::delay(500);
    Intake.move_velocity(-600);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(100);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
        pros::delay(2000);
    // Set robot pose to a known value
    chassis.setPose(-25,47,270);
    RclMain.setRclPose( lemlib::Pose(-25,47,270));
    RclMain.updateBotPose();
    // Robot moves away from long goal
    chassis.moveToPose(-40,47,270,2000);
    Loader.retract();
    chassis.turnToHeading(180, 1000);
    // Robot move to other side of the field
    chassis.moveToPose(-40,-46, 180, 5000); // move back to (-46, -46) with a 2 second timeout
    //ani-jam
    Intake.move_velocity(-600);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(100);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
        pros::delay(500);
    Intake.move_velocity(-600);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(100);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
        pros::delay(500);
    Descore.extend();
    Loader.extend();
    chassis.turnToHeading(270, 1000);
    // Robot turns to face the loader
    chassis.turnToHeading(270,1000);
    // Robot moves to the loader and constantly drives into it to ensure proper loading
    chassis.moveToPose(-80,-46, 270, 3000,  {.maxSpeed = 50, .minSpeed = 5}, false); // move to (-80, -46) with a 2 second timeout
    RclMain.updateBotPose();
    // Intake 0 velocity to prevent jams
    Intake.move_velocity(0);
    Redirect.move_velocity(0);
    Sort.move_velocity(0);
    // Robot move to pose between wall and goal to go to the other side of the field
    chassis.moveToPose(-28,-60, 270, 2000,  {.forwards=false, .minSpeed = 10}); // move back to (-28, -60) with a 2 second timeout
        pros::delay(500);
    RclMain.updateBotPose();
    // Robot moves to pose on the other side of the field
    chassis.moveToPose(40,-60,270, 2000,  {.forwards=false, .maxSpeed = 60}); // move back to (40, -60) with a 2 second timeout
    Loader.retract();
    RclMain.updateBotPose();
    chassis.turnToHeading(180, 1000);
    chassis.moveToPoint(40,-47, 2000,  {.forwards=false}); // move back to (20, -47) with a 2 second timeout
    RclMain.updateBotPose();
    chassis.turnToHeading(90, 1000);
    chassis.moveToPoint(20,-47, 2000,  {.forwards=false}); // move back to (20, -47) with a 2 second timeout
    // Robot waits for .6 seconds to avoid losing blocks
        pros::delay(600);
    Descore.retract();
    Intake.move_velocity(-600);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(100);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
        pros::delay(500);
    Intake.move_velocity(-600);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(100);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
    pros::delay(2000);
    RclMain.updateBotPose();
    Descore.extend();
    Loader.extend();
    // Robot moves to the loader and constantly drives into it to ensure proper loading
    chassis.moveToPoint(80,-46, 4000,  {.maxSpeed = 50, .minSpeed = 5}, false); // move to (80, -46) with a 4 second timeout
    RclMain.updateBotPose();
    // Robot moves backwards to the goal
    chassis.moveToPose(25,-47,90, 2000,  {.forwards=false, .maxSpeed = 80}); // move back to (25, -47) with a 2 second timeout
    // Robot waits for .9 seconds to avoid losing blocks
        pros::delay(900);
    Descore.retract();
    Intake.move_velocity(-600);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(100);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
        pros::delay(500);
    Intake.move_velocity(-600);
    Redirect.move_velocity(600);
    Sort.move_velocity(600);
        pros::delay(100);
    Intake.move_velocity(600);
    Redirect.move_velocity(-600);
    Sort.move_velocity(-600);
    pros::delay(2000);
    // Set robot pose to a known value
    chassis.setPose(25,-47,90);
    RclMain.setRclPose( lemlib::Pose(25,-47,90));
    RclMain.updateBotPose();
    // Robot moves away from long goal
    chassis.moveToPose(40,-47,270,2000);
    Loader.retract();
    chassis.turnToHeading(0, 1000);
    Intake.move_velocity(0);
    Redirect.move_velocity(0);
    Sort.move_velocity(0);
    // Robot moves to center of the field
    chassis.moveToPose(40,0,0,3000);
    chassis.turnToHeading(270, 1000);
    // PARK!!!
    chassis.moveToPose(50,0,270,500,{.forwards = false,.maxSpeed = 60},false);
    chassis.moveToPose(80,0,270,1000,{.forwards = false, .minSpeed = 127});
    chassis.swingToHeading(180,lemlib::DriveSide::RIGHT,1000);
}

void RCLTest(lemlib::Chassis &chassis) {
// Reset starting position 
chassis.setPose({47, 13, 0}); 
RclMain.setRclPose({47, 13, 0}); 
pros::delay(10000);
// Safe distance resets 
RclMain.updateBotPose(&front_rcl); 
RclMain.updateBotPose(&right_rcl); 
}