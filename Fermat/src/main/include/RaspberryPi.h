#pragma once

#include "Fermat.h"

#define MAX_DEGREES 30 //Degrees

class RaspberryPi{
    public:
        RaspberryPi(DalekDrive *drive);
        void SwerveTurn(double degree, double distance);
    private:
        DalekDrive *m_drive;
};