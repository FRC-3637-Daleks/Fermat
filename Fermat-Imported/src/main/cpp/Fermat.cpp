#include "Fermat.h"

using namespace frc;


void Robot::RobotInit() 
{
  cs::AxisCamera camera = CameraServer::GetInstance()-> AddAxisCamera(CAMERA);  // Initialize Camera
  // Only use these two lines if there is problems with the camera
  camera.SetResolution(160, 90);   
  camera.SetFPS(15);

  m_xbox                = new frc::XboxController(XBOX);
  m_drive               = new DalekDrive(m_xbox);
  m_climb_solenoid      = new frc::Solenoid(PCM, PneumaticsModuleType::CTREPCM, CLIMB);
  m_intake_solenoid     = new frc::Solenoid(PCM, PneumaticsModuleType::CTREPCM, INTAKE);
  m_shooter_solenoid    = new frc::Solenoid(PCM, PneumaticsModuleType::CTREPCM, SHOOTER);
  m_compressor          = new frc::Compressor(PCM, PneumaticsModuleType::CTREPCM);
  m_limelight           = new Limelight(m_drive);
  m_pi                  = new RaspberryPi(m_drive, m_xbox);
  m_climb               = new Climb(m_climb_solenoid, m_xbox);
  m_intake              = new Intake(m_intake_solenoid, m_xbox);
  m_shooter             = new Shooter(m_drive ,m_xbox, m_shooter_solenoid, m_limelight);
  m_auton               = new Auton(m_drive, m_pi, m_intake, m_limelight, m_shooter);
  
  m_compressor->Start();
  m_climb_solenoid->Set(false);
  m_intake_solenoid->Set(false);
  m_shooter_solenoid->Set(false);
}

void Robot::RobotPeriodic()
{
  //m_limelight->Tick();
}

// I think I have some errors here, I wanna test this
// We want to be able to test in general
void Robot::AutonomousInit()
{
  m_auton->REALLYBAD();
}

void Robot::AutonomousPeriodic() 
{
  // m_auton->Tick();
}

void Robot::TeleopInit()
{
  
}

void Robot::TeleopPeriodic()
{
  /*

    INTAKE:
      A Buttton - Activate auto intake
      B Button - Activate intake
    
    SHOOTER:
      Right Bumper - Toggle Shooter Pneumatics (HOLD)
      X Button - Miss
      Left Stick XBOX - Shooter Speeds (4 speeds)
        Up - slowest (From start in auton)     
        Left - slower (From tarmac)
        Down - faster (Somewhere in the middle 4m)
        Right - Fastest (From Safe Zome)

    CLIMB:
      Left Bumper - Climb Pneumatics (Toggle)
      Right Stick - Climb Motor(Up and Down)
  */

  //m_pi->Tick();
  m_intake->Tick();
  m_climb->Tick();
  m_drive->Tick(); 
  m_limelight->Tick();
  m_shooter->Tick();
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