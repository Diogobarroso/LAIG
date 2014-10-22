#pragma once

#include "tinyxml.h"
#include <string>
#include <vector>

#include "graphNode.h"

class graphElement
{
private:
	TiXmlElement * element;	
	graphNode * root;
	std::vector <graphNode *> nodes;
	std::string rootID;
public:
	graphElement(void);
	

	bool setElement (TiXmlElement * ele);
	bool setRootID (std::string rID);

	void setRoot () { root = getNode(rootID);}
	void addNode (graphNode * node) {nodes.push_back(node);}
	std::vector <graphNode *> getNodes () { return nodes;}
	graphNode* getNode (std::string id);
	graphNode* getRoot () { return root; }

	TiXmlElement * getElement () { return element; }
	
	~graphElement(void);
};

