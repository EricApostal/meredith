#include "main.h"
#include "robot/robot.hpp"
#include "robot/scheduler.hpp"
#include "robot/tasks.hpp"
#include "robot/auton/far_side.hpp"

using namespace pros;

Scheduler scheduler;
Robot bot = Robot();

void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	doAuton();
}

// Driver control start (always called when not connected to field controller)
void opcontrol() {
	bot.taskName = "robot";
	scheduler.addTask(&bot);
	scheduler.startScheduler();
}