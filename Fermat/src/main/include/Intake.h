#pragma once

#include "Fermat.h"

#define MOTOR_SPEED 0.25

class Intake{
    public:
    Intake(frc::Solenoid *intake_solenoid, frc::XboxController *xbox);
    void StartIntake();
    void StopIntake();
    
    private:
    WPI_TalonSRX *m_intake_motor;
    frc::Solenoid *m_intake_solenoid;
    frc::XboxController *m_xbox;
};