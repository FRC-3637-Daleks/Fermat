#pragma once

#include "Fermat.h"

#define INTAKE_MOTOR_SPEED -0.65

class Intake{
    public:
        Intake(frc::Solenoid *intake_solenoid, frc::XboxController *xbox);
        bool ToggleIntakePneumatics();
        bool AutoIntake(bool toggle);
        void Tick();
    
    private:
        WPI_TalonSRX *m_intake_motor;
        frc::Solenoid *m_intake_solenoid;
        frc::XboxController *m_xbox;
        Limelight *m_limelight;
};