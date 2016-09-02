#ifndef MYQOBJECT_H_INCLUDED
#define MYQOBJECT_H_INCLUDED

#include <QApplication>
#include <QObject>

class MyQObject : public QObject {
    Q_OBJECT
public:
    MyQObject(QApplication *);
public slots:
    void MySlot();
signals:
    void MyQuit();
private:
    QApplication *a;
};

#endif // MYQOBJECT_H_INCLUDED
