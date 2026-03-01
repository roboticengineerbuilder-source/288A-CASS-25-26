#VEX Team 288A – CASS-25
EvanLib is a Ray-Casting Localization framework that works along side LemLib's Competition Code.

Official repository of Team 288A during the 2025/2026 VEX Robotics Competition season, Push Back.

This project is built using:

PROS

LemLib (motion + odometry)

EvanLib (Ray-Casting Localization)

This README is written for future RoboDawgs programmers who might reuse, maintain, or expand this system.

Core Philosophy

Tracking wheels drift.
IMUs drift.
Matches are long.

So we built a robot pose localizer that is not reliant on odometry alone.

Tracking Wheels + IMU → LemLib Odometry
Distance Sensors      → EvanLib (RCL)
LemLib + RCL          → Drift-Limited Pose Fusion

This code continuously corrects its global position using field geometry.

Project Architecture
main.cpp

customs/
│
├── roboports.hpp        → All hardware config
├── pidgains.hpp         → PID + drive curves
├── autons.hpp           → All autonomous routines
├── autonselector.hpp    → LVGL selector system
├── subsystems.hpp       → Intake + pneumatics logic
├── tasks.hpp            → Anti-jam system
└── RCL.hpp              → EvanLib localization framework

Motion System (LemLib)

Handled through lemlib::Chassis.

Odometry

2 vertical tracking wheels

1 horizontal tracking wheel

IMU

12" track width

2.75" omni wheels

PID Configuration

High D on linear controller for sharp corrections

Moderate angular D for heading stability

No integral (prevents windup)

Expo Drive Curves

Deadband filtering

Minimum movement threshold

Light exponential scaling

EvanLib (Ray-Casting Localization)
What It Does

EvanLib uses 4 distance sensors to:

Cast rays toward field walls

Detect obstacles blocking the ray

Validate sensor confidence

Compute corrected X or Y

Gradually sync pose with LemLib

It does not snap pose instantly.

It:

Limits max correction per update

Limits max corrections per second

Rejects extreme deltas

Supports accumulation mode

Obstacle Modeling

Dynamic obstacles prevent false wall readings.

Line_Obstacle

Used for:

Disable line

Field barriers

Polygonal shapes

Circle_Obstacle

Used for:

Loaders

Goal legs

Center goals

Obstacles:

Exist in a global collection

Auto-expire via lifetime timer

Can be inserted/removed at runtime

Pose localizer Strategy

When updating:

Sensor validates distance

Ray intersection is calculated

Obstacle intersection is checked

Coordinate correction computed

Delta filtered against:

minDelta

maxDelta

maxDeltaFromLemlib

Limited by maxSyncPerSec

Smooth sync applied

This prevents:

Jitter

Snap corrections

Oscillation loops

Autonomous System

My custom Autonomous routines include:

sixBR

sixBL

tenBR

skillsA

skillsB

RCLTest

Each auton:

Sets both LemLib pose and RCL pose

Uses moveToPose, moveToPoint, turnToHeading

Calls RclMain.updateBotPose() at critical points

Uses accumulation mode while scoring

Autonomous Selector (LVGL)

Brain screen uses:

TabView system

Red / Blue / Skills tabs

Button matrix for routine selection

Active tab auto-adjusts auton sign

selector::getAuton() returns:

Positive → Red side

Negative → Blue side

Zero → Skills

Driver Control
Drive

Arcade drive

Expo curves applied

Intake System

Smart control logic:

Intake

Redirect

Sort

Anti-jam:

Velocity monitoring

Reverse clearing

Optional background task

Pneumatics

Loader toggle

Descore toggle

Debounced inputs

Accumulation Mode

Used during scoring:

RclMain.startAccumulating();
pros::delay(1500);
RclMain.stopAccumulating();
RclMain.updateBotPose();

This:

Collects multiple readings

Averages them

Applies higher-confidence correction

Best used when robot is stationary.

Math Utilities

Includes:

VEX ↔ Standard angle conversions

Deg ↔ Rad conversion

Custom singly linked list (fast obstacle removal)

Ray slope / intercept calculation

Field boundary constants

Field half length:

±70.5 inches

How Future RoboDawgs Should Use EvanLib

If reusing this system:

1. Update Hardware

Motor ports

Tracking wheel offsets

Distance sensor offsets

2️. Re-measure

Horizontal drift

Sensor mounting angle

Robot center offsets

3️. Tune Carefully

minDelta

maxDelta

maxSyncPerSec

angleTolerance

Never reuse old offsets blindly.

⚠️ Things You Should NOT Do

❌ Do not remove obstacle checks.

❌ Do not allow unlimited pose syncing.

❌ Do not trust distance sensors without angle validation.

❌ Do not enable accumulation while moving.

Why This System Is Different

Most VEX robots:

Use tracking wheels only

Accumulate drift

Manually reset pose

CASS-25:

Continuously validates its field position

Understands walls

Understands obstacles

Smoothly corrects drift

Maintains match-long reliability

Testing Utilities

RCLTest():

Resets pose

Updates specific sensors

Used for debugging ray math

Brain screen:

Displays desired pose vs current pose

Refreshes every 50ms

Engineering Level

This system is closer to collegiate robotics localization than standard VRC code.

It includes:

Sensor localizer

Ray-casting

Obstacle geometry modeling

Time-based filtering

Sync limiting

Background tasks

License

Internal RoboDawgs Use Only!!!
Team 288A – Do not distribute outside this org without permission!!!
