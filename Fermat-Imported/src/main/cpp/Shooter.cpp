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

void
Shooter::SetLow(){
    m_shooter_motor-> Set(FromMetersPerSecond(m_limelight->CalcVelocity(1)));
}

void
Shooter::SetMiss(){
    m_shooter_motor-> Set(0.1); //lowest it can go to output the ball (can't go out of ring)
}

void 
Shooter::SetSpeed(double dist){ // inputs in (m)
    m_shooter_motor->Set(m_limelight->CalcVelocity(2, dist));
}

double
Shooter::GetSpeed(){
    return m_shooter_motor -> Get();
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

bool
Shooter::CheckSpeed(double dist){
    return abs( abs(GetSpeed()) - abs( FromMetersPerSecond( m_limelight->CalcVelocity(dist) ) ) ) < 0.1;
}

void
Shooter::ManualShooting(){
    double speed=0;
    bool isFullSpeed = false;
    if (m_xbox->GetRawAxis(0) > 0.5){
        speed = FromMetersPerSecond(m_limelight->CalcVelocity(2,3.3));
        // isFullSpeed = CheckSpeed(3.3);
    } else if (m_xbox->GetRawAxis(1) > 0.5){
        speed = FromMetersPerSecond(m_limelight->CalcVelocity(2,4.5));
        // isFullSpeed = CheckSpeed(4.3688);
    } else if (m_xbox->GetRawAxis(0)< -0.5){
        speed = FromMetersPerSecond(m_limelight->CalcVelocity(2,7.1844));
        // isFullSpeed = CheckSpeed(7.1844);
    } else if (m_xbox->GetRawAxis(1) < -0.5){
        speed = FromMetersPerSecond(m_limelight->CalcVelocity(2,10));
        // isFullSpeed = CheckSpeed(m_limelight->GetDistance());
    }

    m_shooter_motor-> Set(speed);
    SmartDashboard::PutNumber("SHOOTER SPEED", speed);
    SmartDashboard::PutBoolean("FULL SPEED", isFullSpeed);
    SmartDashboard::PutNumber("T", isFullSpeed);

    if (m_xbox->GetRightBumperPressed()||isFullSpeed){
        Shoot();
    }
}

void
Shooter::AutomaticShooting(){
    if (abs(m_xbox->GetRawAxis(0))+abs(m_xbox->GetRawAxis(1))>0.5){ 
        SetHigh();
    } else {
        m_shooter_motor->Set(0);
    }
    if(CheckSpeed(m_limelight->GetDistance())){
        Shoot();
    }
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

    SmartDashboard::PutBoolean("Auto Shoot", autoShoot);

    if(m_xbox->GetBackButtonPressed()){
        autoShoot = !autoShoot;
    }

    // frc::SmartDashboard::PutBoolean("Shooter Pneumatics State", m_shooter_solenoid->Get());
    if (m_xbox->GetXButton()){
        SetMiss();
    }

    if (autoShoot) {
        AutomaticShooting();
    } else {
        ManualShooting();
    }
}