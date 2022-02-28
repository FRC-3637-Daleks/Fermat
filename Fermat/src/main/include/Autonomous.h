#include "Fermat.h"

// some of this should be in the DalekDrive class, but whatever
#pragma once

// literally every single #define is a guess, so test one at a time
#define START_DIST		        // dist from line to tip of triangle
#define lineToWall				//Fill in
#define startDistanceFromWall   //Fill in
#define pixelOffsetCoefficient	//Fill in
#define angleOffsetCoefficient	//Fill in
#define distanceCoefficient		//Fill in
#define turningErrorThreshold	//Fill in
#define distanceErrorThreshold	//Fill in
#define pTurn					// this number depends on the speed of the robot (weight and handicap)
#define iTurn					0 // probably unnecessary and won't be used
#define dTurn					0 // probably unnecessary and won't be used
#define maxTurnSpeed			0.5

using namespace std;
using namespace frc;

// all angles are in radians
// all measurements are in meters
class Auton {
	public:
	Auton(DalekDrive *drive, RaspberryPi *pi, BallIntake *ballIntake, LImelight *limelight);
	
	void AutonCase(int begin, int end); // this must be called before AutonDrive()
	void AutonDrive(double period);

	private:
	DalekDrive *m_drive;
	RaspberryPi *m_pi;
	BallIntake *m_ballIntake;
    Limelight *m_limelight;

	double p_temp, i_temp, d_temp, target_x, target_y, target_ang;
	// eventually will need delivery mechanism

	int auton_phase;
	double exit_target_x, exit_target_y, exit_target_ang, exit_target_dist, enter_target_x, enter_target_y, enter_target_ang, enter_target_dist, travelled_dist;
	bool pickupBallEnd, pickupBallStart;

	bool driveToCoordinates(double x, double y, double angle, double period);
	bool turnToFace(double angle);
	double angleOffset(double angle);
};