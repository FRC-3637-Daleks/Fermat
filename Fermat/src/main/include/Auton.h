#include "Fermat.h"

// some of this should be in the DalekDrive class, but whatever
#pragma once

// literally every single #define is a guess, so test one at a time
#define START_DIST		        // dist from line to tip of triangle
#define LINE_TO_WALL			//Fill in
#define START_DIST_FROM_WALL   	//Fill in
#define iTurn					0 // probably unnecessary and won't be used
#define dTurn					0 // probably unnecessary and won't be used
#define MAX_TURN_SPEED			0.5
#define LIMELIGHT_GOOD			0 // 1 for true
#define PI_GOOD					0 // 1 for true

using namespace std;
using namespace frc;

// all angles are in radians
// all measurements are in meters
class Auton {
	public:
		Auton(DalekDrive *drive, RaspberryPi *pi, Intake *intake, Limelight *limelight, Shooter *shooter);
		void Tick();	

	private:
		DalekDrive *m_drive;
		RaspberryPi *m_pi;
		Intake *m_intake;
		Limelight *m_limelight;
		Shooter *m_shooter;

		double p_temp, i_temp, d_temp, target_x, target_y, target_ang;
		// eventually will need delivery mechanism

		int auton_phase;
		double exit_target_x, exit_target_y, exit_target_ang, exit_target_dist, enter_target_x, enter_target_y, enter_target_ang, enter_target_dist, travelled_dist;
		bool pickupBallEnd, pickupBallStart;

		bool driveToCoordinates(double x, double y, double angle, double period);
		bool turnToFace(double angle);
		double angleOffset(double angle);
};