#include "Fermat.h"

RaspberryPi::RaspberryPi(DalekDrive *drive){
    m_drive = drive;
}
void RaspberryPi::SwerveTurn(double degrees, double distance) {
    if(distance > 0) {
        if(degrees > 0) {
            m_drive->TankDrive((degrees-30)/6*MAX_SPEED, (degrees-30)/6*MAX_SPEED * 0.5, false);
            //return false;
        } else {
            m_drive->TankDrive(-(degrees+30)/6*MAX_SPEED * 0.5, -(degrees+30)/6*MAX_SPEED, false);
            // return false;
        }
    }   
    //return true;        
}