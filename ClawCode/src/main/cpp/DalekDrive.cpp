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

bool
DalekDrive::DriveToFeet(float feet)
{
	double dis = -1.0*m_left[FRONT]->GetSelectedSensorPosition()/ENCODER_FEET;
	SmartDashboard::PutNumber("Distance", dis);

	double speed = ((MAX_SPEED*10*feet-dis)/feet)*MAX_SPEED;
	SmartDashboard::PutNumber("Speed", speed);

	if(feet>0&&abs(m_left[FRONT]->GetSelectedSensorPosition())/ENCODER_FEET <= feet){
		TankDrive(-1.0*speed, -1.0*speed, false);
		return false;
	} else if(feet<0&&abs(m_left[FRONT]->GetSelectedSensorPosition())/ENCODER_FEET <= feet){
		TankDrive(speed, speed, false);
		return false;
	}else {
		return true;
	}
}

void
DalekDrive::Stop(){
	m_left[FRONT]->Set(m_left[FRONT]->Get() * -1.0);
	m_left[REAR]->Set(m_left[REAR]->Get() * -1.0);
	m_right[FRONT]->Set(m_right[FRONT]->Get() * -1.0);
	m_right[REAR]->Set(m_right[REAR]->Get() * -1.0);
	Wait(0.01);
	TankDrive(0.0, 0.0, false);
}
