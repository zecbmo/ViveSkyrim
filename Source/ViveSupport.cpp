/*
HORSE SPAWNER SCRIPT PLUGIN EXAMPLE

THIS FILE IS A PART OF THE SKYRIM DRAGON SCRIPT PROJECT
(C) Alexander Blade 2011
http://Alexander.SannyBuilder.com
*/
#define NOMINMAX
#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"
#include <math.h>
#include <openvr.h>
#include <string>
#include "Device.h"
#include "Controller.h"
//#include <openvr_capi.h>
//#include <openvr_driver.h>

#define CONFIG_FILE "horsespawner.ini" //using default names from template
#define SCR_NAME "Horse spawner"

//Globals




vr::IVRSystem* InitHMD();
void CheckTrackedDevices(vr::IVRSystem* hmd);
void Debug_ControllerInput(vr::IVRSystem* vr_system, Controller &right_controller, Controller &left_controller, Device &hmd, BYTE key);


void main()
{
	//Home key set up
	BYTE key = IniReadInt(CONFIG_FILE, "main", "key", 0);
		
	//hmf initialisation
	vr::IVRSystem *vr_system = NULL;
	vr_system = InitHMD();

	//Variables needed
	int framecount = 0;

	//controller init
	//Get the controller ID's from tracking system (vive)
	u_int right_controller_id = (u_int)vr_system->GetTrackedDeviceIndexForControllerRole(vr::TrackedControllerRole_RightHand);
	u_int left_controller_id = (u_int)vr_system->GetTrackedDeviceIndexForControllerRole(vr::TrackedControllerRole_LeftHand);
	PrintNote("Left Controller is: %d", left_controller_id);
	PrintNote("Right Controller is: %d", right_controller_id);	
	//Set up our controller class based on the IDs returned
	Controller right_controller, left_controller;
	Device hmd;

	CActor* player = Game::GetPlayer();

	right_controller.SetUp(right_controller_id, &framecount, player, vr_system);
	left_controller.SetUp(left_controller_id, &framecount, player, vr_system);
	hmd.SetUp(0, &framecount, player, vr_system);

	while (TRUE)
	{
		hmd.Update();
		right_controller.UpdateHandPosition(&hmd);
		left_controller.UpdateHandPosition(&hmd);

		Debug_ControllerInput(vr_system, right_controller, left_controller, hmd, key);

		



		framecount++;
		Wait(0); // In order to switch between script threads Wait() must be called anyway		
	}

	vr::VR_Shutdown();
}



void Debug_ControllerInput(vr::IVRSystem* vr_system, Controller &right_controller, Controller &left_controller, Device& hmd, BYTE key )
{
	if (GetKeyPressed(key))
	{
		//CheckTrackedDevices(hmd);
		bool temp = vr_system->IsInputFocusCapturedByAnotherProcess();
		if (temp == true)
		{
			PrintNote("Funciton working t");
		}
		else
		{
			PrintNote("Funciton working f");
		}
		if (vr_system == NULL)
		{
			PrintNote("Head set is null");
		}
		else
		{
			PrintNote("Headset pointer set %s", vr_system);
		}
		

	}

	if (right_controller.GetPressDown(vr::k_EButton_SteamVR_Trigger))
	{
		//PrintNote("Right Trigger Pressed");
		PrintNote("Player Pos: x = %.2f, y = %.2f, z = %.2f.  Offest: x = %.2f, y = %.2f, z = %.2f" , right_controller.body_pos.x, right_controller.body_pos.y, right_controller.body_pos.z, right_controller.offset.x, right_controller.offset.y, right_controller.offset.z);
		PrintNote("in_game_pos: x = %.2f, y = %.2f, z = %.2f", right_controller.in_game_pos.x, right_controller.in_game_pos.y, right_controller.in_game_pos.z);
		PrintNote("HMD: x = %.2f, y = %.2f, z = %.2f", hmd.GetTransform().pos.x, hmd.GetTransform().pos.y, hmd.GetTransform().pos.z);
		PrintNote("Right Controller: x = %.2f, y = %.2f, z = %.2f", right_controller.GetTransform().pos.x, right_controller.GetTransform().pos.y, right_controller.GetTransform().pos.z);


	}

	if (right_controller.GetPressDown(vr::k_EButton_SteamVR_Touchpad))
	{
		PrintNote("Right Touchpad Pressed");
	}

	if (right_controller.GetPressDown(vr::k_EButton_ApplicationMenu))
	{
		PrintNote("Right Menu Pressed");
	}

	if (right_controller.GetPressDown(vr::k_EButton_Grip))
	{
		PrintNote("Right Grip Pressed");
	}

	if (left_controller.GetPressDown(vr::k_EButton_SteamVR_Trigger))
	{
		PrintNote("Left Trigger Pressed");
	}

	if (left_controller.GetPressDown(vr::k_EButton_SteamVR_Touchpad))
	{
		PrintNote("Left Touchpad Pressed");
	}

	if (left_controller.GetPressDown(vr::k_EButton_ApplicationMenu))
	{
		PrintNote("Left Menu Pressed");
	}

	if (left_controller.GetPressDown(vr::k_EButton_Grip))
	{
		PrintNote("Left Grip Pressed");
	}


}
vr::IVRSystem* InitHMD()
{


	vr::EVRInitError eError = vr::VRInitError_None;
	vr::IVRSystem* hmd = vr::VR_Init(&eError, vr::VRApplication_Other);

	if (eError != vr::VRInitError_None)
	{
		PrintNote("Error: %s", eError);
	}
	else
	{
		PrintNote("HMD succesfully initialized");
	}
	//extra chech for my own sanity
	if (hmd == nullptr)
	{
		PrintNote("NULL POINTER HMD");
	}
	else
	{
		PrintNote("HMD pointer set");
	}

	return hmd;

}
void CheckTrackedDevices(vr::IVRSystem* hmd)
{
	for (int i = 0; i < vr::k_unMaxTrackedDeviceCount; i++)
	{
		vr::ETrackedDeviceClass temp = hmd->GetTrackedDeviceClass(i);


		if (temp == vr::TrackedDeviceClass_Invalid)
		{
			PrintNote("device %d: TrackedDeviceClass_Invalid", i);
		}
		if (temp == vr::TrackedDeviceClass_HMD)
		{
			PrintNote("device %d: TrackedDeviceClass_HMD", i);
		}
		if (temp == vr::TrackedDeviceClass_Controller)
		{
			PrintNote("device %d: TrackedDeviceClass_Controller", i);
		}
		if (temp == vr::TrackedDeviceClass_TrackingReference)
		{
			PrintNote("device %d: TrackedDeviceClass_TrackingReference", i);
		}
		if (temp == vr::TrackedDeviceClass_Other)
		{
			PrintNote("device %d: TrackedDeviceClass_Other", i);
		}

	}

}