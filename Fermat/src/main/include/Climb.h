#pragma once

#include "Fermat.h"

class Climb{
    public:
        Climb(frc::Solenoid *climb_solenoid);
        bool MainArm();
    private:
        frc::Solenoid *m_climb_solenoid;
        WPI_TalonFX *m_climb_motor;
        frc::DigitalInput *m_upperLimit;
        frc::DigitalInput *m_lowerLimit;
};