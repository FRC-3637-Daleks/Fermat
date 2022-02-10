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
	// send robot motors in the opposite direction to stop robot
	m_left[FRONT]->Set(m_left[FRONT]->Get() * -.9);
	m_left[REAR]->Set(m_left[REAR]->Get() * -.9);
	m_right[FRONT]->Set(m_right[FRONT]->Get() * -.9);
	m_right[REAR]->Set(m_right[REAR]->Get() * -.9);
	//Wait(0.1);
	//TankDrive(0.0, 0.0, false);
}

bool
DalekDrive::Turn(float degrees, bool isRight){
	/*pseudocode time
		calculate the motor power based on degrees
		move robot
		positive degrees - left forward
		negative degrees - right forward
		gear ratio 1:6
		small gear 12, big gear 72
		circumfrence is 8*pi = 25.13274123

		if distance < total distance traveled: set motor speed to how fast youre turning (1)
		else stop return false
	*/

	double radAngle = degrees * (pi / 180);
	double totalDistance = (13.5/12) * radAngle;
	double distanceTraveled = -1.0*m_left[FRONT]->GetSelectedSensorPosition()/ENCODER_FEET;
	
	double speed = ((MAX_SPEED*10*totalDistance-distanceTraveled)/totalDistance)*MAX_SPEED;
	SmartDashboard::PutNumber("Speed", speed);

	if(isRight) {
		if(totalDistance>0&&abs(m_left[FRONT]->GetSelectedSensorPosition())/ENCODER_FEET <= totalDistance){
			TankDrive(-1.0*speed, speed, false);
			return false;
		} else if(totalDistance<0&&abs(m_left[FRONT]->GetSelectedSensorPosition())/ENCODER_FEET <= totalDistance){
			TankDrive(speed, -1.0*speed, false);
			return false;
		}else {
			return true;
		}
	}

	if(!isRight) {
		if(totalDistance>0&&abs(m_left[FRONT]->GetSelectedSensorPosition())/ENCODER_FEET <= totalDistance){
			TankDrive(speed, speed, false);
			return false;
		} else if(totalDistance<0&&abs(m_left[FRONT]->GetSelectedSensorPosition())/ENCODER_FEET <= totalDistance){
			TankDrive(-1*speed, speed, false);
			return false;
		}else {
			return true;
		}
	}
}