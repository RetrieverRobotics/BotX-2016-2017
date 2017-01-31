#pragma config(Motor,  port1,           ErightLiftMotor, tmotorVex393HighSpeed_HBridge, openLoop, driveLeft)
#pragma config(Motor,  port2,           backRight,     tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port3,           backLeft,      tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port4,           frontRight,    tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port5,           frontLeft,     tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port6,           leftLiftMotor, tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port7,           rightLiftMotor, tmotorVex393HighSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port8,           leftClaw,      tmotorNone, openLoop)
#pragma config(Motor,  port9,           rightClaw,     tmotorNone, openLoop)
#pragma config(Motor,  port10,          EleftLiftMotor, tmotorVex393HighSpeed_HBridge, openLoop, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

//#define AUTONOMOUS_TESTING

/**
* Limits the raw input value to be in the range:
* if < -max then -max
* if >= -max and < -min then rawInput
* if >= -min and <= min then 0
* if > min and <= max then rawInput
* if > max then max
*
* @param rawInput the value you want to pass to the motor
* @param max the absolute maximum value you want to pass to the motor (both positive and negative)
* @param min the absolute minimum value you want to output before setting to zero (both positive and negative)
* @return the value that should be passed to the motor
*/
int limitValue(int rawInput, int max, int min)
{
	if (abs(rawInput) > max)
	{
		rawInput = max * (rawInput > 0 ? 1 : -1);
	}

	if (abs(rawInput) <= min)
	{
		rawInput = 0;
	}

	return rawInput;
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/



void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	//bIfiAutonomousMode = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

void autonomousMode()
{

	motor[frontLeft] = 127;
	motor[frontRight] = 127;
	motor[backLeft] = 127;
	motor[backRight] = 127;

	wait1Msec(2000);

	motor[frontLeft] = 0;
	motor[frontRight] = 0;
	motor[backLeft] = 0;
	motor[backRight] = 0;


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
task autonomous()
{
#ifndef AUTONOMOUS_TESTING
		autonomousMode();
#else
		AutonomousCodePlaceholderForTesting();
#endif
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	// User control code here, inside the loop

#ifdef AUTONOMOUS_TESTING
	autonomousMode();
#else

	int forward;
	int strafe;
	int rotation;

	int deadzoneOuter = 127;
	int deadzoneInner = 30;

	while (true)
	{

		if(vexRT[Btn5U] == 1){
			motor[leftLiftMotor] = 127;
			motor[EleftLiftMotor] = -127;
			motor[rightLiftMotor]= -127;
			motor[ErightLiftMotor] = -127;

			motor[rightClaw] = -35;
			motor[leftClaw] = 35;
		}
		else if(vexRT[Btn5D] == 1){
			motor[leftLiftMotor] = -40;
			motor[EleftLiftMotor] = 40;
			motor[rightLiftMotor]= 40;
			motor[ErightLiftMotor] = 40;

			//motor[rightClaw] = 1;
			//motor[leftClaw] = -1;
		}
		else{
			motor[leftLiftMotor] = 0;
			motor[rightLiftMotor]= 0;
			motor[EleftLiftMotor] = 0;
			motor[ErightLiftMotor] = 0;
		}


		if(vexRT[Btn6U] == 1){
			motor[rightClaw] = 60;
			motor[leftClaw] = -60;
		}
		else if(vexRT[Btn6D] == 1){
			motor[rightClaw] = -30;
			motor[leftClaw] = 30;
		}
		else{
			motor[rightClaw] = 0;
			motor[leftClaw] = 0;
		}


		forward = vexRT[Ch3];
		strafe = vexRT[Ch4];
		rotation = vexRT[Ch1];

		motor[frontLeft] = limitValue( forward + strafe + rotation, deadzoneOuter, deadzoneInner );
		motor[frontRight] = limitValue( forward - strafe - rotation, deadzoneOuter, deadzoneInner );
		motor[backLeft] = limitValue( forward - strafe + rotation, deadzoneOuter, deadzoneInner );
		motor[backRight] = limitValue( forward + strafe - rotation, deadzoneOuter, deadzoneInner );
	}
#endif

}
