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
bool
Intake::AutoIntake(bool toggle) {
    if(toggle) {
        m_intake_solenoid->Set(true);
        m_intake_motor->Set(INTAKE_MOTOR_SPEED);
    } else {
        m_intake_solenoid->Set(false);
        m_intake_motor->Set(0);
    }
    
}

//Tick function doin tick function things
void
Intake::Tick() {
    //SmartDashboard::PutBoolean("Y Button", m_xbox->GetYButton());
    //SmartDashboard::PutBoolean("A Button", m_xbox->GetAButton());
    //SmartDashboard::PutBoolean("B Button", m_xbox->GetBButton());
    //SmartDashboard::PutBoolean("X Button", m_xbox->GetXButton());

    // FALSE MEANS IT NEEDED A BUTTON

    frc::SmartDashboard::PutBoolean("Intake Pneumatics State", m_intake_solenoid->Get());
    
    if (m_xbox->GetBumper(frc::GenericHID::kLeftHand)){
        SuckBalls();
    }else if (false){
        UnSuckBalls();
    }else{
        m_intake_motor->Set(0);
    }

    
    if (m_xbox->GetYButtonPressed()) {
        autoIntake = !autoIntake;
    }
    

    if (m_xbox->GetAButtonPressed()) {
        ToggleIntakePneumatics();
    }
    
    if((SmartDashboard::GetNumber("Distance", -1) <= 24)&&autoIntake) {
        AutoIntake(true);
    }
    
}