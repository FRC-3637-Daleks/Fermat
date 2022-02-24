#include "Fermat.h"

Shooter::Shooter(frc::XboxController *xbox, frc::Solenoid *shooter_solenoid)
{
    m_shooter_solenoid = shooter_solenoid;
    m_xbox = xbox;
    m_shooter_motor = new WPI_TalonSRX(SHOOTER_MOTOR);
}

void
Shooter::tick(){
    Spin();
    if(m_xbox->GetBumper(frc::GenericHID::kRightHand)){
        TurnOnSolenoid();
    }
}

bool
Shooter::Spin(){
    if(m_xbox->GetRawAxis(5) > 0.5){
        m_shooter_motor->Set(0.25); //Need to convert velocity to RPM for controlling motor speed
    }else if(m_xbox->GetRawAxis(4) < -0.5){
        m_shooter_motor->Set(0.5);
    }else if(m_xbox->GetRawAxis(5) < -0.5){
        m_shooter_motor->Set(0.75);
    }else if(m_xbox->GetRawAxis(4) > 0.5){
        m_shooter_motor->Set(1);
    }else{
        m_shooter_motor->Set(0);
    }
}

bool
Shooter::TurnOnSolenoid(){
    m_shooter_solenoid->Toggle();
}