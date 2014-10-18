#include <iostream>

#include "ANFScene.h"

// Vector3s for two lights



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

	failed = false;
	usedIDs = std::vector<std::string> ();
	appearenceStack = std::stack<Appearence *> ();

	/* -------------------------------- */

	/* Block of ANF Elements */
	global = new globalElement();
	if (!global->setElement (anfElement -> FirstChildElement ( "globals" )))
	{
		printf ("Globals Element not found\n");
		system("pause");
		return;
	}

	cameras = new cameraElement();
	if (!cameras->setElement (anfElement -> FirstChildElement ( "cameras" )))
	{
		printf ("Cameras Element not found\n");
		system("pause");
		return;
	}

	lights = lightElement();
	lights.setElement (anfElement -> FirstChildElement ( "lights" ));

	textures = new textureElement();
	if(!textures->setElement (anfElement -> FirstChildElement ( "textures" )))
	{
		printf ("Textures Element not found\n");
		system("pause");
		return;
	}

	appearences = new appearenceElement();
	if(!appearences->setElement (anfElement -> FirstChildElement ( "appearances" )))
	{
		printf ("Appearances Element not found\n");
		system("pause");
		return;
	}

	graph = new graphElement();
	if(!graph->setElement (anfElement -> FirstChildElement ( "graph" )))
	{
		printf ("Graph Element not found\n");
		system("pause");
		return;
	}

	/* --------------------- */

	processGlobal();
	processCameras();
	processLights();
	processTextures();
	processAppearences();
	processGraph();

	if (failed)
	{
		std::cout << "\nPlease check your ANF file for the errors listed above\n";
		system("pause");
		exit(1);
	}

	generateGraph();
	generateMatrices(graph->getRoot());

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
	if (global->getLightEnabled()) {
		glEnable (GL_LIGHTING);
	} else {
		glDisable (GL_LIGHTING);
	}

	if (global->getLightDS()) {
		glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	} else {
		glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	}


	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global->getLightAmbientColor().getArray());

	glCullFace(global->getCullFace());
	glFrontFace(global->getCullOrder());


	/* INIT CAMERA */
//	activeCamera = cameras->getActiveCamera();


	/* ------------- */

	for(unsigned int i = 0; i < lights.getLightSet().size(); i++)
	{
		lights.getLight(i)->setKc(0.0);
		lights.getLight(i)->setKl(0.2);
		lights.getLight(i)->setKq(0.0);
		scene_lights.push_back(lights.getLight(i));
	}
	//light0->enable();

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

//	activeCamera = cameras->getActiveCamera();

	activeCamera = scene_cameras[activeCameraIndex];
	activeCamera->applyView();

	// Draw axis
	axis.draw();

	// ---- END Background, camera and axis setup

	// ---- BEGIN Primitive drawing section

	glPolygonMode(GL_FRONT_AND_BACK, global->getDrawMode());

	//light0->draw();
	for(int i = 0; i < lights.getLightSet().size(); i++)
		lights.getLight(i)->draw();

	navigateGraph(graph->getRoot());

	// ---- END Primitive drawing section

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

void ANFScene::update(unsigned long t)
{

}

