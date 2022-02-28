#include "Fermat.h"

Shooter::Shooter(DalekDrive *drive, frc::XboxController *xbox, frc::Solenoid *shooter_solenoid, Limelight *limelight)
{
    m_shooter_solenoid = shooter_solenoid;
    m_xbox = xbox;
    m_limelight = limelight;
    m_drive = drive;
    m_shooter_motor = new WPI_TalonSRX(SHOOTER_MOTOR);
    m_shooterIR = new DigitalInput(SHOOTER_IR);

    frc::SmartDashboard::PutBoolean("Shooter Pneumatics State", m_shooter_solenoid->Get());
}

void
Shooter::ShootHigh(){
    //Warm up the motor
    m_shooter_motor-> Set(FromMetersPerSecond(m_limelight->CalcVelocity(2)));
    while (abs(m_limelight->GetAngle())>2){
        if (m_limelight->GetAngle()>0){
            m_drive->TankDrive( -1.0 * MAX_SPEED , 1.0 * MAX_SPEED , false , true);
        } else {  // m_limelight->GetAngle() < 0
            m_drive->TankDrive( 1.0 * MAX_SPEED , -1.0 * MAX_SPEED , false , true);
        }
        
    }
    //adjust motor to right speed
    m_shooter_motor-> Set(FromMetersPerSecond(m_limelight->CalcVelocity(2)));
    TurnOnSolenoid();
}

void
Shooter::ShootLow(){
    m_shooter_motor-> Set(FromMetersPerSecond(m_limelight->CalcVelocity(1)));
}

void
Shooter::Shoot(){
     m_shooter_motor-> Set(0.1); //lowest it can go to output the ball (can't go out of ring)
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
Shooter::ManualShooting(){

    // This should use some pre determinded values not just random motor speeds ^^^
    
    if (m_xbox->GetRawAxis(5) > 0.5){
        m_shooter_motor-> Set(0.25);
    } else if (m_xbox->GetRawAxis(4) > 0.5){
        m_shooter_motor-> Set(0.5);
    } else if (m_xbox->GetRawAxis(5)< -0.5){
        m_shooter_motor-> Set(0.75);
    } else if (m_xbox->GetRawAxis(4) < -0.5){
        m_shooter_motor-> Set(1.0);
    } else {
        m_shooter_motor->Set(0);
    }

    if (m_xbox->GetBumperPressed(frc::GenericHID::kRightHand)){
        m_shooter_solenoid->Toggle();
    }
}

void
Shooter::ShootFromTarmac(){
    m_shooter_motor->Set(FromMetersPerSecond(m_limelight->CalcVelocity(2.0, 84.6)));
}

// shoot from 180 inches
void
Shooter::ShootFromHangarWall(){ 
    m_shooter_motor->Set(FromMetersPerSecond(m_limelight->CalcVelocity(1, 180)));
}

/*
  X Button - Rev motor
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
    frc::SmartDashboard::PutBoolean("Shooter Pneumatics State", m_shooter_solenoid->Get());
    if (autoShoot) {
        if(m_shooterIR->Get()){
            if (m_xbox->GetXButton()){ // this or we make it Get ButtonPressed and a variable 
                ShootHigh();
            } else {
                m_shooter_motor->Set(0);
            }
            if (m_xbox->GetBumper(frc::XboxController::kRightHand)){

                if((m_shooter_motor->GetSelectedSensorVelocity()-m_limelight->CalcVelocity(2))<=.02){
                    TurnOnSolenoid();
                }
                // // If we want to be able to shoot low
                // else if(abs(m_shooter_motor->GetSelectedSensorVelocity()-m_limelight->CalcVelocity(1))<=.02){
                //     TurnOnSolenoid();
                // } 
                else {
                    TurnOffSolenoid();
                }
            }else{ 
                TurnOnSolenoid();
            }
        }
    } else {
        ManualShooting();
    }

    if(m_xbox->GetRawButtonPressed(6)){
        autoShoot = !autoShoot;
    }
}