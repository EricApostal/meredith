#pragma once

#include "main.h"
#include "okapi/api.hpp"

using namespace okapi;


class Motors
{
public:
    /*
        There isn't much of a need for us to use okapi anymore, so I will likely switch over to pros motor groups
        It was originally for auton, but there isn't much of a point
    */
    okapi::MotorGroup leftMotors = okapi::MotorGroup({-10,-9,-7});
    okapi::MotorGroup rightMotors = okapi::MotorGroup({11,12,13});
    std::shared_ptr<ChassisController> drive;

    Motors() {
        leftMotors.setBrakeMode( okapi::AbstractMotor::brakeMode::hold );
        rightMotors.setBrakeMode( okapi::AbstractMotor::brakeMode::hold );

        drive = ChassisControllerBuilder()

        // .withMotors({-1, -2, 3}, {8, -9, -10})
        .withMotors(leftMotors, rightMotors)
        // Green gearset, 4 in wheel diam, 11.5 in wheel track
        .withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 12_in}, 400})
        .build();
    }
};