void ANFScene::processGlobal ()
{
	/* Block of Variables for processing */

	std::string content;
	float r, g, b, a, f, x, y, z;
	std::vector<std::string>::iterator it;

	printf ("Processing Globals\n");

	printf ("\tProcessing Drawing\n");

	TiXmlElement * drawingElement = global->getElement()->FirstChildElement("drawing");

	if (drawingElement)
	{
		content = std::string ( drawingElement->Attribute("mode"));
		if (!global->setDrawMode(content))
			failed = true;

		content = std::string ( drawingElement->Attribute("shading"));
		if (!global->setDrawShading(content))
			failed = true;

		content = std::string ( drawingElement->Attribute("background"));

		const char * content_c = content.c_str();

		if(content_c && sscanf(content_c,"%f %f %f %f",&r, &g, &b, &a) == 4)
		{
			if (!global->setDrawBackground(r, g, b, a))
				failed = true;
		}
	} else {
		printf ("\tDrawing Element not found\n");
		failed = true;
	}

	printf ("\tProcessing Culling\n");

	TiXmlElement * cullingElement = global->getElement()->FirstChildElement("culling");

	if (cullingElement)
	{
		content = std::string ( cullingElement->Attribute("face"));
		if (!global->setCullFace(content))
			failed = true;

		content = std::string ( cullingElement->Attribute("order"));
		if (!global->setCullOrder(content))
			failed = true;
	} else {
		printf ("\tCulling Element not found\n");
		failed = true;
	}

	printf ("\tProcessing Lighting\n");

	TiXmlElement * lightingElement = global->getElement()->FirstChildElement("lighting");

	if (lightingElement)
	{

		content = std::string ( lightingElement->Attribute("doublesided"));
		if (!global->setLightDS(content))
			failed = true;

		content = std::string ( lightingElement->Attribute("local"));
		if (!global->setLightLocal(content))
			failed = true;

		content = std::string ( lightingElement->Attribute("enabled"));
		if (!global->setLightEnabled(content))
			failed = true;

		content = std::string ( lightingElement->Attribute("ambient"));

		const char * content_c = content.c_str();

		if(content_c && sscanf(content_c,"%f %f %f %f",&r, &g, &b, &a) == 4)
		{
			if (!global->setLightAmbientColor(r, g, b, a))
				failed = true;
		}
	} else {
		printf ("\tLighting Element not found\n");
		failed = true;
	}
}

void ANFScene::processCameras ()
{
	/* Block of Variables for processing */

	std::string content;
	float r, g, b, a, f, x, y, z;
	std::vector<std::string>::iterator it;

	printf ("Processing Cameras\n");
	content = std::string (cameras->getElement()->Attribute ("initial"));
	cameras->setInitial(content);

	int cameraCount = 0;
	for(TiXmlElement* camera = cameras->getElement()->FirstChildElement(); camera != NULL; camera = camera->NextSiblingElement())
	{

		content = camera->Value();

		if (content == "perspective")
		{

			printf ("\tProcessing Perspective Camera\n");
			PerspectiveCamera* cam = new PerspectiveCamera();

			content = std::string ( camera->Attribute("id"));

			it = find (usedIDs.begin(), usedIDs.end(),  content);

			if (it == usedIDs.end())
			{
				cam->setID(content);
				usedIDs.push_back(content);
			} else {
				std::cout << "\tID " << content << " is already in use\n";
				failed = true;
			}

			if (content == cameras->getInitial())
				activeCameraIndex = cameraCount;

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

			content = std::string ( camera->Attribute("target"));

			content_c = content.c_str();

			if(content_c && sscanf(content_c,"%f %f %f",&x, &y, &z) == 3)
			{
				if (!cam->setTarget(x,y,z))
					failed = true;
			}
			
			scene_cameras.push_back(cam);
		} else if (content == "ortho")
		{
			printf ("\tProcessing Orthogonal Camera\n");
			OrthoCamera * cam = new OrthoCamera ();

			content = std::string ( camera->Attribute("id"));

			it = find (usedIDs.begin(), usedIDs.end(),  content);

			if (it == usedIDs.end())
			{
				cam->setID(content);
				usedIDs.push_back(content);
			} else {
				std::cout << "\tID " << content << " is already in use\n";
				failed = true;
			}

			if (content == cameras->getInitial())
				activeCameraIndex = cameraCount;

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

			scene_cameras.push_back(cam);
		}
		
		cameraCount ++;
	}

	std::cout << "\tFound " << cameraCount << " camera(s)\n";
/*
	for (unsigned int i = 0; i < camVec.size(); i++)
	{
		scene_cameras.push_back(camVec[i]);
	}
	*/
}

