#include "Fermat.h"

Auton::Auton(DalekDrive *drive, RaspberryPi *pi, Intake *intake, Limelight *limelight, Shooter *shooter) {
	m_drive			= drive;
	m_pi            = pi; 
	m_intake		= intake;
    m_limelight     = limelight;
	m_shooter		= shooter;
	// auton_phase		= 0;
	
	frc::SmartDashboard::PutNumber("Auton",AUTON_VERSION);
}

void 
Auton::REALLYBAD(){

	// The way we do auton when we have no time to do anything (aka this season).
	m_drive->TankDrive(-.3,-.3,false, false);
	if (AUTON_VERSION == 0){
		m_intake->AutoIntake(true);
		Wait(2.0_s); //1.5_s
		m_drive->TankDrive(0.0, 0.0, false, false);	
		Wait(4.0_s);
		m_intake->AutoIntake(false);
	} else if (AUTON_VERSION == 1){
		m_drive->ResetEncoder();
		m_intake->AutoIntake(true);
		//total distance = 5.9525 feet
		while(!m_drive->DriveToFeet(68/12)){};
		m_drive->TankDrive(0.0, 0.0, false, false);
	}

	if (LIMELIGHT_GOOD==1){
		m_shooter->SetMotorSpeed();
	} else {
		if (AUTON_VERSION==0){
			m_shooter->SetMotorSpeed(4.6164);
		} else if (AUTON_VERSION==1){
			m_shooter->SetMotorSpeed(3.3766);
		}
		
	}

	Wait(5.0_s);
	m_intake->AutoIntake(false);
	m_shooter->Shoot();
	Wait(4.0_s);
	m_shooter->Shoot();
	Wait(1.0_s);
	m_shooter->SetMotorSpeed(0.0);
	// m_pi->SwerveTurn();
}