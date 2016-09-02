#ifndef GRAPHICSFACTORY_H_INCLUDED
#define GRAPHICSFACTORY_H_INCLUDED

#include "CompositeGraphics.h"
#include "SimpleGraphics.h"
#include "Circle.h"
#include "Square.h"
#include "Rectangle.h"
#include "DescriptionVisitor.h"
#include "Graphics.h"
#include "Presentation.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <typeinfo>


using namespace std;

class GraphicsFactory {
public:
    void buildGraphicsFromFile(const char * fileName, Presentation * m_p); /*implement the pseudo code */
    string fileContentsAsString(const char * fileName); /* implement line 1 of pseudo code */
    Graphics * extractGraphicsFromOneLine(std::string & contents, int & level); /*implement line 3 */
    void compose (); /* implement lines 5, 6 as well as line 9 */
    stack<pair<Graphics * , int >> * getStack() {return &_graphicsStack;}
private:
    stack<pair<Graphics * , int >> _graphicsStack;

};

#endif // GRAPHICSFACTORY_H_INCLUDED
