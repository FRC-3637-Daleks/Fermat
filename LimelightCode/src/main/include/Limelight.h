#pragma once

#include "Euler.h"

class Limelight {
    public:
        Limelight(DalekDrive *drive);
        void Update();
		void LightOff();
		void LightOn();
        double CalcDistance(double area);
    private:
        DalekDrive *m_drive;
        double Area;
        double Distance;

};