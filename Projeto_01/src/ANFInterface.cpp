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
	
	addColumn();
	
	GLUI_Panel * drawPanel = addPanel("Draw Mode", 1);

	GLUI_RadioGroup* drawGroup = addRadioGroupToPanel(drawPanel, anfscene->getActiveDrawModePointer(), 2);

	addRadioButtonToGroup(drawGroup, "Fill");
	addRadioButtonToGroup(drawGroup, "Line");
	addRadioButtonToGroup(drawGroup, "Point");

}

void ANFInterface::processGUI(GLUI_Control *ctrl)
{
	switch (ctrl->user_id)
	{
	case 1:
		{
			anfscene->setActiveCameraIndex(ctrl->int_val);
			break;
		};
	case 2:
		{
			anfscene->setActiveDrawMode(ctrl->int_val);
			break;
		};
	};
}

ANFInterface::~ANFInterface(void)
{
}
