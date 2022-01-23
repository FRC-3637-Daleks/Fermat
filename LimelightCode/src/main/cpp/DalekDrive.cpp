#include "Fermat.h"

using namespace frc;
using namespace frc2;
using namespace rev;

DalekDrive::DalekDrive(int leftFront, int leftRear, int rightFront, int rightRear, DalekDrive::driveType t)
{
	m_leftMotor[FRONT]   = new CANSparkMax(leftFront, CANSparkMax::MotorType::kBrushless);
	if (m_leftMotor[FRONT] == NULL)
		std::bad_alloc();
	m_rightMotor[FRONT]  = new CANSparkMax(rightFront, CANSparkMax::MotorType::kBrushless);
	if (m_rightMotor[FRONT] == NULL)
		std::bad_alloc();
	m_leftMotor[REAR]    = new CANSparkMax(leftRear, CANSparkMax::MotorType::kBrushless);
	if (m_leftMotor[REAR] == NULL)
		std::bad_alloc();
	m_rightMotor[REAR]   = new CANSparkMax(rightRear, CANSparkMax::MotorType::kBrushless);
	if (m_rightMotor[REAR] == NULL)
		std::bad_alloc();
	m_left  = new SpeedControllerGroup(*m_leftMotor[FRONT], *m_leftMotor[REAR]);
    m_right = new SpeedControllerGroup(*m_rightMotor[FRONT], *m_rightMotor[REAR]);
	m_type  = t;

	if(t == DalekDrive::driveType::kDifferential) {
		m_diffdrive      	= new DifferentialDrive(*m_left, *m_right);
	}
	else {
	    m_mecanum        	= new MecanumDrive(*m_leftMotor[FRONT], *m_leftMotor[REAR], *m_rightMotor[FRONT], *m_rightMotor[REAR]);
	}
	m_leftEncoder[FRONT]	= new CANEncoder(*m_leftMotor[FRONT]);
	m_leftEncoder[REAR]  	= new CANEncoder(*m_leftMotor[REAR]);
	m_rightEncoder[FRONT]	= new CANEncoder(*m_rightMotor[FRONT]);
	m_rightEncoder[REAR] 	= new CANEncoder(*m_rightMotor[REAR]);
	m_needFree          	= true;
	InitDalekDrive();
}

DalekDrive::DalekDrive(CANSparkMax* leftFront, CANSparkMax* leftRear, CANSparkMax* rightFront, CANSparkMax* rightRear, DalekDrive::driveType t)
{
	m_leftMotor[FRONT]   = leftFront;
	m_rightMotor[FRONT]  = rightFront;
	m_leftMotor[REAR]    = leftRear;
	m_rightMotor[REAR]   = rightRear;    	
	m_left               = new SpeedControllerGroup(*m_leftMotor[FRONT], *m_leftMotor[REAR]);
    m_right              = new SpeedControllerGroup(*m_rightMotor[FRONT], *m_rightMotor[REAR]);
	m_type               = t;
	if(t == DalekDrive::driveType::kDifferential) {
		m_diffdrive      = new DifferentialDrive(*m_left, *m_right);
	}
	else {   
		m_mecanum        = new MecanumDrive(*m_leftMotor[FRONT], *m_leftMotor[REAR], *m_rightMotor[FRONT], *m_rightMotor[REAR]);
	}
	m_needFree           = false;
	InitDalekDrive();
}

DalekDrive::DalekDrive(CANSparkMax& leftFront, CANSparkMax& leftRear, CANSparkMax& rightFront, CANSparkMax& rightRear, DalekDrive::driveType t)
{
	m_leftMotor[FRONT]   = &leftFront;
	m_rightMotor[FRONT]  = &rightFront;
	m_leftMotor[REAR]    = &leftRear;
	m_rightMotor[REAR]   = &rightRear;
    m_left               = new SpeedControllerGroup(*m_leftMotor[FRONT], *m_leftMotor[REAR]);
    m_right              = new SpeedControllerGroup(*m_rightMotor[FRONT], *m_rightMotor[REAR]);
	m_type               = t;
	if(m_type == DalekDrive::driveType::kDifferential) {
		m_diffdrive      = new DifferentialDrive(*m_left, *m_right);
	}
	else {
		m_mecanum        = new MecanumDrive(*m_leftMotor[FRONT], *m_leftMotor[REAR], *m_rightMotor[FRONT], *m_rightMotor[REAR]);
	}
	m_needFree           = false;
	InitDalekDrive();
}

