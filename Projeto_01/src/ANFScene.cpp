#include <iostream>

#include "ANFScene.h"

// Positions for two lights
float light0_pos[4] = {1, 2, 1, 1};

ANFScene::ANFScene(char *filename)
{

	// Read XML from file

	doc=new TiXmlDocument( filename );
	bool loadOkay = doc->LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );

		system("pause");
		exit( 1 );
	}

	TiXmlElement* anfElement= doc->FirstChildElement( "anf" );

	if (anfElement == NULL)
	{
		printf("Main anf block element not found! Exiting!\n");
		exit(1);
	}

	/* Block of Variables for processing */

	std::string content;
	float r, g, b, a, f, x, y, z;
	bool failed = false;
	std::vector<std::string>::iterator it;

	usedIDs = std::vector<std::string> ();

	/* -------------------------------- */

	/* Block of ANF Elements */
	global = globalElement();
	global.setElement (anfElement -> FirstChildElement ( "globals" ));

	cameras = cameraElement();
	cameras.setElement (anfElement -> FirstChildElement ( "cameras" ));

	lights = lightElement();
	lights.setElement (anfElement -> FirstChildElement ( "lights" ));

	/* --------------------- */

	if (global.getElement() == NULL)
		printf ("Globals Element not found\n");
	else
	{
		printf ("Processing Globals\n");

		printf ("Processing Drawing\n");

		TiXmlElement * drawingElement = global.getElement()->FirstChildElement("drawing");

		if (drawingElement)
		{
			content = std::string ( drawingElement->Attribute("mode"));
			if (!global.setDrawMode(content))
				failed = true;

			content = std::string ( drawingElement->Attribute("shading"));
			if (!global.setDrawShading(content))
				failed = true;

			content = std::string ( drawingElement->Attribute("background"));

			const char * content_c = content.c_str();

			if(content_c && sscanf(content_c,"%f %f %f %f",&r, &g, &b, &a) == 4)
			{
				if (!global.setDrawBackground(r, g, b, a))
					failed = true;
			}
		} else {
			printf ("Drawing Element not found\n");
			failed = true;
		}

		printf ("Processing Culling\n");

		TiXmlElement * cullingElement = global.getElement()->FirstChildElement("culling");

		if (cullingElement)
		{
			content = std::string ( cullingElement->Attribute("face"));
			if (!global.setCullFace(content))
				failed = true;

			content = std::string ( cullingElement->Attribute("order"));
			if (!global.setCullOrder(content))
				failed = true;
		} else {
			printf ("Culling Element not found\n");
			failed = true;
		}

		printf ("Processing Lighting\n");

		TiXmlElement * lightingElement = global.getElement()->FirstChildElement("lighting");

		if (lightingElement)
		{

			content = std::string ( lightingElement->Attribute("doublesided"));
			if (!global.setLightDS(content))
				failed = true;

			content = std::string ( lightingElement->Attribute("local"));
			if (!global.setLightLocal(content))
				failed = true;

			content = std::string ( lightingElement->Attribute("enabled"));
			if (!global.setLightEnabled(content))
				failed = true;

			content = std::string ( lightingElement->Attribute("ambient"));

			const char * content_c = content.c_str();

			if(content_c && sscanf(content_c,"%f %f %f %f",&r, &g, &b, &a) == 4)
			{
				if (!global.setLightAmbientColor(r, g, b, a))
					failed = true;
			}
		} else {
			printf ("Lighting Element not found\n");
			failed = true;
		}

	}

	if (cameras.getElement() == NULL)
		printf ("Cameras Element not found\n");
	else
	{
		content = std::string (cameras.getElement()->Attribute ("initial"));
		cameras.setInitial(content);

		int cameraCount = 0;
		for(TiXmlElement* camera = cameras.getElement()->FirstChildElement(); camera != NULL; camera = camera->NextSiblingElement())
		{
			cameraCount ++;

			content = camera->Value();

			if (content == "perspective")
			{
				PerspectiveCamera* cam = new PerspectiveCamera();

				content = std::string ( camera->Attribute("id"));

				it = find (usedIDs.begin(), usedIDs.end(),  content);

				if (it == usedIDs.end())
				{
					cam->setID(content);
				} else {
					std::cout << "ID " << content << " is already in use\n";
					failed = true;
				}

				if (camera->QueryFloatAttribute("near",&f)==TIXML_SUCCESS)
					if (!cam->setNear(f))
						failed = true;

				if (camera->QueryFloatAttribute("far",&f)==TIXML_SUCCESS)
					if (!cam->setFar(f))
						failed = true;

				if (camera->QueryFloatAttribute("angle",&f)==TIXML_SUCCESS)
					if (!cam->setAngle(f))
						failed = true;

				content = std::string ( camera->Attribute("pos"));

				const char * content_c = content.c_str();

				if(content_c && sscanf(content_c,"%f %f %f",&x, &y, &z) == 3)
				{
					if (!cam->setPos(x,y,z))
						failed = true;
				}

				cameras.addCamera(cam);
			} else if (content == "ortho")
			{
				OrthoCamera * cam = new OrthoCamera ();

				content = std::string ( camera->Attribute("id"));

				it = find (usedIDs.begin(), usedIDs.end(),  content);

				if (it == usedIDs.end())
				{
					cam->setID(content);
				} else {
					std::cout << "ID " << content << " is already in use\n";
					failed = true;
				}

				if (camera->QueryFloatAttribute("near",&f)==TIXML_SUCCESS)
					if (!cam->setNear(f))
						failed = true;

				if (camera->QueryFloatAttribute("far",&f)==TIXML_SUCCESS)
					if (!cam->setFar(f))
						failed = true;

				if (camera->QueryFloatAttribute("left",&f)==TIXML_SUCCESS)
					if (!cam->setLeft(f))
						failed = true;

				if (camera->QueryFloatAttribute("right",&f)==TIXML_SUCCESS)
					if (!cam->setRight(f))
						failed = true;

				if (camera->QueryFloatAttribute("top",&f)==TIXML_SUCCESS)
					if (!cam->setTop(f))
						failed = true;

				if (camera->QueryFloatAttribute("bottom",&f)==TIXML_SUCCESS)
					if (!cam->setBottom(f))
						failed = true;

				content = std::string ( camera->Attribute("direction"));
				if (!cam->setAxis(content.at(0)))
					failed = true;

				cameras.addCamera(cam);
			}
		}


		std::cout << "Found " << cameraCount << " camera(s)\n";

		cameras.setActiveID(cameras.getInitial());

		activeCamera = cameras.getActiveCamera();
	}

	int lightCounter = 0;
	float position[3];

	if(lights.getElement() == NULL)
		printf("Lights Element not found\n");
	else
	{
		printf("Processing Lights\n");
		TiXmlElement * lightIt = lights.getElement()->FirstChildElement("light");

		for(lightIt; lightIt != NULL; lightIt = lightIt->NextSiblingElement( "light" ))
		{
			lightCounter++;
			printf("The lightCounter is %u, next Light is called %s\n", lightCounter, lightIt->Attribute( "id" ));

			if(lightCounter >= 8)
				break;
			else
			{
				content = std::string(lightIt->Attribute( "type" ));
				if(content == "omni")
				{

					content = std::string(lightIt->Attribute( "pos" ));
					const char * content_c = content.c_str();
					if(content_c && sscanf(content_c, "%f %f %f", &x, &y, &z) != 3)
						failed = true;
					else
					{
						position[0] = x;
						position[1] = y;
						position[2] = z;

						omniLight * omni = new omniLight((lightCounter - 1), position , NULL);

						content = std::string(lightIt->Attribute( "id" ));
						omni->setId(content);

						content = std::string(lightIt->Attribute( "enabled" ));
						content == "true"? omni->enable() : omni->disable();

						content = std::string(lightIt->Attribute( "marker" ));
						content == "true"? omni->enableMarker() : omni->disableMarker();

						TiXmlElement * component = lightIt->FirstChildElement( "component" );
						content = component->Attribute( "type" );
						if(content != "ambient")
							failed = true;
						else
						{
							content_c = component->Attribute( "value" );
							if(content_c && sscanf(content_c, "%f %f %f %f", &r, &g, &b, &a) == 4)
								if(!omni->setAmbient(Color(r,g,b,a)))
									failed = true;
						}

						component = component->NextSiblingElement( "component" );
						content = component->Attribute( "type" );
						if(content != "diffuse")
							failed = true;
						else
						{
							content_c = component->Attribute( "value" );
							if(content_c && sscanf(content_c, "%f %f %f %f", &r, &g, &b, &a) == 4)
								if(!omni->setDiffuse(Color(r,g,b,a)))
									failed = true;
						}

						component = component->NextSiblingElement( "component" );
						content = component->Attribute( "type" );
						if(content != "specular")
							failed = true;
						else
						{
							content_c = component->Attribute( "value" );
							if(content_c && sscanf(content_c, "%f %f %f %f", &r, &g, &b, &a) == 4)
								if(!omni->setSpecular(Color(r,g,b,a)))
									failed = true;
						}

						lights.addLight(omni);
					}
				}
				else if(content == "spot")
				{
					content = std::string(lightIt->Attribute( "pos" ));
					const char * content_c = content.c_str();
					if(content_c && sscanf(content_c, "%f %f %f", &x, &y, &z) != 3)
						failed = true;
					else
					{
						position[0] = x;
						position[1] = y;
						position[2] = z;

						content = std::string(lightIt->Attribute( "target" ));
						float target[3];
						if(content.c_str() && sscanf(content.c_str(), "%f %f %f", &x, &y, &z) != 3)
							failed = true;
						else
						{
							target[0] = x;
							target[1] = y;
							target[2] = z;
							spotLight * spot = new spotLight((lightCounter - 1), position , target);

							content = std::string(lightIt->Attribute( "id" ));
							spot->setId(content);

							content = std::string(lightIt->Attribute( "enabled" ));
							content == "true"? spot->enable() : spot->disable();

							content = std::string(lightIt->Attribute( "marker" ));
							content == "true"? spot->enableMarker() : spot->disableMarker();

							content = std::string(lightIt->Attribute( "pos" ));

							const char * content_c = content.c_str();

							if(content_c && sscanf(content_c, "%f %f %f", &x, &y, &z) == 3)
							{
								if(!spot->setPosition(x,y,z))
									failed = true;
							}

							if(content_c && sscanf(content_c, "%f %f %f", &x, &y, &z) == 3)
							{
								if(!(spot->setTarget(x,y,z)))
									failed = true;
							}

							float f;

							if(lightIt->QueryFloatAttribute("angle",&f)==TIXML_SUCCESS)
								spot->setAngle(f);

							if(lightIt->QueryFloatAttribute("exponent",&f)==TIXML_SUCCESS)
								spot->setExponent(f);

							TiXmlElement * component = lightIt->FirstChildElement( "component" );
							content = component->Attribute( "type" );
							if(content != "ambient")
								failed = true;
							else
							{
								content_c = component->Attribute( "value" );
								if(content_c && sscanf(content_c, "%f %f %f %f", &r, &g, &b, &a) == 4)
									if(!spot->setAmbient(Color(r,g,b,a)))
										failed = true;
							}
							
							component = component->NextSiblingElement("component");
							content = component->Attribute( "type" );
							if(content != "diffuse")
								failed = true;
							else
							{
								content_c = component->Attribute( "value" );
								if(content_c && sscanf(content_c, "%f %f %f %f", &r, &g, &b, &a) == 4)
									if(!spot->setDiffuse(Color(r,g,b,a)))
										failed = true;
							}

							component = component->NextSiblingElement( "component" );
							content = component->Attribute( "type" );
							if(content != "specular")
								failed = true;
							else
							{
								content_c = component->Attribute( "value" );
								if(content_c && sscanf(content_c, "%f %f %f %f", &r, &g, &b, &a) == 4)
									if(!spot->setSpecular(Color(r,g,b,a)))
										failed = true;
								cout << failed << "bananas\n";
							}
							lights.addLight(spot);
						}
					}
				}
			}
		}
	}

	printf("Parsed %u lights\n", lightCounter);
	/*
	content = std::string (cameras.getElement()->Attribute ("initial"));
	cameras.setInitial (content);



	TiXmlElement * camera = cameras.getElement()->FirstChildElement("perspective");

	while (camera)
	{
	cameraCount ++;

	PerspectiveCamera* cam = new PerspectiveCamera();

	content = std::string ( camera->Attribute("id"));

	it = find (usedIDs.begin(), usedIDs.end(),  content);

	if (it == usedIDs.end())
	{
	cam->setID(content);
	} else {
	std::cout << "ID " << content << " is already in use\n";
	failed = true;
	}



	if (camera->QueryFloatAttribute("near",&f)==TIXML_SUCCESS)
	if (!cam->setNear(f))
	failed = true;

	if (camera->QueryFloatAttribute("far",&f)==TIXML_SUCCESS)
	if (!cam->setFar(f))
	failed = true;

	if (camera->QueryFloatAttribute("angle",&f)==TIXML_SUCCESS)
	if (!cam->setAngle(f))
	failed = true;

	content = std::string ( camera->Attribute("pos"));

	const char * content_c = content.c_str();

	if(content_c && sscanf(content_c,"%f %f %f",&x, &y, &z) == 3)
	{
	if (!cam->setPos(x,y,z))
	failed = true;
	}

	cameras.addCamera(cam);

	camera = camera->NextSiblingElement();
	}

	std::cout << "Found " << cameraCount << " perspective camera(s)\n";
	cameras.setActiveID(cameras.getInitial());

	}
	*/

	initCameras();
	initLights();

	if (failed)
	{
		std::cout << "\nPlease check your ANF file for the errors listed above\n";
		system("pause");
		exit(1);
	}
}

