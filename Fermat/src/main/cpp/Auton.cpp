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
Auton::REALLYBAD(){
	m_drive->TankDrive(0.6, 0.6, false, false);
	m_intake->AutoIntake(true);
	Wait(2.0);
	m_drive->StopLeft();
	m_drive->StopRight();
	while (!m_shooter->CheckSpeed(3.3)){
		m_shooter->SetSpeed(3.3);
	}
	m_shooter->Shoot();
	// while (!m_shooter->CheckSpeed(3.3)){
	// 	m_shooter->SetSpeed(3.3);
	// }
	// m_shooter->Shoot();
}

void 
Auton::REALLYBAD(){
	m_drive->ResetEncoder();
	m_drive->TankDrive(.7,.7,false, false);
	m_intake->AutoIntake(true);
	Wait(1.5);
	// m_drive->DriveToFeet(11);
	m_intake->AutoIntake(false);
	m_drive->TankDrive(0.0, 0.0, false, false);
	//m_drive->StopLeft();
	//m_drive->StopRight();
	while (!m_shooter->CheckSpeed(3.5)){
		m_shooter->SetSpeed(3.5);
	}
	m_shooter->Shoot();
	m_shooter->SetSpeed(0);
}

void
Auton::Tick() {
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
    	
	// 	//Arnav was here
	// 	//arnav is the goat
	// 	//Goat is for greatest of all time
	// 	//je suis d'accord - visvam
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
