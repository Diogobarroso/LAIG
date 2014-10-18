#include "ANFInterface.h"
#include "CGFapplication.h"

ANFInterface::ANFInterface(void)
{

}

void ANFInterface::initGUI()
{
	anfscene = (ANFScene *) scene;

	GLUI_Panel* cameraPanel = addPanel("Cameras", 1);

	GLUI_RadioGroup* cameraGroup = addRadioGroupToPanel(cameraPanel, anfscene->getActiveCameraIndexPointer(), 1);


	std::vector <Camera *> cameras = anfscene->getCameras();
	for (unsigned int cam = 0; cam < cameras.size(); cam ++)
	{
		addRadioButtonToGroup(cameraGroup,(char*)cameras[cam]->getID().c_str());
	}


}

void ANFInterface::processGUI(GLUI_Control *ctrl)
{
	switch (ctrl->user_id)
	{
	case 1:
		{
			anfscene->setActiveCameraIndex(ctrl->int_val);
		};

	};
}

ANFInterface::~ANFInterface(void)
{
}
