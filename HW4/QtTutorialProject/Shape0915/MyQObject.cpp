#include "MyQObject.moc"
#include <iostream>

using namespace std;
MyQObject::MyQObject(QApplication *app):a(app){
    QObject::connect(this, SIGNAL(MyQuit()), a, SLOT(quit()));
}
void MyQObject::MySlot() {
    cout << "MyObject::MySlot called" << endl;
    emit MyQuit();
}
