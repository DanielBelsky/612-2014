#include "main.h"
#include "612.h"
#include <DigitalInput.h>
#include <Relay.h>
#include <Joystick.h>
#include "ports.h"

main_robot* robot=NULL;

main_robot::main_robot()
{
    printf("hello\n");
    printf("world\n");
    robot=this;
}

main_robot::~main_robot()
{
}

void main_robot::RobotInit()
{
    printf("robot init\n");
    driverJoy = new Joystick(1);
    gunnerJoy = new Joystick(2);
    //pnum = new Pneumatics(1,8,1,8); // TODO Placeholder for the ports
    //shift = new Shifter(1,7,8);
    //shift->setHigh();
    drive = new DriveTrain(TALON_FL_MODULE, TALON_FL_CHANNEL,
                           TALON_RL_MODULE, TALON_RL_CHANNEL,
                           TALON_FR_MODULE, TALON_FR_CHANNEL,
                           TALON_RR_MODULE, TALON_RR_CHANNEL);
}
void main_robot::TeleopInit()
{

}
void main_robot::AutonomousInit()
{

}
void main_robot::TestInit()
{

}
void main_robot::DisabledInit()
{

}
void main_robot::TeleopPeriodic()
{
    float left = driverJoy->GetRawAxis(2);
    float right = driverJoy->GetRawAxis(5);
    drive->TankDrive(left, right);
}

void main_robot::AutonomousPeriodic()
{
}

void main_robot::DisabledPeriodic()
{

}
void main_robot::TestPeriodic()
{
    static int output=0;
    if(output%20==0)
    {
        printf("test periodic\n");
    }
    output++;
    pnum->checkPressure();
    pnum->updateSolenoid();
    if(gunnerJoy->GetRawButton(5))
    {
        if(shift->gear!=Shifter::low)
        {
            shift->setLow();
        }
    }
    else if(gunnerJoy->GetRawButton(6))
    {
        if(shift->gear!=Shifter::high)
        {
            shift->setHigh();
        }
    }
}

START_ROBOT_CLASS(main_robot)
