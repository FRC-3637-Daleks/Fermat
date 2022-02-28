#include "Fermat.h"

Climb::Climb(frc::Solenoid *climb_solenoid, frc::XboxController *xbox){
    m_climb_solenoid = climb_solenoid;
    m_xbox = xbox;
    m_climb_motor = new WPI_TalonFX(CLIMB_MOTOR);
    m_upperLimit = new DigitalInput(UPPER_IR);
    m_lowerLimit = new DigitalInput(LOWER_IR);

    frc::SmartDashboard::PutBoolean("Arm Pneumatics State", m_climb_solenoid->Get());
}

// Untested (Would be nice to have a limit switch for side arm but we probably wont get it)
void
Climb::AutoClimb(){
    for(int i = 0; i < 4; i++){
        m_climb_solenoid->Set(true);
        Wait(0.1);
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
        Wait(0.1);
    }
}

// Moving arm Tested but not solenoid (should easily work)
/*
    Left Stick - Climb Motor(Up and Down)
    L3 - Climb Pneumatics(Toggle)
    Y - Auto Climb(Toggle)
*/
void
Climb::Tick(){
    frc::SmartDashboard::PutBoolean("Arm Pneumatics State", m_climb_solenoid->Get());
    if(m_xbox->GetYButtonPressed()){
        isAuto = !isAuto;
    }
    if(isAuto){
        AutoClimb();
    }else {
        if(m_upperLimit->Get() || m_lowerLimit->Get()){
            if(m_xbox->GetRawAxis(1)>0.5){
                m_climb_motor->Set(-CLIMB_MOTOR_SPEED);
            }
            if(m_xbox->GetRawAxis(1)<-0.5){
                m_climb_motor->Set(CLIMB_MOTOR_SPEED);
            }
        }
        if(m_xbox->GetStickButtonPressed(frc::GenericHID::kLeftHand)){
            m_climb_solenoid->Toggle();
        }
    }
   
    
}