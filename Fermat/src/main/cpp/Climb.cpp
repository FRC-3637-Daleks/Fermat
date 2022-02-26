#include "Fermat.h"

Climb::Climb(frc::Solenoid *climb_solenoid, frc::XboxController *xbox){
    m_climb_solenoid = climb_solenoid;
    m_xbox = xbox;
    m_climb_motor = new WPI_TalonFX(CLIMB_MOTOR);
    m_upperLimit = new DigitalInput(UPPERLIMIT);
    m_lowerLimit = new DigitalInput(LOWERLIMIT);

    m_climb_solenoid->Set(false);
    frc::SmartDashboard::PutBoolean("Arm Pneumatics State", m_climb_solenoid->Get());
}

void
Climb::Tick(){
    frc::SmartDashboard::PutBoolean("Arm Pneumatics State", m_climb_solenoid->Get());
    MainArm(true);
    //(m_xbox->GetStickButton(XboxController::kLeftHand)){
    SideArm();
    //}
}

bool
Climb::MainArm(bool isTheFunctionWithoutTheThing){
    if(m_xbox->GetRawAxis(1)>0.5){
        m_climb_motor->Set(MOTOR_SPEED);
    }
    else if(m_xbox->GetRawAxis(1)<-0.5){
        m_climb_motor->Set(-MOTOR_SPEED);
    }
    else{
        m_climb_motor->Set(0);
    }
    
    return false;
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
    m_climb_solenoid->Set(true);
    return false;
}