#pragma once

#include "Fermat.h"

#define PI_MAX_DEGREES 30 //Degrees

class RaspberryPi{
    public:
        RaspberryPi(DalekDrive *drive, XboxController *xbox);
        bool SwerveTurn(double degree, double distance);
        bool SwerveTurn();
        void Tick();
    private:
        DalekDrive *m_drive;
        XboxController *m_xbox;
};