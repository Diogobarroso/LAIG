#include <iostream>

#include "ANFScene.h"

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
	float r, g, b, a;
	bool failed = false;
	
	/* -------------------------------- */

	/* Block of ANF Elements */
	global = globalElement();
	global.setElement (anfElement -> FirstChildElement ( "globals" ));

	if (global.getElement() == NULL)
		printf ("Globals Element not found\n");
	else
	{
		printf ("Processing Globals\n");
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
			

		}
	}

	/*
	initElement = anfElement->FirstChildElement( "Init" );
	matsElement = anfElement->FirstChildElement( "Materials" );
	textsElement =  anfElement->FirstChildElement( "Textures" );
	leavesElement =  anfElement->FirstChildElement( "Leaves" );
	nodesElement =  anfElement->FirstChildElement( "Nodes" );

	graphElement =  anfElement->FirstChildElement( "Graph" );


	// Init
	// An example of well-known, required nodes

	if (initElement == NULL)
		printf("Init block not found!\n");
	else
	{
		printf("Processing init:\n");
		// frustum: example of a node with individual attributes
		TiXmlElement* frustumElement=initElement->FirstChildElement("frustum");
		if (frustumElement)
		{
			float near,far;

			if (frustumElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS && 
				frustumElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS
				)
				printf("  frustum attributes: %f %f\n", near, far);
			else
				printf("Error parsing frustum\n");
		}
		else
			printf("frustum not found\n");


		// translate: example of a node with an attribute comprising several float values
		// It shows an example of extracting an attribute's value, and then further parsing that value 
		// to extract individual values
		TiXmlElement* translateElement=initElement->FirstChildElement("translate");
		if (translateElement)
		{
			char *valString=NULL;
			float x,y,z;

			valString=(char *) translateElement->Attribute("xyz");

			if(valString && sscanf(valString,"%f %f %f",&x, &y, &z)==3)
			{
				printf("  translate values (XYZ): %f %f %f\n", x, y, z);
			}
			else
				printf("Error parsing translate");
		}
		else
			printf("translate not found\n");		

		// repeat for each of the variables as needed
	}

	// Other blocks could be validated/processed here


	// graph section
	if (graphElement == NULL)
		printf("Graph block not found!\n");
	else
	{
		char *prefix="  -";
		TiXmlElement *node=graphElement->FirstChildElement();

		while (node)
		{
			printf("Node id '%s' - Descendants:\n",node->Attribute("id"));
			TiXmlElement *child=node->FirstChildElement();
			while (child)
			{
				if (strcmp(child->Value(),"Node")==0)
				{
					// access node data by searching for its id in the nodes section
					
					TiXmlElement *noderef=findChildByAttribute(nodesElement,"id",child->Attribute("id"));

					if (noderef)
					{
						// print id
						printf("  - Node id: '%s'\n", child->Attribute("id"));

						// prints some of the data
						printf("    - Material id: '%s' \n", noderef->FirstChildElement("material")->Attribute("id"));
						printf("    - Texture id: '%s' \n", noderef->FirstChildElement("texture")->Attribute("id"));

						// repeat for other leaf details
					}
					else
						printf("  - Node id: '%s': NOT FOUND IN THE NODES SECTION\n", child->Attribute("id"));

				}
				if (strcmp(child->Value(),"Leaf")==0)
				{
					// access leaf data by searching for its id in the leaves section
					TiXmlElement *leaf=findChildByAttribute(leavesElement,"id",child->Attribute("id"));

					if (leaf)
					{
						// it is a leaf and it is present in the leaves section
						printf("  - Leaf id: '%s' ; type: '%s'\n", child->Attribute("id"), leaf->Attribute("type"));

						// repeat for other leaf details
					}
					else
						printf("  - Leaf id: '%s' - NOT FOUND IN THE LEAVES SECTION\n",child->Attribute("id"));
				}

				child=child->NextSiblingElement();
			}
			node=node->NextSiblingElement();
		}
	}
	*/

		if (failed)
		{
			std::cout << "\nPlease check your ANF file for the errors listed above\n";
			system("pause");
			exit(1);
		}
}

ANFScene::~ANFScene()
{
	delete(doc);
}

//-------------------------------------------------------

TiXmlElement *ANFScene::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
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


