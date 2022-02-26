#include "Fermat.h"

Climb::Climb(frc::Solenoid *climb_solenoid, frc::XboxController *xbox){
    m_climb_solenoid = climb_solenoid;
    m_xbox = xbox;
    m_climb_motor = new WPI_TalonFX(CLIMB_MOTOR);
    m_upperLimit = new DigitalInput(UPPER_IR);
    m_lowerLimit = new DigitalInput(LOWER_IR);
    m_sideLimit = new DigitalInput(SIDE_IR);

    m_climb_solenoid->Set(false);
    frc::SmartDashboard::PutBoolean("Arm Pneumatics State", m_climb_solenoid->Get());
}

void
Climb::Tick(){
    frc::SmartDashboard::PutBoolean("Arm Pneumatics State", m_climb_solenoid->Get());
    MainArm(true);
    if(m_xbox->GetBButton()){
        m_climb_solenoid->Set(true);
    }
}

// Move main arm with joystick
bool
Climb::MainArm(bool isTheFunctionWithoutTheThing){
    if(m_xbox->GetRawAxis(1)>0.5){
        m_climb_motor->Set(CLIMB_MOTOR_SPEED);
    }
    else if(m_xbox->GetRawAxis(1)<-0.5){
        m_climb_motor->Set(-CLIMB_MOTOR_SPEED);
    }
    else{
        m_climb_motor->Set(0);
    }
    
    return false;
}

// Move main arm with joystick and the limit switch back up
bool
Climb::MainArm(){
    if(m_upperLimit->Get() || m_lowerLimit->Get()){
        return true;
    }
    if(m_xbox->GetRawAxis(1)>0.5){
        m_climb_motor->Set(-CLIMB_MOTOR_SPEED);
    }
    if(m_xbox->GetRawAxis(1)<-0.5){
        m_climb_motor->Set(CLIMB_MOTOR_SPEED);
    }
    return false;
}

//switch the sidearm from out to in and vise versa
void
Climb::AutoClimb(){
    for(int i = 0; i < 4; i++){
        m_climb_solenoid->Set(true);
        while(!(m_upperLimit->Get())){
            m_climb_motor->Set(CLIMB_MOTOR_SPEED);
        }
        while(!(m_lowerLimit->Get())){
            m_climb_motor->Set(-CLIMB_MOTOR_SPEED);
        }
        while(!(m_upperLimit->Get())){
            m_climb_motor->Set(CLIMB_MOTOR_SPEED);
        }
        m_climb_motor->Set(0);
        m_climb_solenoid->Set(false);
        Wait(0.1); //Might be replaced if we get a limit switch
    }
}

bool
Climb::SideArm(){
    m_climb_solenoid->Set(true);
    return false;
}