#include "Fermat.h"

Shooter::Shooter(frc::XboxController *xbox, frc::Solenoid *shooter_solenoid)
{
    m_shooter_solenoid = shooter_solenoid;
    m_xbox = xbox;
    m_shooter_motor = new WPI_TalonSRX(SHOOTER_MOTOR);
}

bool
Shooter::Spin(){
    if(m_xbox->GetAButton()){
        m_shooter_motor-> Set(0.75); //Need to convert velocity to RPM for controlling motor speed
    }
    //m_shooter_solenoid->Set(true);
}

bool
Shooter::TurnOnSolenoid(){
    bool on = false;
    if(!(m_shooter_solenoid->Get())){
        m_shooter_solenoid->Set(!on);
    }
}