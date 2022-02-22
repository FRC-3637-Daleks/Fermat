// SPINNER MUST BE NEGATIVE

#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include "WPILibVersion.h"
#include "cameraserver/CameraServer.h"
#include <frc/AnalogGyro.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DriverStation.h>
#include <frc/Joystick.h>
#include <frc/GenericHID.h>
#include <frc/XboxController.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/DigitalInput.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <frc/system/plant/DCMotor.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
//#include <AHRS.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <DalekDrive.h>
#include <Limelight.h>
#include <RaspberryPi.h>
#include <Climb.h>
#include <Intake.h>
#include <Shooter.h>

#define PI	3.14159265358979323846

// Mostly for documentation of the ip addresses of the 
// devices on the robot
#define ROBORIO             "10.36.37.2"
#define ACCESS_POINT        "10.36.37.1"
#define FORWARD_CAMERA		"10.36.37.16"
#define REAR_CAMERA			"10.36.37.??"
#define RASPBERRY_PI_ADDR	"10.36.37.??"
#define LIMELIGHT_ADDR		"10.36.37.11"
#define LEVEL_SENSOR_ADDR   "10.36.37.??"

// CAN BUS devices
enum CAN_IDS {
	LEFT_FRONT_DRIVE = 1,
	LEFT_REAR_DRIVE = 2, 
	RIGHT_FRONT_DRIVE = 3, 
	RIGHT_REAR_DRIVE = 4,
	ROLLER_BAR = 5, 
	CONVEYOR_BELT = 6, 
	LIFT = 7, 
	TROLLEY = 8, 
	SPINNER = 9,
	PCM = 10
 };

// Devices connected to driverstation
enum DRIVER_STATION_IO {
	XBOX = 0, 
	LEFT_JOY = 1, 
	RIGHT_JOY = 2
};

// Digitial Input
enum DIGITAL_IO {
	CONVEYOR_INPUT = 0,
	CONVEYOR_STOP = 1
};

enum SOLENOID_IDS {
	CLIMB_DEPLOY = 0,
	RATCHET_LOCK = 1,
	INTAKE_DEPLOY = 2,
	SPINNER_DEPLOY = 3,
	SPINNER_EXHAUST = 4,
	CLIMB_EXHAUST = 5,
	INTAKE_EXHAUST = 6,
	NUM_SOLENOIDS
};

class Robot : public TimedRobot {
	public:
	void RobotInit() override;
	void RobotPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestInit() override;
	void TestPeriodic() override;
	void DisabledInit() override;

	private:
	frc::XboxController *m_xbox;
	frc::Joystick *m_leftStick;
	frc::Joystick *m_rightStick;
	frc::DigitalInput *m_cinput;
	//frc::Compressor *m_compressor;
	DalekDrive *m_drive;
	//AHRS *m_ahrs;
	frc::DoubleSolenoid *m_climb_solenoid;
	Limelight *m_limelight;
	RaspberryPi *m_pi;
	
	bool canDrive = true;
	bool timeChanged = false;
	double waitSeconds = 0.0, timeOffset = 0.0;
	int auton_start, auton_end;

	WPI_TalonFX *m_leftFront;
};
