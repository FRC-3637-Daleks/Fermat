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

void
Shooter::SetHigh(){
    //Warm up the motor
    m_shooter_motor-> Set(-FromMetersPerSecond(m_limelight->CalcVelocity(2)));
    if (abs(m_limelight->GetAngle())>2){
        m_drive->SetCanDrive(false);
        m_drive->Turn(m_limelight->GetAngle());
    } else {
        m_drive->SetCanDrive(true);
    }
    
}

void
Shooter::SetLow(){
    m_shooter_motor-> Set(FromMetersPerSecond(m_limelight->CalcVelocity(1)));
}

void
Shooter::SetMiss(){
    m_shooter_motor-> Set(-0.6); //lowest it can go to output the ball (can't go out of ring)
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
    Wait(0.5);
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
    return speed/14.177169887609779606984986211852+SHOOT_MOTOR_BOOST;
}

void
Shooter::ManualShooting(){
    // This should use some pre determinded values not just random motor speeds ^^^
    if (m_xbox->GetRawAxis(0) > 0.5){
        m_shooter_motor-> Set(-FromMetersPerSecond(m_limelight->CalcVelocity(2,2.15)));
    } else if (m_xbox->GetRawAxis(1) > 0.5){
        m_shooter_motor-> Set(-FromMetersPerSecond(m_limelight->CalcVelocity(2,4)));
    } else if (m_xbox->GetRawAxis(0)< -0.5){
        m_shooter_motor-> Set(-FromMetersPerSecond(m_limelight->CalcVelocity(2,6.0)));
    } else if (m_xbox->GetRawAxis(1) < -0.5){
        m_shooter_motor-> Set(-FromMetersPerSecond(m_limelight->CalcVelocity(2,10.0)));
    } else {
        m_shooter_motor->Set(0);
    }

    if (m_xbox->GetBumperPressed(frc::GenericHID::kRightHand)){
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
    if((m_shooter_motor->GetSelectedSensorVelocity()-m_limelight->CalcVelocity(2))<=.02){
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
    

    if (autoShoot) {
        AutomaticShooting();
    } else {
        ManualShooting();
    }
    if (m_xbox->GetXButton()){
        SetMiss();
    }
}