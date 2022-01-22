#pragma once

#include "Euler.h"

#define STARTING_HEIGHT				0.058 // meters
#define HIGH_SHOOT				    2.6416 // meters
#define LOW_SHOOT                   1.2192 // meters
#define SHOOT_ANGLE					1 // rad (57 degrees)



class Limelight {
    public:
        Limelight(DalekDrive *drive);
        void Update();
		void LightOff();
		void LightOn();
        double CalcDistance(double area);
        double CalcVelocity(double angle, double distance, double height);
        double Distance;
    private:
        DalekDrive *m_drive;
        double Area;

};