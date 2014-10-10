#include <iostream>

#include "ANFScene.h"

// Vector3s for two lights
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
	failed = false;
	std::vector<std::string>::iterator it;

	usedIDs = std::vector<std::string> ();

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


}

void ANFScene::initCameras()
{
	std::vector<Camera*> camVec = cameras->getCameras();
	for (unsigned int i = 0; i < camVec.size(); i++)
	{
		scene_cameras.push_back(camVec[i]);
	}

}


void ANFScene::setCamera(Camera cam)
{
	std::vector<Camera*> camVec = cameras->getCameras();
	for (unsigned int i = 0; i < camVec.size(); i++)
	{
		if (cam.getID() == cameras->getActiveID())
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
	activeCamera = cameras->getActiveCamera();


	/* ------------- */
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->setKc(0.0); light0->setKl(0.2); light0->setKq(0.0);
	light0->disable();
	light0->enable();

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

	activeCamera = cameras->getActiveCamera();

	activeCamera->applyView();

	// Draw axis
	axis.draw();

	// ---- END Background, camera and axis setup

	// ---- BEGIN Primitive drawing section

	glPolygonMode(GL_FRONT_AND_BACK, global->getDrawMode());


	navigateGraph(graph->getRoot());

	light0->draw();
	//cube->draw();

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
	bool failed = false;
	std::vector<std::string>::iterator it;

	printf ("Processing Cameras\n");
	content = std::string (cameras->getElement()->Attribute ("initial"));
	cameras->setInitial(content);

	int cameraCount = 0;
	for(TiXmlElement* camera = cameras->getElement()->FirstChildElement(); camera != NULL; camera = camera->NextSiblingElement())
	{
		cameraCount ++;

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

			cameras->addCamera(cam);
		} else if (content == "ortho")
		{
			printf ("\tProcessing Orthogonal Camera\n");
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

			cameras->addCamera(cam);
		}
	}


	std::cout << "\tFound " << cameraCount << " camera(s)\n";

	cameras->setActiveID(cameras->getInitial());

	activeCamera = cameras->getActiveCamera();


	initCameras();
}

void ANFScene::processLights ()
{
	/* Block of Variables for processing */

	std::string content;
	float r, g, b, a, f, x, y, z;
	bool failed = false;
	std::vector<std::string>::iterator it;

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

						omniLight * omni = new omniLight(lightCounter - 1, position , NULL);

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
							spotLight * spot = new spotLight(lightCounter - 1, position , target);

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
							}
							lights.addLight(spot);
						}
					}
				}
			}
		}
	}

	printf("Parsed %u lights\n", lightCounter);
}

void ANFScene::processTextures ()
{
	/* Block of Variables for processing */

	std::string content;
	float r, g, b, a, f, x, y, z;
	bool failed = false;
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
		} else {
			std::cout << "ID " << content << " is already in use\n";
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
	bool failed = false;
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
		} else {
			std::cout << "ID " << content << " is already in use\n";
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
			Color* color = new Color();

			content = std::string ( component->Attribute("value"));

			const char * content_c = content.c_str();

			if(content_c && sscanf(content_c,"%f %f %f %f",&r, &g, &b, &a) == 4)
			{
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
	}
	std::cout << "\tFound " << appearenceCount << " appearence(s)\n";
}

void ANFScene::processGraph ()
{
	/* Block of Variables for processing */

	std::string content;
	float r, g, b, a, f, x, y, z;
	bool failed = false;
	std::vector<std::string>::iterator it;

	printf ("Processing Graph\n");

	content = std::string (graph->getElement()->Attribute ("root"));
	graph->setRootID(content);

	for(TiXmlElement* nodeEle = graph->getElement()->FirstChildElement(); nodeEle != NULL; nodeEle = nodeEle->NextSiblingElement())
	{

		content = std::string (nodeEle->Attribute ("id"));

		graphNode * node = new graphNode ();
		node->setElement(nodeEle);


		it = find (usedIDs.begin(), usedIDs.end(),  content);

		if (it == usedIDs.end())
		{
			node->setID (content);
		} else {
			std::cout << "ID " << content << " is already in use\n";
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

					printf ( "Translation added to %f, %f, %f\n\n" , x,y,z);
				}

			} else if ( content == "rotate") {

				RotateTransformation* rtransform =  new RotateTransformation ();

				content = std::string (transformation->Attribute ("axis"));

				if (! rtransform->setAxis (content.at(0)))
					failed = true;

				if (transformation->QueryFloatAttribute("angle",&f)==TIXML_SUCCESS)
					rtransform->setAngle (f);

				node->addTransformation(rtransform);
				printf ( "Rotation added in %c axis, by %f degrees\n\n" , rtransform->getAxis() , rtransform->getAngle());
			} else if (content == "scale") {
				content = std::string ( transformation->Attribute("factor"));

				const char * content_c = content.c_str();

				if(content_c && sscanf(content_c,"%f %f %f",&x, &y, &z) == 3)
				{
					node->addTransformation(new ScaleTransformation (x,y,z));
					printf ( "Scale added by %f, %f, %f\n\n" , x,y,z);
				}
			}
		}

		/* Process Appearence */

		/* Each node must have a non-empty primitive section or a descendants section */
		bool valid = false;

		/* Process Primitives */
		TiXmlElement* PrimitiveEle = nodeEle->FirstChildElement( "primitives" );


		/* Find all rectangles */
		for (TiXmlElement * rectangle = PrimitiveEle->FirstChildElement( "rectangle" ); rectangle != NULL; rectangle = rectangle->NextSiblingElement("rectangle"))
		{
			valid = true;

			Rectangle * rect = new Rectangle();

			content = std::string ( rectangle->Attribute("xy1"));

			const char * content_c = content.c_str();

			if(content_c && sscanf(content_c,"%f %f",&x, &y) == 2)
			{
				printf ( "Rectangle point 1  %f, %f\n" , x,y);
			}

			rect->setX1 (x);
			rect->setY1 (y);

			content = std::string ( rectangle->Attribute("xy2"));

			content_c = content.c_str();

			if(content_c && sscanf(content_c,"%f %f",&x, &y) == 2)
			{
				printf ( "Rectangle point 2  %f, %f\n\n" , x,y);
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

			if(content_c && sscanf(content_c,"%f %f %f",&x, &y, &z) == 3)
			{
				printf ( "Triangle point 1  %f, %f, %f\n" , x,y,z);
			}

			tri->setV1(Vector3(x,y,z));

			content = std::string ( triangle->Attribute("xyz2"));

			content_c = content.c_str();

			if(content_c && sscanf(content_c,"%f %f %f",&x, &y, &z) == 3)
			{
				printf ( "Triangle point 2  %f, %f, %f\n" , x,y,z);
			}

			tri->setV2(Vector3(x,y,z));

			content = std::string ( triangle->Attribute("xyz3"));

			content_c = content.c_str();

			if(content_c && sscanf(content_c,"%f %f %f",&x, &y, &z) == 3)
			{
				printf ( "Triangle point 3  %f, %f, %f\n" , x,y,z);
			}

			tri->setV3(Vector3(x,y,z));

			tri->updateNormal();

			node->addPrimitive(tri);
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
	generateGraph();
	
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

void ANFScene::navigateGraph (graphNode * node)
{
	node->setVisited(true);
	// Process node
	glPushMatrix();
	node->applyTransforms();
	node->draw();

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
	glPopMatrix();
	node->setVisited(false);
}

ANFScene::~ANFScene()
{
	delete(doc);
}