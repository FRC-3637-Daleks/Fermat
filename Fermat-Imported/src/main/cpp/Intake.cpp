#include "Fermat.h"

Intake::Intake(frc::Solenoid *intake_solenoid, frc::XboxController *xbox){
    m_intake_solenoid = intake_solenoid;
    m_xbox = xbox;
    m_intake_motor = new WPI_TalonSRX(INTAKE_MOTOR);
}

//Turns on pneumatics and turns on motor at the same time
bool
Intake::AutoIntake(bool toggle) {
    if(toggle) {
        m_intake_solenoid->Set(true);
        m_intake_motor->Set(INTAKE_MOTOR_SPEED);
    } else {
        m_intake_solenoid->Set(false);
        Wait(1.0_s);
        m_intake_motor->Set(0);
    }
    
}

//Tick function doin tick function things
/*
    Left Bumper - Activate intake motor
    A Buttton - Activate intake pneumatics
    Start Button - Activate auto intake
*/
void
Intake::Tick() {
    // frc::SmartDashboard::PutBoolean("A button", m_xbox->GetAButton());
    
    if (m_xbox->GetAButton()){
        AutoIntake(true);
    } else {
        AutoIntake(false);
    }
}