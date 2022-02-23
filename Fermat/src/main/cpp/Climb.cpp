#include "Fermat.h"

Climb::Climb(frc::Solenoid *climb_solenoid, frc::XboxController *xbox){
    m_climb_solenoid = climb_solenoid;
    m_xbox = xbox;
    m_climb_motor = new WPI_TalonFX(CLIMB_MOTOR);
    m_upperLimit = new DigitalInput(UPPERLIMIT);
    m_lowerLimit = new DigitalInput(LOWERLIMIT);

}

bool
Climb::MainArm(){
    if(m_upperLimit->Get() || m_lowerLimit->Get()){
        return true;
    }
    if(m_xbox->GetTriggerAxis(frc::GenericHID::kLeftHand)>0){
        m_climb_motor->Set(MOTOR_SPEED);
    }
    if(m_xbox->GetTriggerAxis(frc::GenericHID::kLeftHand)<0){
        m_climb_motor->Set(-MOTOR_SPEED);
    }
    return false;
}