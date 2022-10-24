#include "Fermat.h"

// some of this should be in the DalekDrive class, but whatever
#pragma once

#define LIMELIGHT_GOOD			0 // 1 for true
#define AUTON_VERSION			0 // 0 for left
#define PI_GOOD					0 // 1 for true

using namespace std;
using namespace frc;

// all angles are in radians
// all measurements are in meters
class Auton {
	public:
		Auton(DalekDrive *drive, RaspberryPi *pi, Intake *intake, Limelight *limelight, Shooter *shooter);
		void REALLYBAD();

	private:
		DalekDrive *m_drive;
		RaspberryPi *m_pi;
		Intake *m_intake;
		Limelight *m_limelight;
		Shooter *m_shooter;
		// int auton_phase;
};