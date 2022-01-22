#pragma once

#include "Euler.h"

class Limelight {
    public:
        Limelight(DalekDrive *drive);
        void Update();
		void LightOff();
		void LightOn();
        double CalcDistance(double area);
        double CalcVelocity(double angle, double distance, double height);
        double Distance;
        const double ANGLE = 57; // angle of shooter in degrees
        const double HEIGHT = 2.6416; // height of top target in meterss
        const double INITALHEIGHT = 0.058; //initial height of shooter in meters
    private:
        DalekDrive *m_drive;
        double Area;

};