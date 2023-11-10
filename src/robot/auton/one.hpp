#include "main.h"
#include "lemlib/api.hpp"

/*
    Auton testing, useless otherwise. Should be added to scheduler.
*/
void doAuton(){
    pros::MotorGroup left_side_motors({9, 7});
    pros::MotorGroup right_side_motors({-12, -13});
    pros::Imu inertial_sensor(16);
    
    lemlib::Drivetrain_t drivetrain {
        &left_side_motors, // left drivetrain motors
        &right_side_motors, // right drivetrain motors
        10.3, // track width
        3.25, // wheel diameter
        360 // wheel rpm
    };

    lemlib::TrackingWheel left_tracking_wheel(&left_side_motors, 3.25, 5.15, 360);
    lemlib::TrackingWheel right_tracking_wheel(&right_side_motors, 3.25, 5.15, 360);

    // odometry struct
    lemlib::OdomSensors_t sensors {
        // &left_tracking_wheel, // vertical tracking wheel 1
        // &right_tracking_wheel, // vertical tracking wheel 2
        // &back_tracking_wheel, // horizontal tracking wheel 1
        // nullptr, // we don't have a second tracking wheel, so we set it to nullptr
        // &inertial_sensor // inertial sensor
        

        &left_tracking_wheel, // vertical tracking wheel 1
        &right_tracking_wheel, // vertical tracking wheel 2
        nullptr, // horizontal tracking wheel 1
        nullptr, // we don't have a second tracking wheel, so we set it to nullptr
        &inertial_sensor// inertial sensor
    };

    // forward/backward PID
    lemlib::ChassisController_t lateralController {
        8, // kP
        30, // kD
        1, // smallErrorRange
        100, // smallErrorTimeout
        3, // largeErrorRange
        500, // largeErrorTimeout
        5 // slew rate
    };
    
    // turning PID
    lemlib::ChassisController_t angularController {
        4, // kP
        40, // kD
        1, // smallErrorRange
        100, // smallErrorTimeout
        3, // largeErrorRange
        500, // largeErrorTimeout
        0 // slew rate
    };

    lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);

    chassis.calibrate(); // calibrate the chassis
    chassis.setPose(-35, 60, 90);
    chassis.moveTo(-35, 24, 10000, 100);
    // pros::delay(250);
    // chassis.turnTo(-70, 24, 5000, 100);
    // pros::delay(250);
    // chassis.moveTo(-15, 24, 10000, 100);
    
}