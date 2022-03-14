#include "Fermat.h"

Shooter::Shooter(DalekDrive *drive, frc::XboxController *xbox, frc::Solenoid *shooter_solenoid, Limelight *limelight)
{
    m_shooter_solenoid = shooter_solenoid;
    m_xbox = xbox;
    m_limelight = limelight;
    m_drive = drive;
    m_shooter_motor = new WPI_TalonSRX(SHOOTER_MOTOR);
    //m_shooterIR = new DigitalInput(SHOOTER_IR);
}

double
Shooter::SetHigh(){
    //Warm up the motor
    return FromMetersPerSecond(m_limelight->CalcVelocity(2));
}

double
Shooter::SetLow(){
    return FromMetersPerSecond(m_limelight->CalcVelocity(1));
}

double
Shooter::SetMiss(){
    return 0.5; //lowest it can go to output the ball (can't go out of ring)
}

void 
Shooter::SetSpeed(double dist){ // inputs in (m)
    m_shooter_motor->Set(FromMetersPerSecond(m_limelight->CalcVelocity(2, dist)));
}

void
Shooter::Shoot(){
    TurnOnSolenoid();
    Wait(0.5_s);
    TurnOffSolenoid();
}


void
Shooter::TurnOnSolenoid(){
    m_shooter_solenoid->Set(true);
}

void
Shooter::TurnOffSolenoid(){
    m_shooter_solenoid->Set(false);
}

double 
Shooter::FromMetersPerSecond(double speed){
    // 5330 rpm = 88.8333333 rps
    // 2 in radius = 0.0508 m radius
    // 0.1595929068023614965139022838706 circumferance
    // 1 speed point
    // 14.177169887609779606984986211852 meters per seconds per 1 speed point
    return -1.0*speed/14.177169887609779606984986211852-SHOOT_MOTOR_BOOST;
}



/*
  Back Button - Toggle auto shoot
  Right Bumper - Toggle shooter pneumatics
  Right Joystick XBOX - Shooter speeds (4 speeds)
    Up - 0.25
    Left - 0.5
    Down - 0.75
    Right - 1
*/
void
Shooter::Tick(){

    double speed=0;

    // frc::SmartDashboard::PutBoolean("Shooter Pneumatics State", m_shooter_solenoid->Get());
    if (m_xbox->GetXButton()){
        speed = SetMiss();
    } else if (m_xbox->GetRawAxis(0) > 0.5){
        speed = FromMetersPerSecond(m_limelight->CalcVelocity(2,3.3));
    } else if (m_xbox->GetRawAxis(1) > 0.5){
        speed = FromMetersPerSecond(m_limelight->CalcVelocity(2,4.5));
    } else if (m_xbox->GetRawAxis(0)< -0.5){
        speed = FromMetersPerSecond(m_limelight->CalcVelocity(2,7.2));
    } else if (m_xbox->GetRawAxis(1) < -0.5){
        speed = FromMetersPerSecond(m_limelight->CalcVelocity(2));
    } 

    m_shooter_motor-> Set(speed);    
    SmartDashboard::PutNumber("SET SPEED", speed);
    
    if (m_xbox->GetRightBumperPressed()){
        Shoot();
    }
}