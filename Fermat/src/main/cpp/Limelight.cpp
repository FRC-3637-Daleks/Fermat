#include "Fermat.h"
#include "Limelight.h"

Limelight::Limelight(DalekDrive *drive) {
    m_drive = drive;
}

double Limelight::CalcDistance(double area) // (m)
{
  return (DIST_EXPONENT*pow(area, DIST_EXPONENT))*0.0254;
}

double Limelight::CalcVelocity(double points, double xDistance) // (m/s)
{
	double height = (points==1)?LOW_SHOOT:HIGH_SHOOT - START_HEIGHT;
	SmartDashboard::PutNumber("Shoot Velocity",sqrt( (4.9*pow(xDistance, 2)) / ( pow(cos(SHOOT_ANGLE), 2) * (height - (xDistance * (tan(SHOOT_ANGLE)))) ) ));
	return sqrt( (4.9*pow(xDistance, 2)) / ( pow(cos(SHOOT_ANGLE), 2) * (height - (xDistance * (tan(SHOOT_ANGLE)))) ) );
}

double Limelight::CalcVelocity(double points) // (m/s)
{
	double area = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta", 0.0);
	double xDistance = CalcDistance(DIST_EXPONENT*pow(area, DIST_EXPONENT)*0.0254);
	return CalcVelocity(points, xDistance);
}

double Limelight::CalcTurnAngle(double xPos){
	SmartDashboard::PutNumber("TurnAngle", ANGLE_PRODUCT*xPos + ANGLE_OFFSET);
	return ANGLE_PRODUCT*xPos + ANGLE_OFFSET;
}

double Limelight::GetAngle(){
	return angle;
}

void Limelight::LightOff() {
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
}

void Limelight::LightOn() {
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
}

void Limelight::Tick() { 
	
	//Set Limelight area (ta) to a variable
	area = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta", 0.0);

	//ANGLE NEEDS TO BE ACCOUNTED FOR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (degrees please)
	angle = 0; // it would be something like this: nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta", 0.0);

	// set a variable distance using a linear regression of ax+b using tvert on desmos
	distance = CalcDistance(area);

	//display the hypothetical velocity for the wheel
	low_velocity = CalcVelocity(1, distance);
	high_velocity = CalcVelocity(2, distance);

	//Put the X-Distance the robot is from the target on the dashboard 
	SmartDashboard::PutNumber("Horizontal Distance from the Target", distance);

	//Put the hypothetical velocity
	SmartDashboard::PutNumber("Flywheel Speed for Low Shot", low_velocity);
	SmartDashboard::PutNumber("Flywheel Speed for High Shot", high_velocity);

	//Display all the Limelight Varibles on the Smart Dashboard
	SmartDashboard::PutNumber("ta", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta", 0.0));
	SmartDashboard::PutNumber("tx", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0));
	SmartDashboard::PutNumber("ty", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty", 0.0));
}