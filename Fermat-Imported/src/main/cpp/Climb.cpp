#include "Fermat.h"

Climb::Climb(frc::Solenoid *climb_solenoid, frc::XboxController *xbox){
    m_climb_solenoid = climb_solenoid;
    m_xbox = xbox;
    m_climb_motor = new WPI_TalonFX(CLIMB_MOTOR);
    if (CLIMB_SENSOR_TESTING == 0){
        m_climb_motor->SetNeutralMode(Brake);
    }
    m_upperLimit = new DigitalInput(UPPER_IR);
    m_lowerLimit = new DigitalInput(LOWER_IR);
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
    frc::SmartDashboard::PutBoolean("Climb On", CLIMB_SENSOR_TESTING==0);
    // frc::SmartDashboard::PutBoolean("Arm Pneumatics State", m_climb_solenoid->Get());

    if (CLIMB_SENSOR_TESTING == 0){
        // if (!(m_upperLimit->Get())){
        //     m_climb_motor->Set(CLIMB_MOTOR_SPEED);
        //     m_climb_solenoid->Set(false);
        // } else if (!(m_lowerLimit->Get())){
        //     m_climb_motor->Set(-CLIMB_MOTOR_SPEED);
        //     m_climb_solenoid->Set(false);
        // } else {
        //     if(m_xbox->GetRawAxis(5)>0.5){
        //     m_climb_motor->Set(CLIMB_MOTOR_SPEED);
        //     } else if(m_xbox->GetRawAxis(5)<-0.5){
        //         m_climb_motor->Set(-CLIMB_MOTOR_SPEED);
        //     } else{
        //         m_climb_motor->Set(0.0);
        //     }
        // }
        
        if(m_xbox->GetRawAxis(5) > DEADZONE && m_lowerLimit->Get()){
            m_climb_motor->Set(CLIMB_MOTOR_SPEED*abs(m_xbox->GetRawAxis(5)));
        } else if(m_xbox->GetRawAxis(5) < -DEADZONE && m_upperLimit->Get()){
            m_climb_motor->Set(-CLIMB_MOTOR_SPEED*abs(m_xbox->GetRawAxis(5)));
        } else{
            m_climb_motor->Set(0.0);
        }

        if (!m_lowerLimit->Get()||!m_upperLimit->Get()){
            m_climb_solenoid->Set(false);
        }
    }

    if(m_xbox->GetLeftBumperPressed()){
        m_climb_solenoid->Toggle();
    }
}