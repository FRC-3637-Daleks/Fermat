#include "Fermat.h"

Shooter::Shooter(frc::XboxController *xbox, frc::Solenoid *shooter_solenoid, Limelight *limelight)
{
    m_shooter_solenoid = shooter_solenoid;
    m_xbox = xbox;
    m_limelight = limelight;
    m_shooter_motor = new WPI_TalonSRX(SHOOTER_MOTOR);
}

void
Shooter::SpinHigh(){
    m_shooter_motor-> Set(FromMetersPerSecond(m_limelight->CalcVelocity(2))); //Need to convert velocity to RPM for controlling motor speed
}

void
Shooter::SpinLow(){
    m_shooter_motor-> Set(FromMetersPerSecond(m_limelight->CalcVelocity(1))); //Need to convert velocity to RPM for controlling motor speed
}

void
Shooter::TurnOnSolenoid(){
    m_shooter_solenoid->Set(true);
}

void
Shooter::TurnOffSolenoid(){
    m_shooter_solenoid->Set(true);
}

double 
Shooter::FromMetersPerSecond(double speed){
    // 5330 rpm = 88.8333333 rps
    // 2 in radius = 0.0508 m radius
    // 0.1595929068023614965139022838706 circumferance
    // 1 speed point
    // 14.177169887609779606984986211852 meters per seconds per 1 speed point
    return 1.0*speed/14.177169887609779606984986211852;
}

void
Shooter::Tick(){
    if (m_xbox->GetXButton()){
        SpinHigh();
    }
    if (!m_xbox->GetBumper(frc::XboxController::kLeftHand)){
        if(abs(m_shooter_motor->GetSelectedSensorVelocity()-m_limelight->CalcVelocity(2))<=.02){
            TurnOnSolenoid();
        }else if(abs(m_shooter_motor->GetSelectedSensorVelocity()-m_limelight->CalcVelocity(1))<=.02){
            TurnOnSolenoid();
        } else {
            TurnOffSolenoid();
        }
    }else{ 
        TurnOnSolenoid();
    }

    if(m_xbox->GetXButton()){
        m_limelight->LightOff();
    }
}

void
Shooter::ShootFromTarmac(){
    m_shooter_motor->Set(FromMetersPerSecond(m_limelight->CalcVelocity(2.0, 84.6)));
}

void
Shooter::ShootFromHangarWall(){
    //m_shooter_motor->Set(FromMetersPerSecond(m_limelight->CalcVelocity(1, 180)));
}
