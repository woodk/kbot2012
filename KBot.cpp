#include "KBot.h"

#ifdef USE_CAMERA
#include "Vision/ColorImage.h"
#include "ImageProcessing/ImageProcessing.h"
#endif

KBot::KBot(void){
	m_leftJaguar = new CANJaguar(8, CANJaguar::kPercentVbus);
	m_leftJaguar->Set(0.0);

	m_rightJaguar = new CANJaguar(9, CANJaguar::kPercentVbus);
	m_rightJaguar->Set(0.0);
	
	m_robotDrive = new RobotDrive(m_leftJaguar, m_rightJaguar);
	
	m_Stick = new Joystick(2);
	
#ifdef USE_CAMERA
	camera = &AxisCamera::GetInstance("192.168.0.90");//"10.28.08.11");
	camera->WriteResolution(camera->kResolution_320x240);
	camera->WriteWhiteBalance(camera->kWhiteBalance_FixedIndoor);
	Wait(3.0);
	//dds = new DashboardDataSender();
#endif
	
}// end

KBot::~KBot(void){}

void KBot::RobotInit(void){}
void KBot::DisabledInit(void){}
void KBot::AutonomousInit(void){}
void KBot::TeleopInit(void){}

void KBot::DisabledPeriodic(void){
	GetWatchdog().Feed();
	
#ifdef USE_CAMERA
	int nError = camera->GetImage(image.GetImaqImage());
	if (1 == nError)
	{
		findBestTarget(image.GetImaqImage());
	}
	std::vector<Target> targets;
	//dds->sendVisionData(0.0, 0.0, 0.0, 0.0, targets);

#endif
	
}// end

void KBot::AutonomousPeriodic(void){
	GetWatchdog().Feed();
}// end

void KBot::TeleopPeriodic(void){
	GetWatchdog().Feed();
	
	drive_routine();
	
	// left bummper -> turn left slowly 
	if (m_Stick->GetRawButton (5) == 1 ){
		m_robotDrive->ArcadeDrive(0.0, 0.4);
	}// end if
	
	// right bummper -> turn right slowly
	if (m_Stick->GetRawButton (6) == 1 ){
		m_robotDrive->ArcadeDrive(0.0, -0.4);
	}// end if
	
#ifdef USE_CAMERA
	int nError = camera->GetImage(image.GetImaqImage());
	if (0 == nError)
	{
		std::cout << nError << std::endl;
	}
#endif
	
}// end

void KBot::drive_routine(void) {
	
	float left_y = m_Stick->GetRawAxis(2);
	float right_x = m_Stick->GetRawAxis(4);
	
	// check for left_y deadband
	if( (left_y < DEADBAND && left_y > 0) || (left_y < 0 && left_y > -DEADBAND) ) {
		left_y = 0;
	}// end if
	
	// check for right_x deadband
	if( (right_x < DEADBAND && right_x > 0) || (right_x < 0 && right_x > -DEADBAND) ) {
		right_x = 0;
	}// end if
	
	// square right_x input
	if (right_x > 0){
		right_x = right_x * right_x;
	}//end if
	if (right_x < 0){
		right_x = right_x * -right_x;
	}//end if
	right_x = -right_x;

	// if in low gear
	if (m_Stick->GetRawAxis (3) < -0.8){
		left_y = left_y * 6/10;
		right_x = right_x / 2;
	}// end if
	
	m_robotDrive->ArcadeDrive(left_y, right_x);
}// end

#ifdef USE_CAMERA
void KBot::findBestTarget(Image* pImage)
{
    int success = 1;
    int err = 0;

     // Vision Assistant Algorithm
     success = IVA_ProcessImage(pImage);
     if (!success)
          err = imaqGetLastError();

}
#endif

START_ROBOT_CLASS(KBot);
