#include "Fermat.h"

Limelight::Limelight(DalekDrive *drive) {
    m_drive = drive;
}

// double Limelight::CalcDistance() // (m)
// {
//   return (DIST_COEFFICIENT*pow(area, DIST_EXPONENT))*0.0254;
// }
double Limelight::CalcDistance(){
	if (mode == 0){
		return (DIST_COEF_C*pow(area, DIST_EXPO_C))*0.0254;
	} else if (mode == 1) {
		return (DIST_COEF_M*pow(area, DIST_EXPO_M))*0.0254;
	} else {
		return (DIST_COEF_F*pow(area, DIST_EXPO_F))*0.0254;
	}
}

void Limelight::SetMode(int newMode){
	mode = newMode;
}

double Limelight::CalcVelocity(double points, double xDistance) // (m/s)
{
	double height = (points==1)?LOW_SHOOT:HIGH_SHOOT - START_HEIGHT;
	return sqrt( (-4.9*pow(xDistance, 2)) / ( pow(cos(SHOOT_ANGLE), 2) * (height - (xDistance * (tan(SHOOT_ANGLE)))) ) );
}

double Limelight::CalcVelocity(double points) // (m/s)
{
	return CalcVelocity(points, CalcDistance());
}

double Limelight::CalcTurnAngle(double xPos){
	SmartDashboard::PutNumber("TurnAngle", ANGLE_PRODUCT * xPos + ANGLE_OFFSET);
	return ANGLE_PRODUCT * xPos + ANGLE_OFFSET;
}

double Limelight::GetAngle(){
	return angle;
}

double Limelight::GetDistance(){
	return distance;
}

void Limelight::LightOff() {
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
}

void Limelight::LightOn() {
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
}

void Limelight::Tick() { 
	
	LightOn();	
	
	//Set Limelight area (ta) to a variable
	area = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta", 0.0);

	// set a variable distance using a linear regression of ax+b using tvert on desmos
	distance = (area>AREA_MIN&&area<AREA_MAX)?CalcDistance():distance;

	//angle?
	angle = acos (nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0)/distance)*180/PI; 

	//display the hypothetical velocity for the wheel
	// low_velocity = CalcVelocity(1);
	high_velocity = CalcVelocity(2);

	//Put the X-Distance the robot is from the target on the dashboard 
	SmartDashboard::PutNumber("Horizontal Distance from the Target", distance);
	SmartDashboard::PutNumber("Horizontal Distance from the Target", angle);

	// // Display all the Limelight Varibles on the Smart Dashboard
	// SmartDashboard::PutNumber("ta", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta", 0.0));
	// SmartDashboard::PutNumber("tx", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx", 0.0));
	// SmartDashboard::PutNumber("ty", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ty", 0.0));
}