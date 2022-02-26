#include "Fermat.h"

Intake::Intake(frc::Solenoid *intake_solenoid, frc::XboxController *xbox){
    //m_this_is_stupid = new frc::Dumb(0); - Andrew Rodriguez
    m_intake_solenoid = intake_solenoid;
    m_xbox = xbox;
    m_intake_motor = new WPI_TalonSRX(INTAKE_MOTOR);

    m_intake_solenoid->Set(false);
    frc::SmartDashboard::PutBoolean("Intake Pneumatics State", m_intake_solenoid->Get());
}

//Tick function doin tick function things
//Left bumper hold = motor go brrrrrr
//A button = pneumatics piston goes out and in (toggle)
void
Intake::Tick() {
    SmartDashboard::PutBoolean("Y Button", m_xbox->GetYButton());
    SmartDashboard::PutBoolean("A Button", m_xbox->GetAButton());
    SmartDashboard::PutBoolean("B Button", m_xbox->GetBButton());
    SmartDashboard::PutBoolean("X Button", m_xbox->GetXButton());
    frc::SmartDashboard::PutBoolean("Intake Pneumatics State", m_intake_solenoid->Get());
    if (m_xbox->GetBumper(frc::GenericHID::kLeftHand))
        SuckBalls();
    else if (m_xbox->GetBumper(frc::GenericHID::kRightHand))
        UnSuckBalls();
    else
        m_intake_motor->Set(0);
    if(m_xbox->GetAButton()) {
        ToggleIntakePneumatics();
    }
}

//Starts and stops the intake depending on whether or not the button 
//is being pressed
bool
Intake::SuckBalls() {
    SmartDashboard::PutBoolean("Intake Work?", true);
    m_intake_motor->Set(MOTOR_SPEED);  
}

//Reverses the motor
bool
Intake::UnSuckBalls() {
    m_intake_motor->Set(-MOTOR_SPEED);
}

//Toggles the solenoid for the intake pneumatics
bool
Intake::ToggleIntakePneumatics() {
    m_intake_solenoid->Toggle();
}

/*
bool
Intake::AutoIntake() {
    m_intake_solenoid->
}
*/