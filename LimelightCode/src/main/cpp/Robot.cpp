#include "Fermat.h"

using namespace frc;

void Robot::RobotInit() 
{
  cs::AxisCamera camera = CameraServer::GetInstance()->AddAxisCamera(FORWARD_CAMERA);  // Initialize Camera
  // camera.SetResolution(160, 90);    // Only use these two lines if needed
  // camera.SetFPS(15);
  try {
    m_xbox        = new frc::XboxController(XBOX);
    m_leftStick   = new frc::Joystick(LEFT_JOY);
    m_rightStick  = new frc::Joystick(RIGHT_JOY);
    m_climb_solenoid = new frc::DoubleSolenoid(PCM, CLIMB_DEPLOY, CLIMB_EXHAUST);
    m_ahrs        = new AHRS(SPI::Port::kMXP);
    m_compressor  = new frc::Compressor(PCM);
    m_limelight   = new Limelight(m_drive);
  }
  catch (std::exception& e) {
    std::string err_string = "Error instantiating components:  ";
    err_string += e.what();
    DriverStation::ReportError(err_string.c_str());
  }
  frc::SmartDashboard::PutNumber("Start Auton", 2);
  frc::SmartDashboard::PutNumber("End Auton", 2);
  frc::SmartDashboard::PutNumber("Delay", 0);
  frc::SmartDashboard::PutNumber("Delay Phase", 0);
  frc::SmartDashboard::PutNumber("Auton Phase", 0);
  frc::SmartDashboard::PutBoolean("Pickup Ball End", false);
  frc::SmartDashboard::PutBoolean("Pickup Ball Start", false);
  //frc::SmartDashboard::PutNumber("Starting # of Balls", 3);

  m_ahrs->ZeroYaw();
  m_ahrs->Reset();
  m_ahrs->ResetDisplacement();
  m_compressor->Start();
}

void Robot::RobotPeriodic()
{
    m_limelight->Update();
}

// I think I have some errors here, I wanna test this
void Robot::AutonomousInit()
{
  auton_start = 2;//(int)frc::SmartDashboard::GetData("Start Auton");
  auton_end =   1;//(int)frc::SmartDashboard::GetData("End Auton");
  waitSeconds = 0;//(int)frc::SmartDashboard::GetData("Delay");
}

void Robot::AutonomousPeriodic() 
{
	
}

void Robot::TeleopInit()
{
  
}

void Robot::TeleopPeriodic()
{
    if (m_drive) {
	  if (m_rightStick->GetTrigger() || m_leftStick->GetTrigger()) { // JUST FOR TESTING
      } else {
        m_drive->TankDrive(m_leftStick, m_rightStick, true);
        frc::SmartDashboard::PutBoolean("start button pressed", false);
      }
    }


}

void Robot::TestInit()
{

}

void Robot::TestPeriodic()
{

}

void Robot::DisabledInit()
{
  
}


#ifndef RUNNING_FRC_TESTS
int main() { return StartRobot<Robot>(); }
#endif