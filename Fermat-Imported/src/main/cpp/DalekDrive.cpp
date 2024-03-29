#include "Fermat.h"

DalekDrive::DalekDrive(XboxController *xbox) {
	m_left[FRONT]  = new WPI_TalonFX(LEFT_FRONT_DRIVE);
	m_left[REAR]   = new WPI_TalonFX(LEFT_REAR_DRIVE);
	m_right[FRONT] = new WPI_TalonFX(RIGHT_FRONT_DRIVE);
	m_right[REAR]  = new WPI_TalonFX(RIGHT_REAR_DRIVE);
	// m_left[FRONT]->SetNeutralMode(Brake);
	// m_left[REAR]->SetNeutralMode(Brake);
	// m_right[FRONT]->SetNeutralMode(Brake);
	// m_right[REAR]->SetNeutralMode(Brake);
	m_leftStick   = new frc::Joystick(LEFT_JOY);
    m_rightStick  = new frc::Joystick(RIGHT_JOY);
	m_xbox = xbox;
	canDrive = true;
}

double
DalekDrive::squareInput(double v)
{
	if (v < 0.0) {
		return -(v * v);
	}
	return (v * v);
}


// TankDrive with slow speed and squaredInputs options (maybe take away squared inputs)
void
DalekDrive::TankDrive(double l, double r, bool squaredInputs, bool isSlow)
{
	if(isSlow){
		if(squaredInputs) {
			l = squareInput(l);
			r = squareInput(r);
		}
		m_left[FRONT]->Set(l * MAX_SPEED * SLOW_SPEED);
		m_left[REAR]->Set(l * MAX_SPEED * SLOW_SPEED);
		m_right[FRONT]->Set(r * MAX_SPEED * SLOW_SPEED * -1.0);
		m_right[REAR]->Set(r * MAX_SPEED * SLOW_SPEED * -1.0);
	}else{
		if(squaredInputs) {
			l = squareInput(l);
			r = squareInput(r);
		}
		m_left[FRONT]->Set(l * MAX_SPEED);
		m_left[REAR]->Set(l * MAX_SPEED);
		m_right[FRONT]->Set(r * MAX_SPEED * -1.0);
		m_right[REAR]->Set(r * MAX_SPEED * -1.0);
	}
}

//Another way to call the method but you just put in joysticks
void
DalekDrive::TankDrive(Joystick* leftStick, Joystick* rightStick, bool squaredInputs, bool isSlow)
{
	TankDrive(leftStick->GetY(), rightStick->GetY(), squaredInputs, isSlow);
}

//Another way to call the method but you just put in joysticks (Using References Instead of Pointers)
void
DalekDrive::TankDrive(Joystick& leftStick, Joystick& rightStick, bool squaredInputs, bool isSlow)
{
	TankDrive(leftStick.GetY(), rightStick.GetY(), squaredInputs, isSlow);
}

// Drive to a spot but decrease speed as you go on
bool
DalekDrive::DriveToFeet(double feet)
{
	double dis = -1.0 * m_left[FRONT]->GetSelectedSensorPosition() / ENCODER_FEET;
	// SmartDashboard::PutNumber("DriveToFeet Dist", dis);

	double speed = .5 * SLOW_SPEED * MAX_SPEED;
	// SmartDashboard::PutNumber("DriveToFeet Speed", speed);

	if(feet > 0 && abs(m_left[FRONT]->GetSelectedSensorPosition()) / ENCODER_FEET <= feet){
		TankDrive(-1.0 * speed, -1.0 * speed, false, false);
		return false;
	} else if(feet < 0 && abs(m_left[FRONT]->GetSelectedSensorPosition()) / ENCODER_FEET <= feet){
		TankDrive(speed, speed, false, false);
		return false;
	}else {
		return true;
	}
	SmartDashboard::PutNumber("Encoder Foot", m_left[FRONT]->GetSelectedSensorPosition() / ENCODER_FEET);

}

//Stop only the left 
void
DalekDrive::StopLeft(){
	// send robot left motors in the opposite direction to stop robot
	m_left[FRONT]->Set(0.0);
	m_left[REAR]->Set(0.0);
}

//Stop only the right
void
DalekDrive::StopRight() {
	// send robot left motors in the opposite direction to stop robot
	m_right[FRONT]->Set(0.0);
	m_right[REAR]->Set(0.0);
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
	
	double radAngle = degrees * (PI / 180);
	double totalDistance = (13.5 / 12) * radAngle;
	double distanceTraveled = -1.0 * m_left[FRONT]->GetSelectedSensorPosition() / ENCODER_FEET;
	
	SmartDashboard::PutNumber("Turn TotalDist", totalDistance);
	SmartDashboard::PutNumber("Turn CurrentDist", m_left[FRONT]->GetSelectedSensorPosition()/ENCODER_FEET);

	if((totalDistance > 0) && (m_left[FRONT]->GetSelectedSensorPosition() / ENCODER_FEET) <= (totalDistance - TURNING_ERROR)){
		TankDrive(-1.0, 1.0, false, true);
		SmartDashboard::PutBoolean("Turn GOOD", false);
		return false;
	} else if((totalDistance < 0) && (m_left[FRONT]->GetSelectedSensorPosition() / ENCODER_FEET) >= (totalDistance + TURNING_ERROR)){
		TankDrive(1.0, -1.0, false, true);
		SmartDashboard::PutBoolean("Turn GOOD", false);
		return false;
	}else {
		StopLeft();
		StopRight();
		SmartDashboard::PutBoolean("Turn GOOD", true);
		return true;
	}
}

