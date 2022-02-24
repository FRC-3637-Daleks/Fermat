#pragma once

#include "Fermat.h"

#define MAX_DEGREES 30 //Degrees

class RaspberryPi{
    public:
        RaspberryPi(DalekDrive *drive, XboxController *xbox);
        void SwerveTurn(double degree, double distance);
        void SwerveTurn();
        void Tick();
    private:
        DalekDrive *m_drive;
        XboxController *m_xbox;
};