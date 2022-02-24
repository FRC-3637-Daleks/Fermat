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
        m_shooter_motor-> Set(m_shooter_motor->FromMetersPerSecond(frc::SmartDashboard::GetNumber("Shoot Velocity", 0.0))); //Need to convert velocity to RPM for controlling motor speed
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

int 
Shooter::FromMetersPerSecond(int speed){
    // 5330 rpm = 88.8333333 rps
    // 2 in radius = 0.0508 m radius
    // 0.1595929068023614965139022838706 circumferance
    // 14.177169887609779606984986211852 meters per seconds per 1 speed point
    // 1 full speed
    return 1.0*speed*14.177169887609779606984986211852;
}