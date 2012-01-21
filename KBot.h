// standard includes
#include "math.h"

// FRC includes
#include "WPILib.h"
#include "IterativeRobot.h"
#include "nivision.h"

class CANJaguar;
class RobotDrive;
class Joystick;
class AxisCamera;

// Parameters
#define DEADBAND 0.12

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
	// Members
	CANJaguar *m_leftJaguar;
	CANJaguar *m_rightJaguar;
	
	RobotDrive *m_robotDrive;
	
	Joystick *m_Stick;
	
	AxisCamera *camera;
	Image *img;
	
	// Private Methods
	void drive_routine(void);
};