void ANFScene::processLights ()
{
	/* Block of Variables for processing */

	std::string content;
	float r, g, b, a, f, x, y, z;
	std::vector<std::string>::iterator it;

	int lightCounter = 0;
	float position[4];

	if(lights.getElement() == NULL)
		printf("Lights Element not found\n");
	else
	{
		printf("Processing Lights\n");
		TiXmlElement * lightIt = lights.getElement()->FirstChildElement("light");

		for(; lightIt != NULL; lightIt = lightIt->NextSiblingElement( "light" ))
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

						omniLight * omni = new omniLight(GL_LIGHT0 + lightCounter - 1, position , NULL);

						//content = std::string(lightIt->Attribute( "id" ));
						//omni->setId(content);

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
						printf("1\n");
						position[0] = x;
						position[1] = y;
						position[2] = z;

						content = std::string(lightIt->Attribute( "target" ));
						float target[4];
						float tmp[4];
						if(content.c_str() && sscanf(content.c_str(), "%f %f %f", &x, &y, &z) != 3)
							failed = true;
						else
						{
							target[0] = x;
							target[1] = y;
							target[2] = z;
							target[3] = 1.0;
							spotLight * spot = new spotLight(GL_LIGHT0 + lightCounter - 1, position , target);

							//content = std::string(lightIt->Attribute( "id" ));
							//spot->setId(content);

							content = std::string(lightIt->Attribute( "enabled" ));
							content == "true"? spot->enable() : spot->disable();

							content = std::string(lightIt->Attribute( "marker" ));
							content == "true"? spot->enableMarker() : spot->disableMarker();

							content = std::string(lightIt->Attribute( "pos" ));

							const char * content_c = content.c_str();

							if(content_c && sscanf(content_c, "%f %f %f", &tmp[0], &tmp[1], &tmp[2]) == 3)
							{
								tmp[3] = 1.0;
								spot->setPosition(tmp);
							}
							
							if(content_c && sscanf(content_c, "%f %f %f", &tmp[0], &tmp[1], &tmp[2]) == 3)
							{
								spot->setTarget(tmp);
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
								if(content_c && sscanf(content_c, "%f %f %f %f", &tmp[0], &tmp[1], &tmp[2], &tmp[3]) == 4)
									spot->setAmbient(tmp);

								component = component->NextSiblingElement("component");
								content = component->Attribute( "type" );
								if(content != "diffuse")
									failed = true;
								else
								{
									content_c = component->Attribute( "value" );
									if(content_c && sscanf(content_c, "%f %f %f %f", &tmp[0], &tmp[1], &tmp[2], &tmp[3]) == 4)
										spot->setDiffuse(tmp);
								}


								component = component->NextSiblingElement( "component" );
								content = component->Attribute( "type" );
								if(content != "specular")
									failed = true;
								else
								{
									content_c = component->Attribute( "value" );
									if(content_c && sscanf(content_c, "%f %f %f %f", &tmp[0], &tmp[1], &tmp[2], &tmp[3]) == 4)
										spot->setSpecular(tmp);
								}

								glEnable(GL_LIGHT0 + lightCounter - 1);
								lights.addLight(spot);
							}
						}
					}
				}
			}
		}

		printf("Parsed %u lights\n", lightCounter);
	}
}

void ANFScene::processTextures ()
{
	/* Block of Variables for processing */

	std::string content;
	float r, g, b, a, f, x, y, z;
	std::vector<std::string>::iterator it;

	printf ("Processing Textures\n");

	int textureCount = 0;
	for(TiXmlElement* textureElement = textures->getElement()->FirstChildElement(); textureElement != NULL; textureElement = textureElement->NextSiblingElement())
	{
		textureCount ++;

		Texture * texture = new Texture ();

		content = std::string ( textureElement->Attribute("id"));

		it = find (usedIDs.begin(), usedIDs.end(),  content);

		if (it == usedIDs.end())
		{
			texture->setID(content);
			usedIDs.push_back(content);
		} else {
			std::cout << "\tID " << content << " is already in use\n";
			failed = true;
		}

		content = std::string ( textureElement->Attribute("file"));
		texture->setPath (content);

		if (textureElement->QueryFloatAttribute("texlength_s", &f) == TIXML_SUCCESS)
			texture->setLength_s (f);

		if (textureElement->QueryFloatAttribute("texlength_t", &f) == TIXML_SUCCESS)
			texture->setLength_t (f);

		texture->updateTexture();

		textures->addTexture (texture);
	}

	std::cout << "\tFound " << textureCount << " textures(s)\n";

}

