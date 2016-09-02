#ifndef GUIOBSERVER_H_INCLUDED
#define GUIOBSERVER_H_INCLUDED
class ModelSubject;

class GUIObserver {
public:
    virtual void UpdateModel() = 0;
    virtual void UpdateUI() = 0;
protected:
    Observer(){};
};


#endif // GUIOBSERVER_H_INCLUDED
