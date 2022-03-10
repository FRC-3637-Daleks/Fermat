#include "Fermat.h"

Intake::Intake(frc::Solenoid *intake_solenoid, frc::XboxController *xbox){
    m_intake_solenoid = intake_solenoid;
    m_xbox = xbox;
    m_intake_motor = new WPI_TalonSRX(INTAKE_MOTOR);
}

//Starts the motor
bool
Intake::SuckBalls() {
    m_intake_motor->Set(INTAKE_MOTOR_SPEED);  
}

//Reverses the motor
bool
Intake::UnSuckBalls() {
    m_intake_motor->Set(-INTAKE_MOTOR_SPEED);
}

//Toggles the solenoid for the intake pneumatics
bool
Intake::ToggleIntakePneumatics() {
    m_intake_solenoid->Toggle();
}

//Turns on pneumatics and turns on motor at the same time
void
Intake::AutoIntake(bool toggle) {
    if(toggle) {
        m_intake_solenoid->Set(true);
        SuckBalls();
    } else {
        m_intake_solenoid->Set(false);
        m_intake_motor->Set(0);
    }
    
}

//Spits out the ball
//Just wanna test
void
Intake::AutoOutTake(bool toggle){
    if (toggle){
        UnSuckBalls();
    }else{
        m_intake_solenoid->Set(false);
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

    // frc::SmartDashboard::PutBoolean("Intake Pneumatics State", m_intake_solenoid->Get());

    if (m_xbox->GetAButton()){
        AutoIntake(true);
    } else {
        AutoIntake(false);
    }
    
    //wanna see if this is a good way of taking out a ball
    if (m_xbox->GetYButton()){
        AutoOutTake(true);
    } else {
        AutoIntake(false);
    }
    
}