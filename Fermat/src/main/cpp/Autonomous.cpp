#include "Fermat.h"

Auton::Auton(DalekDrive *drive, RaspberryPi *pi, BallIntake *ballIntake, Limelight *limelight)
{
	m_drive			= drive;
	m_pi            = pi; 
	m_ballIntake    = ballIntake;
    m_limelight     = limelight;

	auton_phase = 0;
	pickupBallStart = frc::SmartDashboard::GetData("Pickup Ball Start");
	pickupBallEnd   = frc::SmartDashboard::GetData("Pickup Ball End");

	p_temp = 0; i_temp = 0; d_temp = 0;
}

void Auton::AutonCase(int begin, int end)
{
	switch (begin) {
		case 1: //right sensor
		enter_target_x = -2; //need sensor
		break;
		case 2: //straight on
		enter_target_x = 0;
		break;
		case 3: //left sensor
		enter_target_x = 5; //need sensor
		break;
	}

	enter_target_y = lineToWall;
	
	switch (end) {
		case 1: //Our trench
			exit_target_x = /*Our Trench x*/;
			exit_target_y = /*Our Trench y*/;
			break;
		case 2: //Shield Generator
			exit_target_x = /*Shield Generator x*/;
			exit_target_y = /*Shield Generator*/;
			break;
		case 3: //Enemy trench
			exit_target_x = /*Enemy Trench x*/;
			exit_target_y = /*Enemy Trench y*/;
			break;
	}

	enter_target_ang = atan2(enter_target_y, enter_target_x);
	exit_target_ang  = atan2(exit_target_y, exit_target_x);
	enter_target_dist = sqrt(enter_target_x * enter_target_x + enter_target_y * enter_target_y);
	exit_target_dist = sqrt(exit_target_x * exit_target_x + exit_target_y * exit_target_y);
	//here set up what happens at the end (after delivery)
}

void Auton::AutonPerform(double period) {
    switch(auton_phase) {
      case 0: //Turn limelight on ;)
          if("ledMode" != 3) {
            LightOn();
          }
          auton_phase++;
    break;
      case 1: //Align Launcher and Shoot Ball 
           ShootHigh(); //Wow the programmers are so smart and ingenuitive and hot ;) 🤤
           auton_phase++;
    break;
      case 2: //Find more bawl(z)
            if(SwerveTurn(SmartDashboard::GetNumber("Degrees", 0), SmartDashboard::GetNumber("Distance", 0)) = true;) {
            auton_phase++;
            }
    break;
      case 3: //Get ready to shoot the other collected bawlz 
            if()
    }
}