#include "Fermat.h"

using namespace frc;


void Robot::RobotInit() 
{
  cs::AxisCamera camera = CameraServer::GetInstance()->AddAxisCamera(CAMERA);  // Initialize Camera
  // // Only use these two lines if there is problems with the camera
  // camera.SetResolution(160, 90);   
  // camera.SetFPS(15);

  try {
    m_xbox                = new frc::XboxController(XBOX);
    m_drive               = new DalekDrive(m_xbox);
    m_climb_solenoid      = new frc::Solenoid(PCM, CLIMB);
    m_intake_solenoid     = new frc::Solenoid(PCM, INTAKE);
    m_shooter_solenoid    = new frc::Solenoid(PCM, SHOOTER);
    m_compressor          = new frc::Compressor(PCM);
    m_limelight           = new Limelight(m_drive);
    m_pi                  = new RaspberryPi(m_drive, m_xbox);
    m_climb               = new Climb(m_climb_solenoid, m_xbox);
    m_intake              = new Intake(m_intake_solenoid, m_xbox);
    m_shooter             = new Shooter(m_drive ,m_xbox, m_shooter_solenoid, m_limelight);
    m_auton               = new Auton(m_drive, m_pi, m_intake, m_limelight, m_shooter);
  }
  catch (std::exception& e) {
    std::string err_string = "Error instantiating components:  ";
    err_string += e.what();
    DriverStation::ReportError(err_string.c_str());
  }
  
  m_compressor->Start();
  m_climb_solenoid->Set(false);
  m_intake_solenoid->Set(false);
  m_shooter_solenoid->Set(false);
}

void Robot::RobotPeriodic()
{
  m_limelight->Tick();
}

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
      A Buttton - Activate intake             (HOLD)
      Y Buttton - Spit out the ball           (HOLD)
      B Button - Swerve turn (follow ball)    (HOLD)
    
    SHOOTER:
      Right Bumper - Shoot                    (PRESS)
      X Button - Miss                         (HOLD)
      left Stick - Shooter Speeds (4 speeds)  (HOLD)
        Up - slowest (From start in auton)     
        Left - slower (From tarmac)
        Down - faster (Somewhere in the middle 4m)
        Right - Fastest (From Safe Zome)

    CLIMB:
      Left Bumper - Climb Pneumatics          (PRESS)
      Right Stick - Climb Motor (Up and Down) (HOLD)
  */

  m_pi->Tick();
  m_intake->Tick();
  m_climb->Tick();
  m_drive->Tick(); 
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
