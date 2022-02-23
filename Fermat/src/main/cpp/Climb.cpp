#include "Fermat.h"

Climb::Climb(frc::Solenoid *climb_solenoid){
    m_climb_solenoid = climb_solenoid;
    m_climb_motor = new WPI_TalonFX(CLIMB_MOTOR);
    m_upperLimit = new DigitalInput(UPPERLIMIT);
    m_lowerLimit = new DigitalInput(LOWERLIMIT);

}

bool MainArm(){
    if(m_upperLimit->Get() || m_lowerLimit->Get()){
        return true;
    }
    return false;
}