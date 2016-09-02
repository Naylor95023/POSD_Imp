#ifndef MODELSUBJECT_H_INCLUDED
#define MODELSUBJECT_H_INCLUDED
#include "GUIObserver.h"

class ModelSubject{
public:
    virtual void SetObserver(GUIObserver * o){_observer = o;}
    virtual void NotifyModel(){}
    virtual void NotifyUI(){}
protected:
    ModelSubject(){};

    GUIObserver* _observer;
};


#endif // MODELSUBJECT_H_INCLUDED
