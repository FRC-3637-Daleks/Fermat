#include "Euler.h"

Limelight::Limelight(DalekDrive *drive) {
    m_drive = drive;
}

void Limelight::Update() {
	SmartDashboard::PutNumber("ta", nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta", 0.0));
	
	//Set ta to a variable
	Area = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("ta", 0.0);

	// set a variable distance using an equation
	Distance = CalcDistance(Area);

	SmartDashboard::PutString("Distance", "The distance is " + std::to_string(Distance));
}


//Calculates Distance using the 'ta' variable from the limlight
//double area: ta variable from limelight
double Limelight::CalcDistance(double area)
{
  return 33.2*pow(area, -0.468);
}

void Limelight::LightOff() {
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1);
}

void Limelight::LightOn() {
	nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 3);
}
