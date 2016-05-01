/* 
	USE THIS ONE AS A TEMPLATE FOR YOUR SCRIPT PLUGINS
*/

#include "common\skyscript.h"
#include "common\obscript.h"
#include "common\types.h"
#include "common\enums.h"
#include "common\plugin.h"
#include "openvr.h"

void main()
{
	PrintNote("dummy script launched");
	vr::HmdError error_check;
	vr::IVRSystem* openvr = vr::VR_Init(&error_check, vr::VRApplication_Other);

	while (TRUE)
	{
		




		Wait(0);
	}
	vr::VR_Shutdown();
}