void ANFScene::processAppearences ()
{
	/* Block of Variables for processing */

	std::string content;
	float r, g, b, a, f, x, y, z;
	std::vector<std::string>::iterator it;

	int appearenceCount = 0;
	for(TiXmlElement* appearenceElement = appearences->getElement()->FirstChildElement(); appearenceElement != NULL; appearenceElement = appearenceElement->NextSiblingElement())
	{
		appearenceCount++;

		Appearence * appearence = new Appearence();

		content = std::string ( appearenceElement->Attribute("id"));

		it = find (usedIDs.begin(), usedIDs.end(),  content);

		if (it == usedIDs.end())
		{
			appearence->setID(content);
			usedIDs.push_back(content);
		} else {
			std::cout << "\tID " << content << " is already in use\n";
			failed = true;
		}

		if (appearenceElement->QueryFloatAttribute("shininess", &f) == TIXML_SUCCESS)
			appearence->setShininess(f);

		const char * texRef = appearenceElement->Attribute("textureref");

		if (texRef != NULL)
		{
			content = std::string (texRef);
			Texture * tex = textures->getTexture(content);
			if (tex != NULL)
				appearence->setTexture(tex);
			else
				std::cout << "Texture with ID = " << content << " not found\n\n";
		}

		// Booleans to check if it has all components
		bool hasAmbient = false;
		bool hasDiffuse = false;
		bool hasSpecular = false;

		for (TiXmlElement * component = appearenceElement->FirstChildElement(); component!= NULL; component = component->NextSiblingElement())
		{


			content = std::string ( component->Attribute("value"));

			const char * content_c = content.c_str();

			if(content_c && sscanf(content_c,"%f %f %f %f",&r, &g, &b, &a) == 4)
			{
				Color* color = new Color(r,g,b,a);
				content = std::string ( component->Attribute("type"));
				if (content == "ambient")
				{
					hasAmbient = true;
					appearence->setAmbient(color);
				} else if (content == "diffuse")
				{
					hasDiffuse = true;
					appearence->setDiffuse(color);
				} else if (content == "specular") {
					hasSpecular = true;
					appearence->setSpecular(color);
				} else {
					std::cout << "Unsupported component type " << content << " in Appearence " << appearence->getID() << endl << endl;
				}
			}

		}

		if (hasAmbient &&  hasDiffuse && hasSpecular)
		{
			appearence->generateAppearence();
		} else 
		{
			std::cout << "Error processing appearance " << appearence->getID() << endl << "Missing at least one of the components\n\n";
			failed = true;
		}

		appearences->addAppearence(appearence);
	}
	std::cout << "\tFound " << appearenceCount << " appearence(s)\n";
}

