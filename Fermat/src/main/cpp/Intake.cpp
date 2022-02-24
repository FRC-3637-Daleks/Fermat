#include "Fermat.h"

Intake::Intake(frc::Solenoid *intake_solenoid, frc::XboxController *xbox){
    //m_this_is_stupid = new frc::Dumb(0); - Andrew Rodriguez
    m_intake_motor = new WPI_TalonSRX(INTAKE_MOTOR_ID);
    m_intake_solenoid = intake_solenoid;
    m_xbox = xbox;
}

//Tick function doin tick function things
//Left bumper hold = motor go brrrrrr
//A button = pneumatics piston goes out and in (toggle)
void
Intake::Tick() {
    if (m_xbox->GetAButton())
        ToggleIntakePneumatics();
    if(m_xbox->GetBumper(frc::GenericHID::kLeftHand)) {
        SuckBalls();
    }
}

//Starts and stops the intake depending on whether or not the button 
//is being pressed
bool
Intake::SuckBalls() {
    m_intake_motor->Set(MOTOR_SPEED);  
}

//Toggles the solenoid for the intake pneumatics
bool
Intake::ToggleIntakePneumatics() {
    m_intake_solenoid->Toggle();
}