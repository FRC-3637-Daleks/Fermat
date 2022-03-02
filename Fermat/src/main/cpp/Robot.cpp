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
    
    //What is this used for (Someone tell me)
    m_leftFront           = new WPI_TalonFX(0);
  }
  catch (std::exception& e) {
    std::string err_string = "Error instantiating components:  ";
    err_string += e.what();
    DriverStation::ReportError(err_string.c_str());
  }
  
  m_compressor->Start();
  m_leftFront->SetSelectedSensorPosition(0);
  m_climb_solenoid->Set(false);
  m_intake_solenoid->Set(false);
  m_shooter_solenoid->Set(false);
}

void Robot::RobotPeriodic()
{
  m_limelight->Tick();
  SmartDashboard::PutNumber("Encoder", m_leftFront->GetSelectedSensorPosition());//6300
  SmartDashboard::PutNumber("Encoder Foot", m_leftFront->GetSelectedSensorPosition()/ENCODER_FEET);//6300
}

// I think I have some errors here, I wanna test this
// We want to be able to test in general
void Robot::AutonomousInit()
{
  phase = 0;
  m_limelight->LightOn();
}

void Robot::AutonomousPeriodic() 
{
  m_auton->Tick();
}

void Robot::TeleopInit()
{
  
}

void Robot::TeleopPeriodic()
{
  /*
    Start Button - Toggle auto intake 
    Back Button - Toggle auto shoot  
    A Buttton - Toggle intake pneumatics (Will do auto intake if on)
    B Button - Swerve turn (follow ball) 
    X Button - Rev motor
    Y - Auto Climb (Hold)
    L3 - Climb Pneumatics (Toggle)
    Left Stick - Climb Motor(Up and Down)
    Left Bumper - Activate Intake Motor (Will do auto intake if on)
    Right Bumper - Toggle Shooter Pneumatics
    Right Joystick XBOX - Shooter Speeds (4 speeds)
      Up - 0.25     T
      Left - 0.5
      Down - 0.75
      Right - 1
  */

  m_pi->Tick();
  m_intake->Tick();
  // m_climb->Tick();
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