void ANFScene::processGraph ()
{
	/* Block of Variables for processing */

	std::string content;
	float r, g, b, a, f, x, y, z;
	std::vector<std::string>::iterator it;
	int s;

	printf ("Processing Graph\n");

	content = std::string (graph->getElement()->Attribute ("rootid"));
	graph->setRootID(content);

	for(TiXmlElement* nodeEle = graph->getElement()->FirstChildElement(); nodeEle != NULL; nodeEle = nodeEle->NextSiblingElement())
	{

		content = std::string (nodeEle->Attribute ("id"));

		std::cout << "Processing node " << content << endl;
		graphNode * node = new graphNode ();
		node->setElement(nodeEle);


		it = find (usedIDs.begin(), usedIDs.end(),  content);

		if (it == usedIDs.end())
		{
			node->setID (content);
			usedIDs.push_back(content);
		} else {
			std::cout << "\tID " << content << " is already in use\n";
			failed = true;
		}

		/* Process Transforms */
		TiXmlElement* TransformEle = nodeEle->FirstChildElement( "transforms" );

		for (TiXmlElement * transformation = TransformEle->FirstChildElement(); transformation != NULL; transformation = transformation->NextSiblingElement())
		{
			content = std::string (transformation->Attribute ( "type" ));

			if ( content == "translate" ) {
				content = std::string ( transformation->Attribute("to"));

				const char * content_c = content.c_str();

				if(content_c && sscanf(content_c,"%f %f %f",&x, &y, &z) == 3)
				{
					node->addTransformation(new TranslateTransformation (x,y,z));
				}

			} else if ( content == "rotate") {

				RotateTransformation* rtransform =  new RotateTransformation ();

				content = std::string (transformation->Attribute ("axis"));

				if (! rtransform->setAxis (content.at(0)))
					failed = true;

				if (transformation->QueryFloatAttribute("angle",&f)==TIXML_SUCCESS)
					rtransform->setAngle (f);

				node->addTransformation(rtransform);

			} else if (content == "scale") {
				content = std::string ( transformation->Attribute("factor"));

				const char * content_c = content.c_str();

				if(content_c && sscanf(content_c,"%f %f %f",&x, &y, &z) == 3)
				{
					node->addTransformation(new ScaleTransformation (x,y,z));
				}
			}
		}

		/* Process Appearence */

		TiXmlElement* appElement = nodeEle->FirstChildElement( "appearanceref" );
		content = std::string (appElement->Attribute("id"));
		Appearence * app = appearences->getAppearence(content);

		if (content != "inherit" && app != NULL)
		{
			node->setAppearence(app);
		} else if (content != "inherit") {
			std::cout << "\tError\n\tAppearence id = " << content << " does not exist in " << node->getID() << endl << endl;
			failed = true;
		} else {
			node->setAppearence(NULL);
		}		

		/* Each node must have a non-empty primitive section or a descendants section */
		bool valid = false;

		/* Process Primitives */
		TiXmlElement* PrimitiveEle = nodeEle->FirstChildElement( "primitives" );


		/* Find all rectangles */
		if (PrimitiveEle != NULL)
		{
			for (TiXmlElement * rectangle = PrimitiveEle->FirstChildElement( "rectangle" ); rectangle != NULL; rectangle = rectangle->NextSiblingElement("rectangle"))
			{
				valid = true;

				Rectangle * rect = new Rectangle();

				content = std::string ( rectangle->Attribute("xy1"));

				const char * content_c = content.c_str();

				if(!content_c || sscanf(content_c,"%f %f",&x, &y) != 2)
				{
					std::cout << "Error parsing rectangle Point 1 in " << node->getID() << endl << endl;
				}

				rect->setX1 (x);
				rect->setY1 (y);

				content = std::string ( rectangle->Attribute("xy2"));

				content_c = content.c_str();

				if(!content_c || sscanf(content_c,"%f %f",&x, &y) != 2)
				{
					std::cout << "Error parsing rectangle Point 2 in " << node->getID() << endl << endl;
				}

				rect->setX2 (x);
				rect->setY2 (y);

				rect->calculateVertex();
				node->addPrimitive(rect);
			}

			/* Find all triangles */
			for (TiXmlElement * triangle = PrimitiveEle->FirstChildElement( "triangle" ); triangle != NULL; triangle = triangle->NextSiblingElement("triangle"))
			{
				valid = true;

				Triangle * tri = new Triangle();

				content = std::string ( triangle->Attribute("xyz1"));

				const char * content_c = content.c_str();

				if(!content_c || sscanf(content_c,"%f %f %f",&x, &y, &z) != 3)
				{
					std::cout << "Error parsing triangle Point 1 in " << node->getID() << endl << endl;
				}

				tri->setV1(Vector3(x,y,z));

				content = std::string ( triangle->Attribute("xyz2"));

				content_c = content.c_str();

				if(!content_c || sscanf(content_c,"%f %f %f",&x, &y, &z) != 3)
				{
					std::cout << "Error parsing triangle Point 2 in " << node->getID() << endl << endl;
				}

				tri->setV2(Vector3(x,y,z));

				content = std::string ( triangle->Attribute("xyz3"));

				content_c = content.c_str();

				if(!content_c || sscanf(content_c,"%f %f %f",&x, &y, &z) != 3)
				{
					std::cout << "Error parsing triangle Point 3 in " << node->getID() << endl << endl;
				}

				tri->setV3(Vector3(x,y,z));

				tri->updateNormal();
				tri->calculateSizes();

				node->addPrimitive(tri);
			}

			/* Find all cylinders */
			for (TiXmlElement * cylinder = PrimitiveEle->FirstChildElement( "cylinder" ); cylinder != NULL; cylinder = cylinder->NextSiblingElement("cylinder"))
			{
				valid = true;

				Cylinder * cyl = new Cylinder();

				if (cylinder->QueryFloatAttribute("base",&f)==TIXML_SUCCESS)
					cyl->setBase(f);

				if (cylinder->QueryFloatAttribute("top",&f)==TIXML_SUCCESS)
					cyl->setTop(f);

				if (cylinder->QueryFloatAttribute("height",&f)==TIXML_SUCCESS)
					cyl->setHeight(f);

				if (cylinder->QueryIntAttribute("slices",&s)==TIXML_SUCCESS)
					cyl->setSlices(s);

				if (cylinder->QueryIntAttribute("stacks",&s)==TIXML_SUCCESS)
					cyl->setStacks(s);

				node->addPrimitive(cyl);
			}

			/* Find all cylinders */
			for (TiXmlElement * sphere = PrimitiveEle->FirstChildElement( "sphere" ); sphere != NULL; sphere = sphere->NextSiblingElement("sphere"))
			{
				valid = true;

				Sphere * sph = new Sphere();

				if (sphere->QueryFloatAttribute("radius",&f)==TIXML_SUCCESS)
					sph->setRadius(f);

				if (sphere->QueryIntAttribute("slices",&s)==TIXML_SUCCESS)
					sph->setSlices(s);

				if (sphere->QueryIntAttribute("stacks",&s)==TIXML_SUCCESS)
					sph->setStacks(s);

				node->addPrimitive(sph);
			}

			/* Find all torus */
			for (TiXmlElement * torus = PrimitiveEle->FirstChildElement( "torus" ); torus != NULL; torus = torus->NextSiblingElement("torus"))
			{
				valid = true;

				Torus * tor = new Torus();

				if (torus->QueryFloatAttribute("inner",&f)==TIXML_SUCCESS)
					tor->setInner(f);

				if (torus->QueryFloatAttribute("outer",&f)==TIXML_SUCCESS)
					tor->setOuter(f);

				if (torus->QueryIntAttribute("slices",&s)==TIXML_SUCCESS)
					tor->setSlices(s);

				if (torus->QueryIntAttribute("loops",&s)==TIXML_SUCCESS)
					tor->setLoops(s);

				tor->generateVertices();

				node->addPrimitive(tor);
			}
		}
		/* Process Descendants */

		TiXmlElement * descendants = nodeEle->FirstChildElement("descendants");
		if (descendants != NULL)
		{
			TiXmlElement * descendant = descendants->FirstChildElement( "noderef" );
			if (descendant != NULL)
				for (descendant; descendant != NULL; descendant = descendant->NextSiblingElement("noderef"))
				{
					valid = true;
					content = std::string ( descendant->Attribute("id"));
					node->addDescendantID(content);
				}

		} 

		if (valid)
			graph->addNode(node);
	}

	/* Generate Graph */

	graph->setRoot();
}

