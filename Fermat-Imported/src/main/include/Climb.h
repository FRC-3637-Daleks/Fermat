#pragma once

#include "Fermat.h"

#define CLIMB_MOTOR_SPEED   0.42    // %
#define CLIMB_SENSOR_TESTING 0       // 1 for true


class Climb{
    public:
        Climb(frc::Solenoid *climb_solenoid, frc::XboxController *xbox);
        void Tick();

    private:
        frc::XboxController *m_xbox;
        frc::Solenoid *m_climb_solenoid;
        WPI_TalonFX *m_climb_motor;
        frc::DigitalInput *m_upperLimit;
        frc::DigitalInput *m_lowerLimit;
};