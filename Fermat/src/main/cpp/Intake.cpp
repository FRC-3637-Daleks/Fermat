#include "Fermat.h"

Intake::Intake(frc::Solenoid *intake_solenoid, frc::XboxController *xbox){
    //m_this_is_stupid = new frc::Dumb(0); - Andrew Rodriguez
    m_intake_motor = new WPI_TalonSRX(0);
    m_intake_solenoid = intake_solenoid;
    m_xbox = xbox;
}
//Starts the solenoid and makes the intake wheels spin
void
Intake::StartIntake() {
    m_intake_solenoid->Set(true);
    m_intake_motor->Set(MOTOR_SPEED);
}

//Stops the solenoid and makes the intake wheels stop
void
Intake::StopIntake() {
    m_intake_solenoid->Set(false);
    m_intake_motor->Set(0);
}