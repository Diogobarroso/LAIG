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

	GLUI_RadioGroup* cameraGroup = addRadioGroupToPanel(cameraPanel, anfscene->getActiveCameraIndexPointer(), 1);

	GLUI_Panel *luzesPanel = addPanel("Luzes", 1);
	for(unsigned int i=0;i<((ANFScene *) scene)->getLights().size();i++){
		string str=((ANFScene *) scene)->getLight(i)->getName();
		char * writable = new char[str.size() + 1];
		copy(str.begin(), str.end(), writable);
		writable[str.size()] = '\0';
		if((((ANFScene *) scene)->getLight(i)->isEnabled())== true){
			addCheckboxToPanel(luzesPanel,writable,NULL,i)->set_int_val(1);
		}
		else{
			addCheckboxToPanel(luzesPanel,writable,NULL,i)->set_int_val(0);
		}
		delete[] writable;
	}




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
	case 3:
		{
			anfscene->getLight(3)->isEnabled()? anfscene->getLight(3)->disable() : anfscene->getLight(3)->enable();
		}
	};
}

ANFInterface::~ANFInterface(void)
{
}
