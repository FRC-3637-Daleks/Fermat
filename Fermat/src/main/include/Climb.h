#pragma once

#include "Fermat.h"

#define CLIMB_MOTOR_SPEED 0.35
#define BARS 3
#define STAGES 6
#define CLIMB_SENSOR_TESING	1 //1 for true 0 for false


class Climb{
    public:
        Climb(frc::Solenoid *climb_solenoid, frc::XboxController *xbox);
        void Tick();
        void AutoClimb();
    private:
        int climbCase=5;
        frc::XboxController *m_xbox;
        frc::Solenoid *m_climb_solenoid;
        WPI_TalonFX *m_climb_motor;
        frc::DigitalInput *m_upperLimit;
        frc::DigitalInput *m_lowerLimit;
};