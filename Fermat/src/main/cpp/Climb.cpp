#include "Fermat.h"

Climb::Climb(frc::Solenoid *climb_solenoid, frc::XboxController *xbox){
    m_climb_solenoid = climb_solenoid;
    m_xbox = xbox;
    m_climb_motor = new WPI_TalonFX(CLIMB_MOTOR);
    m_upperLimit = new DigitalInput(UPPER_IR);
    m_lowerLimit = new DigitalInput(LOWER_IR);
    climbCase=0;
}

// Untested (Would be nice to have a limit switch for side arm but we probably wont get it)
void
Climb::AutoClimb(){
    if (climbCase<=STAGES*BARS){
        //Move the side arm out
        if (climbCase%STAGES==1){
            m_climb_solenoid->Set(true);
            Wait(2);
        }

        //Move arm up
        if(climbCase%STAGES==2){
            m_climb_motor->Set(CLIMB_MOTOR_SPEED);
            if (!(m_upperLimit->Get())){
                climbCase++;
            }
        }

        //Move arm down
        if(climbCase%STAGES==3){
            m_climb_motor->Set(-CLIMB_MOTOR_SPEED);
            if (!(m_lowerLimit->Get())){
                climbCase++;
            }
        }

        //Move the side arm in
        if (climbCase%STAGES==4){
            m_climb_solenoid->Set(false);
            Wait(2);
        }

        //Move arm up
        if(climbCase%STAGES==5){
            m_climb_motor->Set(CLIMB_MOTOR_SPEED);
            if (!(m_upperLimit->Get())){
                Wait(.2);
                m_climb_motor->Set(-CLIMB_MOTOR_SPEED);
                climbCase++;
            }
        }

        //back down to be under the limit


        //Stop the motor
        if (climbCase%STAGES==6){
            m_climb_motor->Set(m_climb_motor->Get()*-.9);
            if (abs(m_climb_motor->Get())<.1){
                climbCase++;
                m_climb_motor->Set(0);
            }
        }

        //Move the side arm in
        if (climbCase%STAGES==0){
            m_climb_solenoid->Set(false);
            Wait(2);
        }

        // (STAGES%STAGES = 0)
        
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
    frc::SmartDashboard::PutBoolean("Upper Sensor", m_upperLimit->Get());
    frc::SmartDashboard::PutBoolean("Lower Sensor", m_lowerLimit->Get());
    // frc::SmartDashboard::PutBoolean("Arm Pneumatics State", m_climb_solenoid->Get());
    
    if(false){// m_xbox->GetYButton()
        AutoClimb();
    } else {
        
        climbCase = 0; // So Auto Climb Resets

        if (CLIMB_SENSOR_TESING == 0){
            if (!(m_upperLimit->Get())){
                m_climb_motor->Set(CLIMB_MOTOR_SPEED);
                m_climb_solenoid->Set(false);
            } else if (!(m_lowerLimit->Get())){
                m_climb_motor->Set(-CLIMB_MOTOR_SPEED);
                m_climb_solenoid->Set(false);
            } else {
                if(m_xbox->GetRawAxis(5)>0.5){
                m_climb_motor->Set(CLIMB_MOTOR_SPEED);
                } else if(m_xbox->GetRawAxis(5)<-0.5){
                    m_climb_motor->Set(-CLIMB_MOTOR_SPEED);
                } else{
                    m_climb_motor->Set(m_climb_motor->Get()*-.9);
                }
            }
        }

        if(m_xbox->GetBumperPressed(frc::GenericHID::kLeftHand)){
            m_climb_solenoid->Toggle();
        }
    } 
}