// standard includes
#include "math.h"

// FRC includes
#include "WPILib.h"
#include "IterativeRobot.h"

#define USE_CAMERA 1
#ifdef USE_CAMERA
#include "nivision.h"
#include "DashboardDataSender.h"
#endif

class CANJaguar;
class RobotDrive;
class Joystick;
class AxisCamera;

// Parameters
const float DEADBAND = 0.12;

class KBot : public IterativeRobot {
	
public:
	KBot();
	~KBot();
	
	void RobotInit(void);
	void DisabledInit(void);
	void AutonomousInit(void);
	void TeleopInit(void);
	
	void DisabledPeriodic(void);
	void AutonomousPeriodic(void);
	void TeleopPeriodic(void);
	
	void DisabledContinuous(void){};
	void AutonomousContinuous(void){};
	void TeleopContinuous(void){};
	
private:
	
#ifdef USE_CAMERA
	// Image analysis
	void findBestTarget(Image* pImage);

	// Best target parameters (pixels)
	int m_nIBestTarget;
	int m_nJBestTarget;
	
	AxisCamera *camera;
	HSLImage image;
	DashboardDataSender* dds; 
#endif
	
	// Members
	CANJaguar *m_leftJaguar;
	CANJaguar *m_rightJaguar;
	
	RobotDrive *m_robotDrive;
	
	Joystick *m_Stick;

	// Private Methods
	void drive_routine(void);
	
};
