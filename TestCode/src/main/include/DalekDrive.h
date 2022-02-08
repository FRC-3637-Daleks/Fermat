#include "Fermat.h"

#pragma once

#define WHEEL_CIRCUMFERENCE			0.612775 // meters
#define GEAR_RATIO					12
#define CAN_TIMEOUT					100
#define STALL_LIMIT					60
#define FREE_LIMIT					20
#define RAMP_RATE					0.5
#define MAX_SPEED					0.25
#define NUM_MOTORS_PER_SIDE			2
#define LEFT						0
#define RIGHT						1
#define FRONT						0
#define REAR						1
#define ENCODER_FEET                6300 //encoder values for 1 feet

using namespace frc;
using namespace rev;

class DalekDrive {
	public:
		DalekDrive();
		double squareInput(double v);
		void TankDrive(Joystick* leftStick, Joystick* rightStick, bool squaredInputs);
		void TankDrive(Joystick& leftStick, Joystick& rightStick, bool squaredInputs);
		void TankDrive(double l, double r, bool squaredInputs);
		void Stop();
		bool DriveToFeet(float feet);
	
	private:
		enum MotorCount {
			leftFront = 0,
			leftRear = 1,
			rightFront = 2,
			rightRear = 3
		};

		WPI_TalonFX *m_left[2];
		WPI_TalonFX *m_right[2];
};