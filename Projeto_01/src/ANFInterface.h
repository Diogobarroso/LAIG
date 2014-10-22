#pragma once
#include "CGFinterface.h"

#include "ANFScene.h"

class ANFInterface :
	public CGFinterface
{
	ANFScene* anfscene;
public:
	ANFInterface(void);

	void initGUI();
	void processGUI(GLUI_Control *ctrl);

	~ANFInterface(void);
};

