#include "Fermat.h"

Auton::Auton(DalekDrive *drive, RaspberryPi *pi, Intake *intake, Limelight *limelight, Shooter *shooter) {
	m_drive			= drive;
	m_pi            = pi; 
	m_intake		= intake;
    m_limelight     = limelight;
	m_shooter		= shooter;
	auton_phase		= 0;
}

// if (LIMELIGHT_GOOD==1){
	
// } else{

// }
// if (PI_GOOD == 1){

// } else {

// }

void
Auton::Tick() {
    switch(auton_phase) {
    	case 0: //Turn limelight on ;)
        	if (LIMELIGHT_GOOD==1){
				m_limelight -> LightOn();	
			}
          	auton_phase++;
   			break;
    	case 1: //Align Launcher and Shoot Ball 
        	if (LIMELIGHT_GOOD==1){
				m_shooter -> SetHigh();
				if (m_shooter->GetSpeed()==m_limelight->CalcVelocity(2)){
        			m_shooter -> Shoot();
					auton_phase++;
				}	
			} else{
				m_shooter -> SetSpeed(10.0);
				if (m_shooter->GetSpeed()==m_limelight->CalcVelocity(2, 10.0)){
        			m_shooter -> Shoot();
					auton_phase++;
				}
			}
    		break;
    	case 2: //Find more bawl(z)
            if (PI_GOOD == 1){
				if(m_pi->SwerveTurn()) {
            		auton_phase++;
            	}
			} else {
				if (m_drive->DriveToFeet(10)){
					auton_phase++;
				}
			}
    		break;
    	case 3: //Get ready to shoot the other collected bawlz 
			break;
			if (LIMELIGHT_GOOD==1){
				m_shooter -> SetHigh();
				if (m_shooter->GetSpeed()==m_limelight->CalcVelocity(2)){
        			m_shooter -> Shoot();
					auton_phase++;
				}	
			} else{
				m_shooter -> SetSpeed(10.0);
				if (m_shooter->GetSpeed()==m_limelight->CalcVelocity(2, 10.0)){
        			m_shooter -> Shoot();
					auton_phase++;
				}
			}
    		break;
    }
}
