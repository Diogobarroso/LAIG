#include "ANFInterface.h"
#include "CGFapplication.h"

ANFInterface::ANFInterface(void)
{

}

void ANFInterface::initGUI()
{
	anfscene = (ANFScene *) scene;

	GLUI_Panel* cameraPanel = addPanel("Cameras", 1);
	addColumn();

	GLUI_Panel * drawPanel = addPanel("Draw Mode", 1);

	GLUI_RadioGroup* drawGroup = addRadioGroupToPanel(drawPanel, anfscene->getActiveDrawModePointer(), 2);
	addRadioButtonToGroup(drawGroup, "Fill");
	addRadioButtonToGroup(drawGroup, "Line");
	addRadioButtonToGroup(drawGroup, "Point");

	addColumn();

	GLUI_RadioGroup* cameraGroup = addRadioGroupToPanel(cameraPanel, anfscene->getActiveCameraIndexPointer(), 1);

	GLUI_Panel *lightPanel = addPanel("Luzes", 1);
	for( unsigned int i=0; i<anfscene->getLights().size(); i++ )
		addCheckboxToPanel( lightPanel, anfscene->getLight(i)->getName(), &(anfscene->lightsEnabled[i]), 0 );

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
