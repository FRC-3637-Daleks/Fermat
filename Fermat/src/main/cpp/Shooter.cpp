#include "Fermat.h"

Shooter::Shooter(frc::XboxController *xbox, frc::Solenoid *climb_solenoid)
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