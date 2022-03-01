// #include "Fermat.h"

// Auton::Auton(DalekDrive *drive, RaspberryPi *pi, Intake *intake, Limelight *limelight, Shooter *shooter)
// {
// 	m_drive			= drive;
// 	m_pi            = pi; 
// 	m_intake		= intake;
//     m_limelight     = limelight;
// 	m_shooter		= shooter;

// 	auton_phase		= 0;
// 	pickupBallStart = frc::SmartDashboard::GetData("Pickup Ball Start");
// 	pickupBallEnd   = frc::SmartDashboard::GetData("Pickup Ball End");

// 	p_temp = 0; i_temp = 0; d_temp = 0;
// }

// void Auton::AutonCase(int begin, int end)
// {
// 	switch (begin) {
// 		case 1: //right sensor
// 		enter_target_x = -2; //need sensor
// 		break;
// 		case 2: //straight on
// 		enter_target_x = 0;
// 		break;
// 		case 3: //left sensor
// 		enter_target_x = 5; //need sensor
// 		break;
// 	}

// 	// enter_target_y = LINE_TO_WALL;
	
// 	switch (end) {
// 		case 1: //Our trench
// 			exit_target_x = 0 /*Our Trench x*/;
// 			exit_target_y =  0/*Our Trench y*/;
// 			break;
// 		case 2: //Shield Generator
// 			exit_target_x = 0 /*Shield Generator x*/;
// 			exit_target_y =0 /*Shield Generator*/;
// 			break;
// 		case 3: //Enemy trench
// 			exit_target_x = 0/*Enemy Trench x*/;
// 			exit_target_y = 0/*Enemy Trench y*/;
// 			break;
// 	}

// 	enter_target_ang = atan2(enter_target_y, enter_target_x);
// 	exit_target_ang  = atan2(exit_target_y, exit_target_x);
// 	enter_target_dist = sqrt(enter_target_x * enter_target_x + enter_target_y * enter_target_y);
// 	exit_target_dist = sqrt(exit_target_x * exit_target_x + exit_target_y * exit_target_y);
// 	//here set up what happens at the end (after delivery)
// }

// // void Auton::AutonPerform(double period) {
// //     switch(auton_phase) {
// //       case 0: //Turn limelight on ;)
// //           if(nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode", 1) != 3) {
// //             m_limelight -> LightOn();
// //           }
// //           auton_phase++;
// //     break;
// //       case 1: //Align Launcher and Shoot Ball 
// //            m_shooter -> ShootHigh(); //Wow the programmers are so smart and ingenuitive and hot ;) 🤤
// //            auton_phase++;
// //     break;
// //       case 2: //Find more bawl(z)
// //             if(m_pi->SwerveTurn(SmartDashboard::GetNumber("Degrees", 0), SmartDashboard::GetNumber("Distance", 0)) = true) {
// //             	auton_phase++;
// //             }
// //     break;
// //       case 3: //Get ready to shoot the other collected bawlz 
// //     }
// // }