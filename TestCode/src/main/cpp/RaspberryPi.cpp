#include "Fermat.h"

RaspberryPi::RaspberryPi(DalekDrive *drive){
    m_drive = drive;
}
void RaspberryPi::SwerveTurn(double degrees, double distance) {
    if(distance > 0) {// track ball
        if(degrees > 0) {
            m_drive->TankDrive((degrees-MAX_DEGREES)/6*MAX_SPEED, (degrees-MAX_DEGREES)/6*MAX_SPEED * 0.5, false);// swerve left while tracking ball
        } else {
            m_drive->TankDrive(-(degrees+MAX_DEGREES)/6*MAX_SPEED * 0.5, -(degrees+MAX_DEGREES)/6*MAX_SPEED, false);// swerve right while tracking ball
        }
    }   
}