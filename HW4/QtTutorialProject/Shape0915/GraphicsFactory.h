#ifndef GRAPHICSFACTORY_H_INCLUDED
#define GRAPHICSFACTORY_H_INCLUDED

#include "Graphics.h"
#include <stack>
#include <string>
#include <utility>

using namespace std;

class GraphicsFactory {
public:
    Graphics * buildGraphicsFromFile(const char * fileName); /*implement the pseudo code */
    string fileContentsAsString(const char * fileName); /* implement line 1 of pseudo code */
    Graphics * extractGraphicsFromOneLine(string & contents, int & level); /*implement line 3 */
    void compose (); /* implement lines 5, 6 as well as line 8 */
public:
    stack<pair<int, Graphics *>> pda;
};


#endif // GRAPHICSFACTORY_H_INCLUDED
