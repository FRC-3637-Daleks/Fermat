#include "Fermat.h"

#pragma once

#define WHEEL_CIRCUMFERENCE			0.612775 // meters
#define GEAR_RATIO					12
#define CAN_TIMEOUT					100
#define STALL_LIMIT					60
#define FREE_LIMIT					20
#define RAMP_RATE					0.5
#define MAX_SPEED					1.0
#define NUM_MOTORS_PER_SIDE			2
#define LEFT						0
#define RIGHT						1
#define FRONT						0
#define REAR						1

using namespace frc;
using namespace rev;

class DalekDrive {
	public:
	enum class driveType { kMecanum, kDifferential };
	DalekDrive(int leftMotorChannel, int leftSlaveMotorChannel, int rightMotorChannel, int rightSlaveMotorChannel, driveType t);
	DalekDrive(CANSparkMax* leftMotor, CANSparkMax* leftSlaveMotor, CANSparkMax* rightMotor, CANSparkMax* rightSlaveMotor, driveType t);
	DalekDrive(CANSparkMax& leftMotor, CANSparkMax& leftSlaveMotor, CANSparkMax& rightMotor, CANSparkMax& rightSlaveMotor, driveType t);

	~DalekDrive();

	void TankDrive(Joystick* leftStick, Joystick* rightStick, bool squaredInputs = true);
	void TankDrive(Joystick& leftStick, Joystick& rightStick, bool squaredInputs = true);
	void TankDrive(double leftValue, double rightValue, bool squaredInputs = true);

	void ArcadeDrive(Joystick* stick, bool squaredInputs = true);
	void ArcadeDrive(Joystick& stick, bool squaredInputs = true);
	void ArcadeDrive(double moveValue, double rotateValue, bool squaredInputs = true);

	void Polar(Joystick* stick);
	void Polar(Joystick& stick);
	void Polar(double magnitude, double angle, double zRotation);

	void Cartesian(Joystick* stick, double gyroAngle = 0.0);
	void Cartesian(Joystick& stick, double gyroAngle = 0.0);
	void Cartesian(double ySpeed, double xSpeed, double zRotation, double gyroAngle = 0.0);

	void SetLeftRightMotorOutputs(double leftOutput, double rightOutput);
	void SetInvertedMotor(int side, bool isInverted);
	bool DriveOk();

	void DriveBaseSquare(int leftSensor, int RightSensor);
	double GetVelocity();

	private:
	void InitDalekDrive();
	double squareInput(double v);
	void printFaults(int side, int faults);
	float DeadZone(float input, float range);
	bool LidarInRange (int sensorOne, int sensorTwo);
	CANSparkMax *m_leftMotor[NUM_MOTORS_PER_SIDE];
	CANSparkMax *m_rightMotor[NUM_MOTORS_PER_SIDE];
    SpeedControllerGroup *m_left;
    SpeedControllerGroup *m_right;
	DifferentialDrive *m_diffdrive;
	MecanumDrive *m_mecanum;
	CANEncoder *m_leftEncoder[NUM_MOTORS_PER_SIDE];
	CANEncoder *m_rightEncoder[NUM_MOTORS_PER_SIDE];
	driveType m_type;
	bool m_needFree;
};