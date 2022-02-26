#pragma once

#include "Fermat.h"

#define COLOR_WHEEL_RADIUS			16.0
#define SPINNER_WHEEL_RADIUS		2.0
#define WHEEL_RATIO                 ((COLOR_WHEEL_RADIUS)/(SPINNER_WHEEL_RADIUS))
#define ENCODER_TICKS_PER_REV		4096
#define NUM_TICKS_PER_COLOR_WHEEL_REV	((WHEEL_RATIO)*(ENCODER_TICKS_PER_REV))

class Shooter {
	public:
		Shooter(frc::XboxController *xbox, frc::Solenoid *shooter_solenoid, Limelight *Limelight);
		void YEETUSHigh();
		void YEETUSLow();
		void TurnOnSolenoid();
		void TurnOffSolenoid();
		double FromMetersPerSecond(double speed);
		void Tick();
		void ShootFromTarmac();
		void ShootFromHangarWall();
		void DisableLimelight();
		void YEETUS();
		void GetIRValue();

	private:
		WPI_TalonSRX *m_shooter_motor;
		XboxController *m_xbox;
		Solenoid *m_shooter_solenoid;
		DigitalInput *m_shooterIR;
		Limelight *m_limelight;
};