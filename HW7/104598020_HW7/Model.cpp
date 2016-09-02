/*
 * Model.cpp
 *
 *  Created on: 2009/11/29
 *      Author: zwshen
 */

#include "Model.h"
#include <cstdlib>

using namespace std;

Model::Model() {
}

Model::~Model() {
	for (int i = 0; i < m_graphics.size(); i++)
		delete m_graphics[i];
}


void Model::addGraphics(Graphics * g) {
	m_graphics.push_back(g);
}

void Model::deleteLastGraphics(){
	m_graphics.pop_back();
}

string Model::toString() {
	string s("File: ");
	DescriptionVisitor dv;
	for(auto g : m_graphics)
        g->accept(dv);
    s += dv.getDescription().c_str();
	return s;
}
