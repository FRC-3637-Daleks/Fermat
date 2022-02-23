#include "Fermat.h"

Shooter::Shooter(frc::XboxController *xbox, frc::Solenoid *shooter_solenoid)
{
    m_shooter_solenoid = shooter_solenoid;
    m_xbox = xbox;
    m_shooter_moter = new WPI_TalonSRX(SHOOTER_MOTOR);
}