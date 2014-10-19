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

	addColumn();

	GLUI_Panel *lightPanel = addPanel("Lights", 1);
	for(unsigned int i=0;i<anfscene->getLights().size();i++)
	{
		string str=anfscene->getLight(i)->getName();
		char * writable = new char[str.size() + 1];
		copy(str.begin(), str.end(), writable);
		writable[str.size()] = '\0';
		if((*anfscene->getLight(i)->isEnabled())== 1){
			addCheckboxToPanel(lightPanel,writable,NULL,i)->set_int_val(1);
		}
		else{
			addCheckboxToPanel(lightPanel,writable,NULL,i)->set_int_val(0);
		}
		delete[] writable;
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
