#include "Fermat.h"

RaspberryPi::RaspberryPi(DalekDrive *drive){
    m_drive = drive;
}
bool RaspberryPi::SwerveTurn(double degrees, double distance) {
        if(degrees > 0) {
            m_drive->TankDrive(MAX_SPEED, MAX_SPEED * 0.75, false);
        } else {
            m_drive->TankDrive(MAX_SPEED * 0.75, MAX_SPEED, false);
        }
    }