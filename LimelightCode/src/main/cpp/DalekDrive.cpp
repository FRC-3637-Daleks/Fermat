#include "Fermat.h"

DalekDrive::DalekDrive() {
	m_left[FRONT]  = new WPI_TalonFX(leftFront);
	m_left[REAR]   = new WPI_TalonFX(leftRear);
	m_right[FRONT] = new WPI_TalonFX(rightFront);
	m_right[REAR]  = new WPI_TalonFX(rightRear);
}

double
DalekDrive::squareInput(double v)
{
	if (v < 0.0) {
		return -(v * v);
	}
	return (v * v);
}

void
DalekDrive::TankDrive(double l, double r, bool squaredInputs)
{
	if(squaredInputs) {
		l = squareInput(l);
		r = squareInput(r);
	}
	m_left[FRONT]->Set(l * MAX_SPEED);
	m_left[REAR]->Set(l * MAX_SPEED);
	m_right[FRONT]->Set(r * MAX_SPEED * -1.0);
	m_right[REAR]->Set(r * MAX_SPEED * -1.0);
}

void
DalekDrive::TankDrive(Joystick* leftStick, Joystick* rightStick, bool squaredInputs)
{
	TankDrive(leftStick->GetY(), rightStick->GetY(), squaredInputs);
}

void
DalekDrive::TankDrive(Joystick& leftStick, Joystick& rightStick, bool squaredInputs)
{
		TankDrive(leftStick.GetY(), rightStick.GetY(), squaredInputs);
}