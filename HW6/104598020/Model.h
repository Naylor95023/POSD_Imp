#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include "Graphics.h"
#include <vector>
using namespace std;

class Model {
public:
	vector<Graphics * > m_graphics;
public:
	Model();
	virtual ~Model();
	void addGraphics(Graphics * g);
	void deleteLastGraphics();
	//string toString();
};


#endif // MODEL_H_INCLUDED
