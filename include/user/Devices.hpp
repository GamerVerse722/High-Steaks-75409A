#pragma once

#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"

#include "user/actions/Doinker.hpp"
#include "user/actions/HailMary.hpp"
#include "user/actions/Intake.hpp"
#include "user/actions/Lift.hpp"
#include "user/actions/MogoMech.hpp"

namespace devices {
    extern pros::MotorGroup leftMotors;
    extern pros::MotorGroup rightMotors;

    extern pros::Imu imu;
    extern pros::Controller controller;

    extern lemlib::Drivetrain drivetrain;

    extern lemlib::ControllerSettings linearController;
    extern lemlib::ControllerSettings angularController;
    extern lemlib::OdomSensors sensors;
    extern lemlib::ExpoDriveCurve throttleCurve;
    extern lemlib::ExpoDriveCurve steerCurve;
    extern lemlib::Chassis chassis;

    extern pros::Motor liftMotor;
    extern pros::Motor intakeMotor;
    extern pros::Motor hailMaryMotor;

    extern pros::adi::Pneumatics mogoMech;
    extern pros::adi::Pneumatics doinker;

    extern pros::adi::Potentiometer potentiometer;
}

namespace configuredButtons{
    extern buttonActions::Doinker doinkerButton;

    extern buttonActions::MogoMech mogoMechButton;

    extern buttonActions::HailMaryUp hailMaryUpButton;
    extern buttonActions::HailMaryDown hailMaryDownButton;

    extern buttonActions::LiftUp liftUpButton;
    extern buttonActions::LiftDown liftDownButton;

    extern buttonActions::IntakeIn intakeInButton;
    extern buttonActions::IntakeOut intakeOutButton;
}