#pragma once

#include "Fermat.h"

#define SHOOT_ANGLE         1.0646508437 //rad (57 degrees) //1.0646508437
#define HIGH_SHOOT          2.6416 //meters //2.6416
#define LOW_SHOOT           4 //meters
#define START_HEIGHT        0.058 //meters

// #define DIST_COEFFICIENT    25.9 //inches
// #define DIST_EXPONENT       -0.471 // inches
#define DIST_COEF_C         13.7
#define DIST_EXPO_C         -0.628
#define DIST_COEF_M         39.1
#define DIST_EXPO_M         -0.352
#define DIST_COEF_F         73.5
#define DIST_EXPO_F         -0.227

#define ANGLE_COEFFICIENT   0 //rad
#define ANGLE_EXPONENT      0
#define ANGLE_PRODUCT       1.59 
#define ANGLE_OFFSET        0.0228 
#define AREA_MAX            0.3
#define AREA_MIN            0.001


class Limelight {
    public:
        Limelight(DalekDrive *drive);
        void Tick();
		void LightOff();
		void LightOn();
        double CalcDistance();
        double CalcVelocity(double points, double xDistance);
        double CalcVelocity(double points);
        double CalcShootAngle(double velocty);
        double CalcTurnAngle(double xPos);
        double GetAngle();
        double GetDistance();
        void SetMode(int newMode);

    private:
        DalekDrive *m_drive;
        double area, distance, low_velocity, high_velocity, angle;
        int mode=1; 
};