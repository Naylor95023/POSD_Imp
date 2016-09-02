#ifndef GUI_H
#define GUI_H
#include <QtWidgets/QMainWindow>
#include <Qt>
#include <QGraphicsView>
#include <QtWidgets/QToolBar>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QString>
#include <QWidget>
#include <QFileDialog>
#include <QSignalMapper>

#include "Painter.h"
#include "GraphicsFactory.h"
#include "DescriptionVisitor.h"
#include "drawVistor.h"

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;


class gui: public QMainWindow
{
    Q_OBJECT
    public:
        gui();
        virtual ~gui();
        QGraphicsView *graphicsView;
        QGraphicsScene *scene;
        QWidget *widget;

        void Display();
        void CreateView();
        void MessageBox(const QString _message);
        void CreateAboutActions();
        void CreateFileActions();
        void CreateAboutMenus();
        void CreateFileMenus();
        void CreateToolBar();
        void SetActionConnection();

    protected:

    private:
        QAction *aboutDeveloper;
        QAction *fileLoad;
        QAction *fileSave;
        QMenu *about;
        QMenu *file;
        QToolBar *toolBar;

        Graphics * g = 0;

    private slots:
        void MessageDialog(QString title, QString mesg);
        void LoadFileDialog();
        void SaveFileDialog();
};

#endif // GUI_H
