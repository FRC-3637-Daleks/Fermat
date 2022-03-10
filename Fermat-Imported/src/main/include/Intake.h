#pragma once

#include "Fermat.h"

#define INTAKE_MOTOR_SPEED -1.0

class Intake{
    public:
        Intake(frc::Solenoid *intake_solenoid, frc::XboxController *xbox);
        bool StartIntake();
        bool StopIntake();
        bool SuckBalls();
        bool UnSuckBalls();
        bool ToggleIntakePneumatics();
        bool AutoIntake(bool toggle);
        void Tick();
    
    private:
        WPI_TalonSRX *m_intake_motor;
        frc::Solenoid *m_intake_solenoid;
        frc::XboxController *m_xbox;
        Limelight *m_limelight;
};