//Move only the right side (uses Joysticks) (Might want a method without a joystick like TankDrive)
void
DalekDrive::MoveRight(Joystick* rightStick, bool squaredInputs, bool isSlow) {
	if(isSlow){
		//if inputs are doubled, double the inputs
		double r = rightStick->GetY();
		if(squaredInputs) {
			r = squareInput(rightStick->GetY());
		}
		
		// Move only the right motor without affecting the left
		m_right[FRONT]->Set(-1.0 * SLOW_SPEED * r * MAX_SPEED);
		m_right[REAR]->Set(-1.0 * SLOW_SPEED * r * MAX_SPEED);
	}else{
		//if inputs are doubled, double the inputs
		double r = rightStick->GetY();
		if(squaredInputs) {
			r = squareInput(rightStick->GetY());
		}
		
		// Move only the right motor without affecting the left
		m_right[FRONT]->Set(-1.0*r*MAX_SPEED);
		m_right[REAR]->Set(-1.0*r*MAX_SPEED);
	}
}

//Move only the left side (uses Joysticks) (Might want a method without a joystick like TankDrive)
void
DalekDrive::MoveLeft(Joystick* leftStick, bool squaredInputs, bool isSlow) {
	
	// If the motor is slow set the speed to the slow speed (percent of fast speed)
	if(isSlow){
		//if inputs are doubled, double the inputs
		double l = leftStick->GetY();
		if(squaredInputs) {
			l = squareInput(leftStick->GetY());
		}
		
		// Move only the left motor without affecting the right
		m_left[FRONT]->Set(l * MAX_SPEED * SLOW_SPEED);
		m_left[REAR]->Set(l * MAX_SPEED * SLOW_SPEED);
	}else{
		//if inputs are doubled, double the inputs
		double l = leftStick->GetY();
		if(squaredInputs) {
			l = squareInput(leftStick->GetY());
		}
		
		// Move only the left motor without affecting the right
		m_left[FRONT]->Set(l*MAX_SPEED);
		m_left[REAR]->Set(l*MAX_SPEED);
	}
}

void
DalekDrive::ResetEncoder(){
	m_left[FRONT]->SetSelectedSensorPosition(0);
}

double
DalekDrive::GetRight(){
	return m_right[FRONT]->Get();
}

double
DalekDrive::GetLeft(){
	return m_left[FRONT]->Get();
}

//For other classes to access Set canDrive (maybe make canDrive public)
void
DalekDrive::SetCanDrive(bool drive){
	canDrive = drive;
}

bool 
DalekDrive::GetCanDrive(){
	return canDrive;
}

/*
  Left Joystick - Move left motors
  Right Joystick - Move right motors
  Left Joystick Trigger - Brake left
  Right Joystick Trigger - Brake right
  Thumb Button Right Joystick - Slow mode (30% slower)
  Button 4 - Turn 10 Degrees Left
  Button 5 - Turn 10 Degrees Right
*/
void
DalekDrive::Tick(){
	m_left[FRONT]->SetNeutralMode(Coast);
	m_left[REAR]->SetNeutralMode(Coast);
	m_right[FRONT]->SetNeutralMode(Coast);
	m_right[REAR]->SetNeutralMode(Coast);
	
	if (m_leftStick->GetRawButton(5)){
		!Turn(10);
	} else if (m_leftStick->GetRawButton(4)){
		!Turn(-10);
	} else if (m_leftStick->GetRawButton(2)) {
		canDrive=true;
	} else if(canDrive) {
		//Check to see if slowmo is active
		if(m_rightStick->GetRawButton(2)){
			driveSlow = true;
		}else{
			driveSlow = false;
		}

		//Check for the brakes and move accordingly
		if (m_leftStick->GetTrigger()&&!m_rightStick->GetTrigger()){
			StopLeft();
			MoveRight(m_rightStick, false, driveSlow);
			SmartDashboard::PutNumber("LeftMotor Value", GetLeft());
		} else if (m_rightStick->GetTrigger()&&!m_leftStick->GetTrigger()){
			StopRight();
			MoveLeft(m_leftStick, false, driveSlow);    
			SmartDashboard::PutNumber("RightMotor Value",  GetRight());    
		} else if (m_leftStick->GetTrigger()&&m_rightStick->GetTrigger()){
			StopLeft();
			StopRight();
		} else {
			TankDrive(m_leftStick, m_rightStick, false, driveSlow);
		}

		// I think this can just be an else in the above statment		
		// if (!(m_leftStick->GetTrigger()||m_rightStick->GetTrigger())){
		// 	TankDrive(m_leftStick, m_rightStick, false, driveSlow);
		// }

		ResetEncoder();
	}
	
	// Put the variables on the board
	SmartDashboard::PutBoolean("Drive Active", canDrive);
	SmartDashboard::PutBoolean("Slow Active", driveSlow);	
}