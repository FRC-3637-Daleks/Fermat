#include "Fermat.h"

Climb::Climb(frc::Solenoid *climb_solenoid, frc::XboxController *xbox){
    m_climb_solenoid = climb_solenoid;
    m_xbox = xbox;
    m_climb_motor = new WPI_TalonFX(CLIMB_MOTOR);
    m_upperLimit = new DigitalInput(UPPERLIMIT);
    m_lowerLimit = new DigitalInput(LOWERLIMIT);

}

void
Climb::tick(){
    MainArm();
    if(m_xbox->GetStickButton(XboxController::kLeftHand)){
        SideArm();
    }
}

bool
Climb::MainArm(){
    if(m_upperLimit->Get() || m_lowerLimit->Get()){
        return true;
    }
    if(m_xbox->GetRawAxis(1)>0){
        m_climb_motor->Set(MOTOR_SPEED);
    }
    if(m_xbox->GetRawAxis(1)<0){
        m_climb_motor->Set(-MOTOR_SPEED);
    }
    return false;
}

bool
Climb::SideArm(){
    m_climb_solenoid->Toggle();
    return false;
}