#include "Fermat.h"
#pragma once

#define COLOR_WHEEL_RADIUS			16.0
#define SPINNER_WHEEL_RADIUS		2.0
#define WHEEL_RATIO                 ((COLOR_WHEEL_RADIUS)/(SPINNER_WHEEL_RADIUS))
#define ENCODER_TICKS_PER_REV		4096
#define NUM_TICKS_PER_COLOR_WHEEL_REV	((WHEEL_RATIO)*(ENCODER_TICKS_PER_REV))

class Shooter {
	public:
	void Shooter::Spinner(XboxController *xbox, Solenoid *climb_solenoid);
    void Tick();
	void Reinit();

	private:
	WPI_TalonSRX *m_shooter;
	XboxController *m_xbox;
   	Solenoid *m_shooterSolenoid;

	void init(XboxController *xbox, DoubleSolenoid *climb_solenoid);
};