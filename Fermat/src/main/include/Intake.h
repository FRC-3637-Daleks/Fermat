#pragma once

#include "Fermat.h"

#define MOTOR_SPEED .25
#define INTAKE_MOTOR_ID 5
#define INTAKE_SOLENOID_ID 

class Intake{
    public:
    Intake(frc::Solenoid *intake_solenoid, frc::XboxController *xbox);
    bool StartIntake();
    bool StopIntake();
    bool SuckBalls();
    bool ToggleIntakePneumatics();
    void Tick();
    
    private:
    WPI_TalonSRX *m_intake_motor;
    frc::Solenoid *m_intake_solenoid;
    frc::XboxController *m_xbox;
};