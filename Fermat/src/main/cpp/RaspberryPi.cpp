#include "Fermat.h"

RaspberryPi::RaspberryPi(DalekDrive *drive, XboxController *xbox){
    m_drive = drive;
    m_xbox = xbox;
}
void RaspberryPi::SwerveTurn(double degrees, double distance) {
    double speed = 0;
    if(distance > 24) {// track ball
        m_drive->SetCanDrive(false);
        if(degrees < 0) {
            //speed = (degrees-MAX_DEGREES)/10*MAX_SPEED; //the orginal value that works
            speed = fmod((distance / 48.0), 1) * (degrees/PI_MAX_DEGREES) * MAX_SPEED; //me trying to make it better
            m_drive->TankDrive(speed * 0.75, speed, false, false);// swerve left while tracking ball
        } else {
            //speed = (degrees+MAX_DEGREES)/10*MAX_SPEED; //the orginal value that works
            speed = fmod((distance / 48.0), 1) * (degrees/PI_MAX_DEGREES) * MAX_SPEED; //me trying to make it better
            m_drive->TankDrive(-1.0 * speed, -1.0 * speed * 0.75, false, false);// swerve right while tracking ball
        }
    }else{
        m_drive->SetCanDrive(true);
        m_drive->StopLeft();
        m_drive->StopRight();
    }
}
void RaspberryPi::SwerveTurn() {
    // Use network tables to get data
    double degrees = 0;
    double distance = 0; 
    SwerveTurn(degrees, distance);
}

/*
  B Button - Swerve turn (follow ball)  
*/
void
RaspberryPi::Tick(){
    // Use SmartDashboard tables to get data
    double degrees = SmartDashboard::GetNumber("Angle", 0.0); 
    SmartDashboard::PutNumber("Degrees",degrees-PI_MAX_DEGREES); //Don't know if we need to subtract MAX_DEGREES
    if (m_xbox->GetBButton()){
        SwerveTurn();
    }
}
