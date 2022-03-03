#include "Fermat.h"

Auton::Auton(DalekDrive *drive, RaspberryPi *pi, Intake *intake, Limelight *limelight, Shooter *shooter) {
	m_drive			= drive;
	m_pi            = pi; 
	m_intake		= intake;
    m_limelight     = limelight;
	m_shooter		= shooter;
	auton_phase		= 0;
}

// // Some Auton C+V
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
				m_drive->ResetEncoder();
				m_limelight -> LightOn();	
			}
			if (m_drive->DriveToFeet(7)){
				auton_phase++;
			}
		break;
		
		case 1: //Find more bawl(z)
            if (PI_GOOD == 1){
				if(m_pi->SwerveTurn()) {
            		m_intake -> AutoIntake(false);
					auton_phase++;
            	}
			} else {
				if (m_drive->DriveToFeet(10)){
					m_intake -> AutoIntake(false);
					auton_phase++;
				}
			}
		break;

    	case 2: //Align Launcher and Shoot Ball 
        	if (LIMELIGHT_GOOD==1){
				m_shooter -> SetHigh();
				if (m_shooter->GetSpeed()==m_limelight->CalcVelocity(2)){
        			m_shooter -> Shoot();
					m_intake -> AutoIntake(true);
					auton_phase++;
				}	
			} else{
				m_shooter -> SetSpeed(2.15);
				if (m_shooter-> GetSpeed()==m_limelight->CalcVelocity(2, 2.15)){
        			m_shooter -> Shoot();
					m_intake -> AutoIntake(true);
					auton_phase++;
				}
			}
		break;
    	
    	case 3: //Get ready to shoot the other collected bawlz 
			if (LIMELIGHT_GOOD==1){
				m_shooter -> SetHigh();
				if (m_shooter->GetSpeed()==m_limelight->CalcVelocity(2)){
        			m_shooter -> Shoot();
					auton_phase++;
				}	
			} else{
				m_shooter -> SetSpeed(4.0);
				if (m_shooter->GetSpeed()==m_limelight->CalcVelocity(2, 4.0)){
        			m_shooter -> Shoot();
					auton_phase++;
				}
			}
		break;
    }
}