void ANFScene::initCameras()
{
	std::vector<Camera*> camVec = cameras.getCameras();
	for (unsigned int i = 0; i < camVec.size(); i++)
	{
		scene_cameras.push_back(camVec[i]);
	}

}

void ANFScene::initLights()
{
	std::vector<light * > lightVec = lights.getLightSet();
	for(unsigned int i = 0; i < lightVec.size(); i++)
	{
		lightVec[i]->setKc(0.0);
		lightVec[i]->setKl(0.2);
		lightVec[i]->setKq(0.0);
		scene_lights.push_back(lightVec[i]);
	}
}

void ANFScene::setCamera(Camera cam)
{
	std::vector<Camera*> camVec = cameras.getCameras();
	for (unsigned int i = 0; i < camVec.size(); i++)
	{
		if (cam.getID() == cameras.getActiveID())
		{
			activateCamera(i);
			break;
		}
	}
}

//-------------------------------------------------------

TiXmlElement * ANFScene::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
	// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
	// A more elaborate version of this would rely on XPath expressions
{
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
			found=1;
		else
			child=child->NextSiblingElement();

	return child;
}

void ANFScene::init()
{
	if (global.getLightEnabled()) {
		glEnable (GL_LIGHTING);
	} else {
		glDisable (GL_LIGHTING);
	}

	if (global.getLightDS()) {
		glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	} else {
		glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	}

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global.getLightAmbientColor().getArray());

	glCullFace(global.getCullFace());
	glFrontFace(global.getCullOrder());


	/* INIT CAMERA */
	activeCamera = cameras.getActiveCamera();
	activeCamera->updateProjectionMatrix(1,1);


	/* ------------- 
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setKc(0.0); light0->setKl(0.2); light0->setKq(0.0);
	light0->disable();
	light0->enable();
	*/

	glEnable(GL_LIGHT0);

	cube = new myUnitCube();
}

void ANFScene::display()
{
	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	//CGFscene::activeCamera->applyView();

	activeCamera = cameras.getActiveCamera();

	activeCamera->applyView();

	// Draw axis
	axis.draw();

	// ---- END Background, camera and axis setup

	// ---- BEGIN Primitive drawing section
	//light0->draw();
	lights.getLightSet()[0]->draw();

	cube->draw();

	// ---- END Primitive drawing section

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

void ANFScene::update(unsigned long t)
{
}

ANFScene::~ANFScene()
{
	delete(doc);
}