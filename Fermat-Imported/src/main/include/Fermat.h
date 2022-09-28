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
#include <frc/system/plant/DCMotor.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableInstance.h>
#include <rev/CANSparkMax.h>
#include <ctre/Phoenix.h>
#include <DalekDrive.h>
#include <Limelight.h>
#include <RaspberryPi.h>
#include <Climb.h>
#include <Shooter.h>
#include <Intake.h>
#include <Auton.h>

// Mostly for documentation of the ip addresses of the 
// devices on the robot
#define ROBORIO         		"10.36.37.2"
#define ACCESS_POINT     		"10.36.37.1"
#define CAMERA					"10.36.37.218"
#define RASPBERRY_PI_ADDR		"10.36.37.??"
#define LIMELIGHT_ADDR			"10.36.37.11"
#define PI						3.14159265358979323846264338327 //pi

// CAN BUS devices
enum CAN_IDS {
	LEFT_FRONT_DRIVE=1,
	LEFT_REAR_DRIVE, 
	RIGHT_FRONT_DRIVE, 
	RIGHT_REAR_DRIVE,
	PCM,
	SHOOTER_MOTOR,
  	INTAKE_MOTOR,
  	CLIMB_MOTOR
 };

// Devices connected to driverstation
enum DRIVER_STATION_IO {
	XBOX, 
	LEFT_JOY, 
	RIGHT_JOY
};

enum SOLENOID_IDS {
	SHOOTER,
  	CLIMB,
  	INTAKE 
};

enum DIO {
	LOWER_IR=2,
	UPPER_IR
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
		frc::DigitalInput *m_cinput;
		frc::Compressor *m_compressor;
		DalekDrive *m_drive;
		frc::Solenoid *m_climb_solenoid;
		frc::Solenoid *m_intake_solenoid;
		frc::Solenoid *m_shooter_solenoid;
		Limelight *m_limelight;
		RaspberryPi *m_pi;
		Climb *m_climb;
		Intake *m_intake;
		Shooter *m_shooter;
		WPI_TalonFX *m_leftFront;
		Auton *m_auton;
};
