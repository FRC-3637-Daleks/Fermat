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
#include <frc/Compressor.h>
#include <frc/DoubleSolenoid.h>
#include <frc/system/plant/DCMotor.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <DalekDrive.h>
#include <Limelight.h>
#include <RaspberryPi.h>
#include <Climb.h>

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
	LEFT_FRONT_DRIVE = 0,
	LEFT_REAR_DRIVE = 1, 
	RIGHT_FRONT_DRIVE = 2, 
	RIGHT_REAR_DRIVE = 3,
	CLIMB_MOTOR = 4,
  INTAKE_MOTOR = 5,
  SHOOTER_MOTOR = 6,
  PCM = 7
 };

// Devices connected to driverstation
enum DRIVER_STATION_IO {
	XBOX = 0, 
	LEFT_JOY = 1, 
	RIGHT_JOY = 2
};

enum SOLENOID_IDS {
	INTAKE = 0,
  CLIMB = 1,
  SHOOTER = 2
};

enum DIO {
  upperLimit = 0, 
  lowerLimit = 1
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
	frc::Compressor *m_compressor;
	DalekDrive *m_drive;
	frc::Solenoid *m_climb_solenoid;
  frc::Solenoid *m_intake_solenoid;
  frc::Solenoid *m_shooter_solenoid;
	Limelight *m_limelight;
	RaspberryPi *m_pi;
	
	bool canDrive = true;
	bool timeChanged = false;
	double waitSeconds = 0.0, timeOffset = 0.0;
	int auton_start, auton_end;

	WPI_TalonFX *m_leftFront;
};
