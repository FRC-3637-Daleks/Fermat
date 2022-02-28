#include "Fermat.h"

using namespace frc;


void Robot::RobotInit() 
{
  //cs::AxisCamera camera = CameraServer::GetInstance()->AddAxisCamera(FORWARD_CAMERA);  // Initialize Camera
  // camera.SetResolution(160, 90);    // Only use these two lines if needed
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
    
    //What is this used for (Someone tell me)
    m_leftFront           = new WPI_TalonFX(0);
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
  frc::SmartDashboard::PutBoolean("start button pressed", false);
  
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
void Robot::AutonomousInit()
{
  phase = 0;
  m_limelight->LightOn();
}

void Robot::AutonomousPeriodic() 
{
  if(phase == 0) {
    m_leftFront->SetSelectedSensorPosition(0);
    phase++;
  }
  if(phase == 1) {
    if(true){
      //m_drive->DriveToFeet(m_limelight->CalcDistance(m_limelight->area))
      phase++;
    }
  }
  if (phase == 2) {
    if (m_drive->Turn(90.0)) {
      phase++;
    }
  } if (phase == 3) {
    m_drive->StopLeft();
    m_drive->StopRight();
  }
  SmartDashboard::PutNumber("phase", phase);
}

void Robot::TeleopInit()
{
  
}

void Robot::TeleopPeriodic()
{
  /*
  
    The buttons doc
    https://docs.google.com/document/d/14A8HDa7gtJTFGJS2YYfce4O7fD7D9ZBCQrjSBS9ddE8/edit
    
    Tick funtions can now switch from manual to automatic
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
