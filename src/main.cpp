#include "main.h"
#include "pros/motors.h"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include "user/Devices.hpp"
#include "user/AutomSelector.hpp"
#include "user/actions/Lift.hpp"
#include <cstdio>

using namespace devices;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
    // pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    hailMaryMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    opticalSensor.set_integration_time(5);
    opticalSensor.set_led_pwm(100);
    
    // std::cout << "HERE!!!" <<poer456dfgscvx 

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::screen::print(pros::E_TEXT_MEDIUM, 0, "X: %f", chassis.getPose().x);
            pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Y: %f", chassis.getPose().y);
            pros::screen::print(pros::E_TEXT_MEDIUM, 2, "Theta: %f", chassis.getPose().theta);
            pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Autom: (%d) %s", automSelector::get_selected(), automSelector::get_selected_name());
            pros::screen::print(pros::E_TEXT_MEDIUM, 4, "HailMerry Deg: %f", hailMaryMotor.get_position());
            pros::screen::print(pros::E_TEXT_MEDIUM, 5, "Hue: %lf", opticalSensor.get_hue());
            pros::screen::print(pros::E_TEXT_MEDIUM, 6, "Distance: %d, Brightness: %lf", opticalSensor.get_proximity(), opticalSensor.get_brightness());
            controller.print(0, 0, "S: %s, Color: %s", buttonActions::toggleScore ? "T" : "F", buttonActions::getRingColor ? "R" : "B");

            // delay to save resources
            pros::delay(50);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

void competition_initialize() {
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    automSelector::run_autom();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    intakeMotor.move(0);
    liftMotor.move(0);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    
    pros::Task warning([] {
        pros::delay(65000);
        controller.rumble("- - - - - - - -");
    });

    button::BaseButton::run();

    while (true) {
        // get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

        chassis.tank(leftY, rightY);

        // int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        // int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // chassis.arcade(leftY, rightX);

        // delay to save resources
        pros::delay(10);
    }
}