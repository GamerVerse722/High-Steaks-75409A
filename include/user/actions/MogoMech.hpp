#pragma once

#include "user/BaseButton.hpp"

namespace buttonActions {
    class MogoMech : public button::BaseButton {
        public:
            MogoMech(pros::controller_digital_e_t button) : BaseButton(button) {}
            void onPress();
    };
};