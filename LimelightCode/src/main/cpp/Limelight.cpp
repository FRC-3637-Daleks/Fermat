#include "Euler.h"

Limelight::Limelight(DalekDrive *drive) {
    m_drive = drive;
}

void Limelight::Update() { 
	SmartDashboard::PutNumber("ta", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta", 0.0));
	
	//Set ta to a variable
	Area = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta", 0.0);

	// set a variable distance using a linear regression of ax+b using tvert on desmos
	Distance = CalcDistance(Area);

	SmartDashboard::PutString("Distance", "The distance is " + std::to_string(Distance));
}

double Limelight::CalcDistance(double area)
{
  return 33.2*pow(area, -0.468);
}

double Limelight::CalcVelocity(int shoot, double xDistance)
{
	int yDistance=0;
	if (shoot==2){
		yDistance = HIGH_SHOOT-STARTING_HEIGHT;
	}else{
		yDistance = LOW_SHOOT-STARTING_HEIGHT;
	}
	return sqrt((4.9*pow(xDistance, 2))/(pow(cos(SHOOT_ANGLE), 2)*(yDistance - (xDistance * (tan(SHOOT_ANGLE))))));
}

void Limelight::LightOff() {
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
}

void Limelight::LightOn() {
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
}
