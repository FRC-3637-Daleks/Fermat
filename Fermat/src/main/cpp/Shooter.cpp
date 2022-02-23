#include "Fermat.h"
#include "Euler"

Shooter(frc::XboxController *xbox, frc::Solenoid *climb_solenoid)
{
    init(xbox, climb_solenoid);
}

void
Shooter::init(frc::XboxController *xbox, frc::Solenoid *climb_solenoid)
{
    const int kTimeoutMs = 30;
    const bool kSensorPhase = false;
    const bool kInvert = false;

    m_xbox = xbox;
    m_shooterSolenoid = climb_solenoid;
	m_shooter = new WPI_TalonSRX(SPINNER);
    if(m_shooter == NULL)
        std::bad_alloc();
    m_shooter->ConfigFactoryDefault();
	m_shooter->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, kTimeoutMs);
	m_shooter->SetSensorPhase(kSensorPhase);
	m_shooter->SetInverted(kInvert);
    m_shooter->SetSelectedSensorPosition(0, 0, kTimeoutMs);
   	m_shooterSolenoid = new frc::Solenoid(PCM, SPINNER_DEPLOY, SPINNER_EXHAUST);
    if(m_shooterSolenoid == NULL)
        std::bad_alloc();
    m_shooterSolenoid->Set(frc::Solenoid::kReverse);
}


Spinner::~Spinner()
{
    free(m_shooter);
    free(m_shooterSolenoid);
}

void Spinner::Reinit()
{
    const int kTimeoutMs = 30;
    m_shooter->SetSelectedSensorPosition(0, 0, kTimeoutMs);
    m_shooterSolenoid->Set(frc::Solenoid::kReverse);
}

void
Spinner::Tick()
{
    float encoderCnt = m_shooter->GetSensorCollection().GetQuadraturePosition();

    frc::SmartDashboard::PutNumber("SpinnerEncoder", encoderCnt);
    frc::SmartDashboard::PutNumber("Approx Color Wheel rotations", encoderCnt/NUM_TICKS_PER_COLOR_WHEEL_REV);

    if (m_xbox->GetYButtonPressed()) {
        if (m_shooterSolenoid->Get() == frc::Solenoid::kForward){
            m_shooterSolenoid->Set(frc::Solenoid::kOff);
            m_shooterSolenoid->Set(frc::Solenoid::kReverse);
        } else {
            m_shooterSolenoid->Set(frc::Solenoid::kReverse);
            m_shooterSolenoid->Set(frc::Solenoid::kForward);
        }
     }

    if (m_shooterSolenoid->Get() == frc::Solenoid::kForward) {
        if (m_xbox->GetXButton()) {
            m_shooter->Set(1);
        } else {
            m_shooter->Set(0.0);
        }
    } else {
        m_shooter->Set(0.0);
    }
}