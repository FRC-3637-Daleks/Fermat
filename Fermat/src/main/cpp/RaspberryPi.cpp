#include "Fermat.h"

RaspberryPi::RaspberryPi(DalekDrive *drive){
    m_drive = drive;
}
void RaspberryPi::SwerveTurn(double degrees, double distance) {
    SmartDashboard::PutNumber("Degrees",degrees-MAX_DEGREES); 
    double speed = 0;
    if(distance > 24) {// track ball
        if(degrees < 0) {
            //speed = (degrees-MAX_DEGREES)/10*MAX_SPEED; //the orginal value that works
            speed = fmod((distance / 48.0), 1) * (degrees/MAX_DEGREES) * MAX_SPEED; //me trying to make it better
            m_drive->TankDrive(speed * 0.75, speed, false);// swerve left while tracking ball
        } else {
            //speed = (degrees+MAX_DEGREES)/10*MAX_SPEED; //the orginal value that works
            speed = fmod((distance / 48.0), 1) * (degrees/MAX_DEGREES) * MAX_SPEED; //me trying to make it better
            m_drive->TankDrive(-1.0 * speed, -1.0 * speed * 0.75, false);// swerve right while tracking ball
        }
    }else{
        m_drive->StopLeft();
        m_drive->StopRight();
    }
}