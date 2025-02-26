#include "lemlib-tarball/api.hpp"
#include "user/AutomSelector.hpp"
#include "user/Devices.hpp"
#include "user/actions/Lift.hpp"
#include <cmath>

using namespace devices;

ASSET(MoveLittle_txt);
ASSET(Automs_txt);

lemlib_tarball::Decoder decoder(Automs_txt);

namespace automSelector{
    int get_selected() {
        return (int) round(devices::potentiometer.get_value() / 1023.75) + 1;
    }

    std::string get_selected_name() {
        switch (get_selected()) {
            case 1:
                return "Red Negative";
            case 2:
                return "Red Positive";
            case 3:
                return "Move Little";
            case 4:
                return "Blue Positive";
            case 5:
                return "Blue Negative";
            }
        return "None";
    }

    void run_autom() {
        switch (get_selected()) {
            case 1:
                buttonActions::getRingColor = true;
                RedNegative();
                break;
            case 2:
                buttonActions::getRingColor = true;
                RedPositive();
                break;
            case 3:
                MoveLittle();
                break;
            case 4:
                buttonActions::getRingColor = false;
                BluePositive();
                break;
            case 5:
                buttonActions::getRingColor = false;
                BlueNegative();
                break;
        }
    }

    void RedNegative() {
        chassis.setPose(-61, 47.5, 270);
        chassis.follow(decoder["RedNegative1"], 15, 3000, false, true);
        chassis.waitUntil(39);
        mogoMech.toggle();
        pros::delay(250);
        buttonActions::toggleScore = true;
        chassis.follow(decoder["RedNegative2"], 15, 5000, true, true);
    }

    void RedPositive() {

    }

    void MoveLittle() {
        chassis.setPose(-60, 23, 90);
        chassis.follow(MoveLittle_txt, 10, 2000, true);
    }

    void BluePositive() {

    }

    void BlueNegative() {
        // chassis.setPose(0, 0, 0);
        // chassis.turnToHeading(90, 100000);

        chassis.setPose(0, 0, 0);
        chassis.moveToPoint(0, 24, 100000);
        // chassis.moveToPose(0, 24, 0, 100000);
    }
}