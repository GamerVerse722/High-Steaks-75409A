#include "user/actions/Lift.hpp"
#include "user/Devices.hpp"

namespace buttonActions {
    void LiftUp::onPress() {
        devices::liftMotor.move(127);
        buttonActions::toggleScore = false;
    }

    void LiftUp::onRelease() {
        devices::liftMotor.move(0);
        buttonActions::toggleScore = false;
    }

    void LiftDown::onPress() {
        devices::liftMotor.move(-127);
        buttonActions::toggleScore = false;
    }
    void LiftDown::onRelease() {
        devices::liftMotor.move(0);
        buttonActions::toggleScore = false;
    }
}