bool ANFScene::generateGraph ()
{
	std::vector<graphNode*> nodesVec = graph->getNodes();

	for (unsigned int i = 0; i < nodesVec.size(); i++)
	{
		std::vector<std::string> descendantsID = nodesVec[i]->getDescendantsID();
		for (unsigned int desc = 0; desc < descendantsID.size(); desc++)
		{
			graphNode * n = graph->getNode(descendantsID[desc]);
			if (n != NULL)
				nodesVec[i]->addDescendant(n);
			else
			{
				std::cout << "Error building scene graph\nNode " << descendantsID[desc] << " not found\n\n";
				return false;
			}
		}
	}

	return true;
}

void ANFScene::generateMatrices (graphNode * node)
{
	glLoadIdentity();
	node->applyTransforms();

	std::vector <graphNode *> descendants = node->getDescendants();

	glGetFloatv(GL_MODELVIEW_MATRIX, node->matrix);

	for (unsigned int desc = 0; desc < descendants.size(); desc++)
	{
		graphNode * descNode = descendants[desc];
		if (! descNode->getVisited())
		{
			// Recursive call
			generateMatrices (descendants[desc]);
		}
	}
}

void ANFScene::navigateGraph (graphNode * node)
{
	Appearence * actualAppearence = node->getAppearence();

	if (actualAppearence != NULL)
	{
		appearenceStack.push(actualAppearence);
	}

	node->setVisited(true);
	// Process node
	glPushMatrix();

	glMultMatrixf(node->matrix);

	appearenceStack.top()->apply();

	Texture * tex = appearenceStack.top()->getTexture();
	if (tex == NULL)
		node->draw(1,1);
	else
		node->draw(tex->getLength_s(), tex->getLength_t());

	std::vector <graphNode *> descendants = node->getDescendants();

	for (unsigned int desc = 0; desc < descendants.size(); desc++)
	{
		graphNode * descNode = descendants[desc];
		if (! descNode->getVisited())
		{
			// Recursive call
			navigateGraph (descendants[desc]);
		}
	}

	// Reverse node processing
	if (actualAppearence != NULL)
	{
		appearenceStack.pop();
	}
	glPopMatrix();
	node->setVisited(false);
}

ANFScene::~ANFScene()
{
	delete(doc);
}