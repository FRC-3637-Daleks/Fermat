#pragma once

#include "Fermat.h"

#define CLIMB_MOTOR_SPEED              0.65    // %
#define CLIMB_MOTOR_SPEED_ADJUST       0.30    // %
#define CLIMB_SENSOR_TESTING           0       // 1 for true
#define DEADZONE                       0.2

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