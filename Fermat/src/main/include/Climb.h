#pragma once

#include "Fermat.h"

#define CLIMB_MOTOR_SPEED 0.1

class Climb{
    public:
        Climb(frc::Solenoid *climb_solenoid, frc::XboxController *xbox);
        bool MainArm();
        bool MainArm(bool isTheFunctionWithoutTheThing);
        bool SideArm();
        void Tick();
        void AutoClimb();
    private:
        frc::XboxController *m_xbox;
        frc::Solenoid *m_climb_solenoid;
        WPI_TalonFX *m_climb_motor;
        frc::DigitalInput *m_upperLimit;
        frc::DigitalInput *m_lowerLimit;
        frc::DigitalInput *m_sideLimit;
};