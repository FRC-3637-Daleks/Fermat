#include "Fermat.h"

#pragma once

#define WHEEL_CIRCUMFERENCE			0.612775 // meters
#define GEAR_RATIO					12
#define CAN_TIMEOUT					100
#define STALL_LIMIT					60
#define FREE_LIMIT					20
#define RAMP_RATE					0.5
#define MAX_SPEED					0.45 // Percent of Full Speed (1)
#define SLOW_SPEED					0.3 // Percent of MAX_SPEED
#define NUM_MOTORS_PER_SIDE			2
#define LEFT						0
#define RIGHT						1
#define FRONT						0
#define REAR						1
#define ENCODER_FEET                6300 //encoder values for 1 feet
#define turningErrorThreshold		0.05
#define pTurn						2 // this number depends on the speed of the robot (weight and handicap)


using namespace frc;
using namespace rev;

class DalekDrive {
	public:
		DalekDrive(XboxController *xbox);
		double squareInput(double v);
		void TankDrive(Joystick* leftStick, Joystick* rightStick, bool squaredInputs, bool isSlow);
		void TankDrive(Joystick& leftStick, Joystick& rightStick, bool squaredInputs, bool isSlow);
		void TankDrive(double l, double r, bool squaredInputs, bool isSlow);
		void MoveLeft(Joystick* leftStick, bool squaredInputs, bool isSlow);
		void MoveRight(Joystick* rightStick, bool squaredInputs, bool isSlow);
		void StopLeft();
		void StopRight();
		double GetRight();
		double GetLeft();
		void SetCanDrive(bool drive);
		bool DriveToFeet(double feet);
		bool Turn(double degrees);
		void Tick();
		bool GetCanDrive();
		
	
	private:
		enum MotorCount {
			leftFront,
			leftRear,
			rightFront,
			rightRear
		};
		bool canDrive = false, driveSlow = false;

		WPI_TalonFX *m_left[2];
		WPI_TalonFX *m_right[2];
		frc::Joystick *m_leftStick;
		frc::Joystick *m_rightStick;
		XboxController *m_xbox;
};