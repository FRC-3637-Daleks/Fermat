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
        //Move the side arm out
        m_climb_solenoid->Set(true);
        Wait(2);
        //Move arm up
        while(!(m_upperLimit->Get())){
            m_climb_motor->Set(CLIMB_MOTOR_SPEED);
        }
        //Move arm down
        while(!(m_lowerLimit->Get())){
            m_climb_motor->Set(-CLIMB_MOTOR_SPEED);
        }
        //Move arm up
        while(!(m_upperLimit->Get())){
            m_climb_motor->Set(CLIMB_MOTOR_SPEED);
        }
        //Stop the motor
        while (abs(m_climb_motor->Get())>.1){
            m_climb_motor->Set(m_climb_motor->Get()*-.9);
        }
        m_climb_motor->Set(0);
        //Move the side arm in
        m_climb_solenoid->Set(false);
        Wait(2);
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
    if(m_xbox->GetYButton()){
        AutoClimb();
    } else {
        if(m_upperLimit->Get() || m_lowerLimit->Get()){
            if(m_xbox->GetRawAxis(1)>0.5){
                m_climb_motor->Set(CLIMB_MOTOR_SPEED);
            } else if(m_xbox->GetRawAxis(1)<-0.5){
                m_climb_motor->Set(-CLIMB_MOTOR_SPEED);
            } else{
                m_climb_motor->Set(m_climb_motor->Get()*-.9);
            }
        } else {
            if (m_upperLimit->Get()){
                m_climb_motor->Set(-CLIMB_MOTOR_SPEED);
            } else {
                m_climb_motor->Set(CLIMB_MOTOR_SPEED);
            }
            
        }

        if(m_xbox->GetStickButtonPressed(frc::GenericHID::kLeftHand)){
            m_climb_solenoid->Toggle();
        }
    }
   
    
}