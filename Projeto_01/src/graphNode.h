#pragma once

#include "tinyxml.h"
#include <vector>
#include <string>

#include "Primitive.h"
#include "Transformation.h"
#include "Appearence.h"

class graphNode
{
private:
	TiXmlElement * element;
	std::string id;
	std::vector <Primitive *> primitives;
	std::vector <graphNode *> descendants;
	std::vector <Transformation *> transformations;
	std::vector <std::string> descendantsID;
	Appearence * appearence;
	bool visited;
	int displayList;
	vector<std::pair<graphNode *, int> > dListVec; //string is the parentID and int is the displayList compiled with parentID appearance

public:
	graphNode();
	
	bool setElement (TiXmlElement * ele);
	TiXmlElement * getElement () { return element; }

	void setID (std::string id);
	std::string getID () { return id; }

	void addPrimitive ( Primitive * primitive) { primitives.push_back (primitive); }
	void addDescendantID ( std::string descendantID) { descendantsID.push_back (descendantID); }
	void addDescendant ( graphNode * desc) { descendants.push_back(desc);}
	void addTransformation ( Transformation * transformation) { transformations.push_back (transformation); }
	void setAppearence (Appearence * app) { appearence = app; }

	std::vector<std::string> getDescendantsID () { return descendantsID; }
	std::vector <graphNode *> getDescendants () { return descendants; }
	std::vector <Primitive *> getPrimitives () { return primitives; }
	Appearence * getAppearence () { return appearence; }

	void setVisited (bool v) { visited = v; }
	bool getVisited () { return visited; }

	vector<pair<graphNode *, int> > getDListVec() {return dListVec;}

	void applyMaterial () { appearence->apply(); }
	void applyTransforms ();
	void draw (float s, float t);

	int displayListValue() { return displayList;}
	void setDisplayList(int a) { displayList = a; }
	void startDisplayList();
	void message(graphNode * parent);
	void removePair(int a) {dListVec.erase(dListVec.begin() + a);}
	void insertPair(pair<graphNode *, int> tmp) {dListVec.push_back(tmp);}

	float matrix [16];

	~graphNode(void);
};

