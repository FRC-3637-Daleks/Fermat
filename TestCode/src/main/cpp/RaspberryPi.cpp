#include "Fermat.h"

RaspberryPi::RaspberryPi(DalekDrive *drive){
    m_drive = drive;
}
void RaspberryPi::SwerveTurn(double degrees, double distance) {
    SmartDashboard::PutNumber("Degrees",degrees-MAX_DEGREES); 
    if(distance > 24) {// track ball
        if(degrees < 0) {
            m_drive->TankDrive((degrees-MAX_DEGREES)/10*MAX_SPEED * 0.75, (degrees-MAX_DEGREES)/10*MAX_SPEED, false);// swerve left while tracking ball
        } else {
            m_drive->TankDrive(-(degrees+MAX_DEGREES)/10*MAX_SPEED, -(degrees+MAX_DEGREES)/10*MAX_SPEED * 0.75, false);// swerve right while tracking ball
        }
    }else{
        m_drive->Stop();
    }
}