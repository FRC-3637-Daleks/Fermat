#include "Fermat.h"

Auton::Auton(DalekDrive *drive, RaspberryPi *pi, Intake *intake, Limelight *limelight, Shooter *shooter) {
	m_drive			= drive;
	m_pi            = pi; 
	m_intake		= intake;
    m_limelight     = limelight;
	m_shooter		= shooter;

	auton_phase		= 0;
	pickupBallStart = frc::SmartDashboard::GetData("Pickup Ball Start");
	pickupBallEnd   = frc::SmartDashboard::GetData("Pickup Ball End");

	p_temp = 0; i_temp = 0; d_temp = 0;
}

void
Auton::Tick() {
    switch(auton_phase) {
    	case 0: //Turn limelight on ;)
        	//	if(nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1) != 3) {
        	//		m_limelight -> LightOn();
          	//	}
			m_limelight -> LightOn();
          	auton_phase++;
   			break;
    	case 1: //Align Launcher and Shoot Ball 
        	m_shooter -> SetHigh();
			if (m_drive->GetCanDrive()){ //Wow the programmers are so smart and ingenuitive and hot ;) 🤤
        		m_shooter -> Shoot();
			}
			auton_phase++;
    		break;
    	case 2: //Find more bawl(z)
            if(m_pi->SwerveTurn()) {
            	auton_phase++;
            }
    		break;
    	case 3: //Get ready to shoot the other collected bawlz 
			break;
    }
}
