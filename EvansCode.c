#pragma config(Motor,  port8,           leftClaw,      tmotorNone, openLoop)
#pragma config(Motor,  port2,           backRight,     tmotorVex393HighSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port3,           backLeft,      tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port4,           frontRight,    tmotorVex393HighSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port5,           frontLeft,     tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port6,           leftLiftMotor, tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port7,           rightLiftMotor, tmotorVex393HighSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port1,           ErightLiftMotor, tmotorVex393HighSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port10,           EleftLiftMotor, tmotorVex393HighSpeed_MC29, openLoop, driveRight)
#pragma config(Motor,  port9,          rightClaw,     tmotorNone, openLoop)
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

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
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
	// ..........................................................................
	// Insert user code here.
	// ..........................................................................

	// Remove this function call once you have "real" code.
	AutonomousCodePlaceholderForTesting();
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

	int forward;
	int strafe;
	bool isRotationPressed;
	bool clockwise;

	int deadzoneOuter = 127;
	int deadzoneInner = 30;

	while (true)
	{

		if(vexRT[Btn5U] == 1){
			motor[leftLiftMotor] = 127;
			motor[EleftLiftMotor] = -127;
			motor[rightLiftMotor]= -127;
			motor[ErightLiftMotor] = -127;

			motor[rightClaw] = -1;
			motor[leftClaw] = 1;
		}
		else if(vexRT[Btn5D] == 1){
			motor[leftLiftMotor] = -127;
			motor[EleftLiftMotor] = -127;
			motor[rightLiftMotor]= 127;
			motor[ErightLiftMotor] = 127;

			motor[rightClaw] = 1;
			motor[leftClaw] = -1;
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
			motor[rightClaw] = -40;
			motor[leftClaw] = 40;
			motor[rightClaw] = 0;
			motor[leftClaw] = 0;
		}


		forward = vexRT[Ch4];
		strafe = vexRT[Ch3];
		isRotationPressed = ( vexRT[Ch1] > 0 || vexRT[Ch1] < 0 );
		clockwise = vexRT[Ch1] > 0;

		if (isRotationPressed)
		{
			motor[frontLeft] = limitValue( (96 - (strafe / 4)) * (clockwise ? 1 : -1),
			deadzoneOuter, deadzoneInner);
			motor[backLeft] = limitValue( (96 + (strafe / 4)) * (clockwise ? 1 : -1),
			deadzoneOuter, deadzoneInner);
			motor[frontRight] = limitValue( (96 + (forward / 4)) * (clockwise ? 1 : -1),
			deadzoneOuter, deadzoneInner);
			motor[backRight] = limitValue( (96 + (forward / 4)) * (clockwise ? 1 : -1),
			deadzoneOuter, deadzoneInner);
		}
		else
		{
			motor[frontLeft] = limitValue( forward + strafe, deadzoneOuter, deadzoneInner );
			motor[frontRight] = limitValue( forward - strafe, deadzoneOuter, deadzoneInner );
			motor[backLeft] = limitValue( -forward + strafe, deadzoneOuter, deadzoneInner );
			motor[backRight] = limitValue( -forward - strafe, deadzoneOuter, deadzoneInner );
		}
	}

}
