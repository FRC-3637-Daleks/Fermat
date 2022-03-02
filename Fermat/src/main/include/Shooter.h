#pragma once

#include "Fermat.h"

// Currently Not used but could be used (especially if motors dont work that well)
#define COLOR_WHEEL_RADIUS				16.0
#define SPINNER_WHEEL_RADIUS			2.0
#define WHEEL_RATIO						((COLOR_WHEEL_RADIUS)/(SPINNER_WHEEL_RADIUS))
#define ENCODER_TICKS_PER_REV			4096
#define NUM_TICKS_PER_COLOR_WHEEL_REV	((WHEEL_RATIO)*(ENCODER_TICKS_PER_REV))

class Shooter {
	public:
		Shooter(DalekDrive *drive, frc::XboxController *xbox, frc::Solenoid *shooter_solenoid, Limelight *limelight);
		void SetHigh();
		void SetLow();
		void SetMiss();
		void Shoot();
		void TurnOnSolenoid();
		void TurnOffSolenoid();
		double FromMetersPerSecond(double speed);
		void Tick();
		void ManualShooting();
		void DisableLimelight();


	private:
		bool autoShoot = true;
		WPI_TalonSRX *m_shooter_motor;
		XboxController *m_xbox;
		Solenoid *m_shooter_solenoid;
		DigitalInput *m_shooterIR;
		Limelight *m_limelight;
		DalekDrive *m_drive;
};