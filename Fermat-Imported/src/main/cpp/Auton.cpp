#include "Fermat.h"

Auton::Auton(DalekDrive *drive, RaspberryPi *pi, Intake *intake, Limelight *limelight, Shooter *shooter) {
	m_drive			= drive;
	m_pi            = pi; 
	m_intake		= intake;
    m_limelight     = limelight;
	m_shooter		= shooter;
	// auton_phase		= 0;
}

void 
Auton::REALLYBAD(){

	// The way we do auton when we have no time to do anything (aka this season).

	m_drive->TankDrive(-.3,-.3,false, false);
	m_intake->AutoIntake(true);
	Wait(1.5_s);
	m_drive->TankDrive(0.0, 0.0, false, false);
	m_shooter->SetSpeed(4.5);
	Wait(5.0_s);
	m_shooter->Shoot();
	// m_pi->SwerveTurn();
}

void
Auton::Tick() {

	// below is the way we usually do auton
	// This is the reason why we have some methods as booleans so it is easy to use during auton

    // switch(auton_phase) {
    // 	case 0: //Turn limelight on ;)
    //     	if (LIMELIGHT_GOOD==1){
	// 			m_limelight -> LightOn();	
	// 		}
	// 		if (m_drive->DriveToFeet(7)){
	// 			auton_phase++;
	// 		}
	// 	break;
		
	// 	case 1: //Find more bawl(z)
    //         if (PI_GOOD == 1){
	// 			if(m_pi->SwerveTurn()) {
    //         		m_intake -> AutoIntake(false);
	// 				auton_phase++;
    //         	}
	// 		} else {
	// 			if (m_drive->DriveToFeet(10)){
	// 				m_intake -> AutoIntake(false);
	// 				auton_phase++;
	// 			}
	// 		}
	// 	break;

    // 	case 2: //Align Launcher and Shoot Ball 
    //     	if (LIMELIGHT_GOOD==1){
	// 			m_shooter -> SetHigh();
	// 			if (m_shooter->CheckSpeed(m_limelight->GetDistance())){
    //     			m_shooter -> Shoot();
	// 				m_intake -> AutoIntake(true);
	// 				auton_phase++;
	// 			}	
	// 		} else{
	// 			m_shooter -> SetSpeed(3.3);
	// 			if (m_shooter->CheckSpeed(3.3)){
    //     			m_shooter -> Shoot();
	// 				m_intake -> AutoIntake(true);
	// 				auton_phase++;
	// 			}
	// 		}
	// 	break;
    	
	// 	// Arnav was here
	// 	// arnav is the goat
	// 	// Goat is for greatest of all time
	// 	// je suis d'accord - visvam
	//  // ça fraçais est mauvias - qui sait
    // 	case 3: //Get ready to shoot the other collected bawlz 
	// 		if (LIMELIGHT_GOOD==1){
	// 			m_shooter -> SetHigh();
	// 			if (m_shooter->GetSpeed()==m_limelight->CalcVelocity(2)){
    //     			m_shooter -> Shoot();
	// 				auton_phase++;
	// 			}	
	// 		} else{
	// 			m_shooter -> SetSpeed(4.0);
	// 			if (m_shooter->GetSpeed()==m_limelight->CalcVelocity(2, 4.0)){
    //     			m_shooter -> Shoot();
	// 				auton_phase++;
	// 			}
	// 		}
	// 	break;
    // }
}