DalekDrive::~DalekDrive()
{
	if (m_type == DalekDrive::driveType::kDifferential) {
		delete m_diffdrive;
	} else {
		delete m_mecanum;
	}
    delete m_left;
    delete m_right;
	if (m_needFree) {
		delete m_leftMotor[FRONT];
		delete m_rightMotor[FRONT];
		delete m_leftMotor[REAR];
		delete m_rightMotor[REAR];
	}
	m_needFree = false;
	return;
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
DalekDrive::TankDrive(Joystick* leftStick, Joystick* rightStick, bool squaredInputs)
{
	if (m_type == DalekDrive::driveType::kDifferential) {
		m_diffdrive->TankDrive(leftStick->GetY() * MAX_SPEED, rightStick->GetY() * MAX_SPEED, squaredInputs);
		SmartDashboard::PutNumber("joystick left", leftStick->GetY());
		SmartDashboard::PutNumber("right joystick", rightStick->GetY());
		SmartDashboard::PutNumber("right encoder", m_rightEncoder[FRONT]->GetVelocity());
		SmartDashboard::PutNumber("left encoder", m_leftEncoder[FRONT]->GetVelocity());
		SmartDashboard::PutNumber("right output", m_rightMotor[FRONT]->GetAppliedOutput());
		SmartDashboard::PutNumber("left output", m_leftMotor[FRONT]->GetAppliedOutput());
		SmartDashboard::PutNumber("right current", m_rightMotor[FRONT]->GetOutputCurrent());
		SmartDashboard::PutNumber("left current", m_leftMotor[FRONT]->GetOutputCurrent());
		SmartDashboard::PutNumber("right voltage", m_rightMotor[FRONT]->GetBusVoltage());
		SmartDashboard::PutNumber("left voltage", m_leftMotor[FRONT]->GetBusVoltage());
	} else {
		double l = leftStick->GetY(), r = rightStick->GetY();
		if(squaredInputs) {
			l = squareInput(l);
			r = squareInput(r);
		}
		if (l * r < 0) {
			l *= .5;
			r *= .5;
		}
		m_left->Set(l * MAX_SPEED);
		m_right->Set(r * MAX_SPEED);
	}
}

void
DalekDrive::TankDrive(Joystick& leftStick, Joystick& rightStick, bool squaredInputs)
{
	if (m_type == DalekDrive::driveType::kDifferential) {
		m_diffdrive->TankDrive(leftStick.GetY() * MAX_SPEED, rightStick.GetY() * MAX_SPEED, squaredInputs);	
	} else {
		double l = leftStick.GetY(), r = rightStick.GetY();
		if(squaredInputs) {
			l = squareInput(l);
			r = squareInput(r);
		}
		m_left->Set(l * MAX_SPEED);
		m_right->Set(r * MAX_SPEED);
	}
}

void
DalekDrive::TankDrive(double leftValue, double rightValue, bool squaredInputs)
{
	if (m_type == DalekDrive::driveType::kDifferential) {
		m_diffdrive->TankDrive(leftValue * MAX_SPEED, rightValue * MAX_SPEED, squaredInputs);
	} else {
		double l = leftValue, r = rightValue;
		if(squaredInputs) {
			l = squareInput(l);
			r = squareInput(r);
		}
		m_left->Set(l * MAX_SPEED);
		m_right->Set(r * MAX_SPEED);
	}
}

void
DalekDrive::ArcadeDrive(Joystick* stick, bool squaredInputs)
{
	if(m_type == DalekDrive::driveType::kDifferential) {
		m_diffdrive->ArcadeDrive(stick->GetX() * MAX_SPEED, stick->GetY() * MAX_SPEED, squaredInputs);
	}
}

void
DalekDrive::ArcadeDrive(Joystick& stick, bool squaredInputs)
{
	if(m_type == DalekDrive::driveType::kDifferential) {
		m_diffdrive->ArcadeDrive(stick.GetX() * MAX_SPEED, stick.GetY() * MAX_SPEED, squaredInputs);
	}
}

void
DalekDrive::ArcadeDrive(double moveValue, double rotateValue, bool squaredInputs)
{
	if(m_type == DalekDrive::driveType::kDifferential) {
		m_diffdrive->ArcadeDrive(moveValue * MAX_SPEED, rotateValue, squaredInputs);
	}
}

void
DalekDrive::SetLeftRightMotorOutputs(double leftOutput, double rightOutput)
{
	m_left->Set(leftOutput * MAX_SPEED);
	m_right->Set(rightOutput * MAX_SPEED);
}

void 
DalekDrive::Polar(Joystick *stick)
{
	if(m_type == DalekDrive::driveType::kMecanum) {
		m_mecanum->DrivePolar(stick->GetY() * MAX_SPEED, stick->GetX() * MAX_SPEED, stick->GetTwist());
	}
}

void
DalekDrive::Polar(Joystick &stick)
{
	if(m_type == DalekDrive::driveType::kMecanum) {
		m_mecanum->DrivePolar(stick.GetY() * MAX_SPEED, stick.GetX() * MAX_SPEED, stick.GetTwist());
	}
}
	
void
DalekDrive::Polar(double magnitude, double angle, double zRotation)
{
	if(m_type == DalekDrive::driveType::kMecanum) {
		m_mecanum->DrivePolar(magnitude * MAX_SPEED, angle, zRotation);
	}
}

void
DalekDrive::Cartesian(Joystick *stick,	double gyroAngle)
{
	if(m_type == DalekDrive::driveType::kMecanum) {
		m_mecanum->DriveCartesian(-stick->GetX() * MAX_SPEED, stick->GetY() * MAX_SPEED, -stick->GetZ(), gyroAngle);
	}
}

void 
DalekDrive::Cartesian(Joystick &stick, double gyroAngle)
{
	if(m_type == DalekDrive::driveType::kMecanum) {
		m_mecanum->DriveCartesian(-stick.GetX() * MAX_SPEED, stick.GetY() * MAX_SPEED, -stick.GetTwist(), gyroAngle);
	}
}

void 
DalekDrive::Cartesian(double ySpeed, double xSpeed, double zRotation, double gyroAngle)
{
	if(m_type == DalekDrive::driveType::kMecanum) {
		m_mecanum->DriveCartesian(ySpeed * MAX_SPEED, xSpeed * MAX_SPEED, zRotation, gyroAngle);
	}
}

double
DalekDrive::GetVelocity()
{
	SmartDashboard::PutNumber("right encoder", m_rightEncoder[FRONT]->GetVelocity());
	SmartDashboard::PutNumber("left encoder", m_leftEncoder[FRONT]->GetVelocity());
	return WHEEL_CIRCUMFERENCE * (m_leftEncoder[FRONT]->GetVelocity() + m_rightEncoder[FRONT]->GetVelocity()) / (120 * GEAR_RATIO); // right is incorrect so im cganhing it here
}
	
void
DalekDrive::SetInvertedMotor(int side, bool isInverted)
{
	switch(side) {
	case LEFT:
		m_leftMotor[FRONT]->SetInverted(isInverted);
		m_leftMotor[REAR]->SetInverted(isInverted);
		break;

	case RIGHT:
		m_rightMotor[FRONT]->SetInverted(isInverted);
		m_rightMotor[REAR]->SetInverted(isInverted);
		break;
	default:
		break;
	}
}

void
DalekDrive::InitDalekDrive(void)
{
	// Setup Encoder access
	m_leftEncoder[FRONT] = new CANEncoder(*m_leftMotor[FRONT]);
	m_leftEncoder[REAR]  = new CANEncoder(*m_leftMotor[REAR]);
	m_rightEncoder[FRONT]= new CANEncoder(*m_rightMotor[FRONT]);
	m_rightEncoder[REAR] = new CANEncoder(*m_rightMotor[REAR]);
	m_leftEncoder[FRONT]->SetInverted(true);
	m_leftEncoder[REAR]->SetInverted(true);
	m_rightEncoder[FRONT]->SetInverted(false);
	m_rightEncoder[REAR]->SetInverted(false);

	// Configure the SparkMax
    m_leftMotor[FRONT]->SetCANTimeout(CAN_TIMEOUT);
	m_leftMotor[FRONT]->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    m_leftMotor[FRONT]->SetSmartCurrentLimit(STALL_LIMIT, FREE_LIMIT, 0);
	m_leftMotor[FRONT]->SetOpenLoopRampRate(RAMP_RATE);
	m_leftMotor[FRONT]->SetInverted(true);

    m_rightMotor[FRONT]->SetCANTimeout(CAN_TIMEOUT);
	m_rightMotor[FRONT]->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    m_rightMotor[FRONT]->SetSmartCurrentLimit(STALL_LIMIT, FREE_LIMIT, 0);
	m_rightMotor[FRONT]->SetOpenLoopRampRate(RAMP_RATE);
	m_rightMotor[FRONT]->SetInverted(true);

    m_leftMotor[REAR]->SetCANTimeout(CAN_TIMEOUT);
  	m_leftMotor[REAR]->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    m_leftMotor[REAR]->SetSmartCurrentLimit(STALL_LIMIT, FREE_LIMIT, 0);
	m_leftMotor[REAR]->SetOpenLoopRampRate(RAMP_RATE);
	m_leftMotor[REAR]->SetInverted(true);

    m_rightMotor[REAR]->SetCANTimeout(CAN_TIMEOUT);
	m_rightMotor[REAR]->SetIdleMode(CANSparkMax::IdleMode::kBrake);
    m_rightMotor[REAR]->SetSmartCurrentLimit(STALL_LIMIT, FREE_LIMIT, 0);
	m_rightMotor[REAR]->SetOpenLoopRampRate(RAMP_RATE);
	m_rightMotor[REAR]->SetInverted(true);

    m_leftMotor[FRONT]->StopMotor();  m_leftMotor[REAR]->StopMotor();
    m_rightMotor[FRONT]->StopMotor(); m_rightMotor[REAR]->StopMotor();
}

float
DalekDrive::DeadZone(float input, float range) {
    if (abs(input) < range) {
        return 0;
    } else {
        if (input > 0) {
            return (abs(input) - range) / (1 - range);
        } else {
            return -1 * (abs(input) - range) / (1 - range);
        }
    }
}

void
DalekDrive::printFaults(int p, int faults)
{
    switch(p) {
	case LEFT: 
		SmartDashboard::PutNumber("Left Drive Motor reported faults", faults);
		if(m_leftMotor[REAR]) {
			SmartDashboard::PutNumber("Left slave status", m_leftMotor[REAR]->GetFaults());
		}
        break; 
    case RIGHT:
		SmartDashboard::PutNumber("Right Drive Motor reported faults", faults);
		if(m_rightMotor[REAR]) {
			SmartDashboard::PutNumber("Right slave status", m_rightMotor[REAR]->GetFaults());
		}
        break;
    default:
        break;
    }
	return;
}

bool
DalekDrive::DriveOk()
{
	int mstat;
	#ifdef MOTOR_PRINT
	// Update dashboard of current draw for motors
	SmartDashboard::PutNumber("Left Front current",  m_leftMotor[FRONT]->GetOutputCurrent());
	SmartDashboard::PutNumber("Left Front Encoder position", m_leftEncoder[FRONT]->GetPosition());
	SmartDashboard::PutNumber("Left Rear Motor current", m_leftMotor[REAR]->GetOutputCurrent());
	SmartDashboard::PutNumber("Left Rear Encoder position", m_leftEncoder[REAR]->GetPosition());
	SmartDashboard::PutNumber("Right Front current", m_rightMotor[FRONT]->GetOutputCurrent());
	SmartDashboard::PutNumber("Right Front Encoder position", m_rightEncoder[FRONT]->GetPosition());
	SmartDashboard::PutNumber("Right Rear Motor current", m_rightMotor[REAR]->GetOutputCurrent());
	SmartDashboard::PutNumber("Right Rear Encoder position", m_rightEncoder[REAR]->GetPosition());
	#endif

	// Check for motor faults
	mstat = m_leftMotor[FRONT]->GetFaults();
	if(mstat != 0) {
		printFaults(LEFT, mstat);
		return false;
	}
	mstat = m_leftMotor[FRONT]->GetStickyFaults();
	if(mstat) {
		printFaults(LEFT, mstat);
		return false;
	}

	mstat = m_rightMotor[FRONT]->GetFaults();
	if(mstat) {
		printFaults(RIGHT, mstat);
		return false;
	}
	mstat = m_rightMotor[FRONT]->GetStickyFaults();
	if(mstat) {
		printFaults(RIGHT, mstat);
		return false;
	}
	return true;
}

// Use SetLeftRightMotorOutputs(double leftOutput, double rightOutput) instead of using these single ones
void
DalekDrive::DriveBaseSquare(int leftSensor, int rightSensor) {
	#ifdef USE_LIDAR
		if (LidarInRange (leftSensor, rightSensor)) {
			if (rightSensor + LidarError > leftSensor || rightSensor - LidarError > leftSensor) {
				// Turn left
				SetLeftRightMotorOutputs(PositiveMotorSpeed, NegativeMotorSpeed);
			}
			else if (leftSensor + LidarError > rightSensor || leftSensor - LidarError > rightSensor) {
				// Turn Right
				SetLeftRightMotorOutputs(NegativeMotorSpeed, PositiveMotorSpeed);
			}
			else {
				// STOP
				SetLeftRightMotorOutputs(NullMotorSpeed, NullMotorSpeed);
			}
			SmartDashboard::PutNumber("Left Motor Master", m_leftMotor[FRONT]->Get());
			SmartDashboard::PutNumber("Left Motor Slave", m_leftMotor[REAR]->Get());
			SmartDashboard::PutNumber("Left Motor Master", m_leftMotor[FRONT]->Get());
			SmartDashboard::PutNumber("Left Motor Slave", m_leftMotor[REAR]->Get());
		}
	#endif
}

bool
DalekDrive::LidarInRange (int sensorOne, int sensorTwo) {
	#ifdef USE_LIDAR
		if (sensorOne >= 1000 || sensorTwo >= 1000) {
			SmartDashboard::PutBoolean("Lidar Status", 0);
			return false;
		}
		// If less than 1000
		SmartDashboard::PutBoolean("Lidar Status", 1);
		return true;
	#endif
	return false;
}
