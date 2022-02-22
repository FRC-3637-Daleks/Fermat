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
DalekDrive::DriveToFeet(double feet)
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
DalekDrive::StopLeft(){
	// send robot left motors in the opposite direction to stop robot
	m_left[FRONT]->Set(m_left[FRONT]->Get() * -.9);
	m_left[REAR]->Set(m_left[REAR]->Get() * -.9);
	
	//Wait(0.1);
	//TankDrive(0.0, 0.0, false);
}

void
DalekDrive::StopRight() {
	// send robot left motors in the opposite direction to stop robot
	m_right[FRONT]->Set(m_right[FRONT]->Get() * -.9);
	m_right[REAR]->Set(m_right[REAR]->Get() * -.9);
}

bool
DalekDrive::Turn(double degrees){
	/*pseudocode time
		calculate the motor power based on degrees
		move robot
		positive degrees - left forward
		negative degrees - right forward
		gear ratio 1:6
		small gear 12, big gear 72
		circumfrence 8*pi = 25.13274123

		if distance < total distance traveled: set motor speed to how fast youre turning (1)
		else stop return false
	*/
	
	//adjust the degrees to account for the motors overshooting
	//degrees = degrees>0?(degrees - 20):(degrees+18); //one side is slightly faster than the other
	double radAngle = degrees * (pi / 180);
	double totalDistance = (13.5/12) * radAngle;
	double distanceTraveled = -1.0*m_left[FRONT]->GetSelectedSensorPosition()/ENCODER_FEET;
	SmartDashboard::PutNumber("Total Distance", totalDistance);
	
	//double speed = ((MAX_SPEED*10*totalDistance-distanceTraveled)/totalDistance)*MAX_SPEED;
	
	double speed = ((MAX_SPEED*10*abs(totalDistance)-abs(distanceTraveled))/abs(totalDistance))*MAX_SPEED;
	SmartDashboard::PutNumber("Speed", speed);
	if(totalDistance>0&&m_left[FRONT]->GetSelectedSensorPosition()/ENCODER_FEET <= totalDistance&&speed>.31){
		TankDrive(-1.0*speed, speed, false);
		return false;
	} else if(totalDistance<0&&m_left[FRONT]->GetSelectedSensorPosition()/ENCODER_FEET >= totalDistance&&speed>.31){
		TankDrive(speed, -1.0*speed, false);
		return false;
	}else {
		return true;
	}
}

void
DalekDrive::MoveRight(Joystick* rightStick, bool squaredInputs) {
	
	//if inputs are doubled, double the inputs
	double r = rightStick->GetY();
	if(squaredInputs) {
		r = squareInput(rightStick->GetY());
	}
	
	// Move only the right motor without affecting the left
	m_right[FRONT]->Set(-1.0*r*MAX_SPEED);
	m_right[REAR]->Set(-1.0*r*MAX_SPEED);
}
void
DalekDrive::MoveLeft(Joystick* leftStick, bool squaredInputs) {

	//if inputs are doubled, double the inputs
	double l = leftStick->GetY();
	if(squaredInputs) {
		l = squareInput(leftStick->GetY());
	}
	
	// Move only the left motor without affecting the right
	m_left[FRONT]->Set(l*MAX_SPEED);
	m_left[REAR]->Set(l*MAX_SPEED);
}

double
DalekDrive::GetRight(){
	return m_right[FRONT]->Get();
}

double
DalekDrive::GetLeft(){
	return m_left[FRONT]->Get();
}