#ifndef GRAPHICSFACTORY_H_INCLUDED
#define GRAPHICSFACTORY_H_INCLUDED
#include "Graphics.h"
#include <stack>

using namespace std;

class GraphicsFactory {
public:
    Graphics * buildGraphicsFromFile(const char * fileName); /*implement the pseudo code */
    string fileContentsAsString(const char * fileName); /* implement line 1 of pseudo code */
    Graphics * extractGraphicsFromOneLine(std::string & contents, int & level); /*implement line 3 */
    void compose (); /* implement lines 5, 6 as well as line 9 */
    stack<pair<Graphics * , int >> * getStack() {return &_graphicsStack;}
private:
    stack<pair<Graphics * , int >> _graphicsStack;



};

#endif // GRAPHICSFACTORY_H_INCLUDED
