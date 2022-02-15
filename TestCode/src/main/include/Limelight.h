#pragma once

#include "Fermat.h"

#define SHOOT_ANGLE 1 //rad (57 degrees)
#define HIGH_SHOOT 2.6416 //meters
#define LOW_SHOOT 1.2192 //meters
#define START_HEIGHT 0.058 //meters
#define DIST_COEFFICIENT 33.2 //inches
#define DIST_EXPONENT -0.468
#define ANGLE_COEFFICIENT 0 //rad
#define ANGLE_EXPONENT 0
#define ANGLE_PRODUCT 1.59 
#define ANGLE_OFFSET 0.0228 


class Limelight {
    public:
        Limelight(DalekDrive *drive);
        void Update();
		void LightOff();
		void LightOn();
        double CalcDistance(double area);
        double CalcVelocity(double points, double xDistance);
        double CalcShootAngle(double velocty);
        double CalcTurnAngle(double xPos);
        double distance, low_velocity, high_velocity;
    private:
        DalekDrive *m_drive;
        double Area;
};