#ifndef GUI_H
#define GUI_H
#include <QtWidgets/QMainWindow>
#include <Qt>
#include <QGraphicsView>
#include <QtWidgets/QToolBar>
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QSize>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QString>
#include <QWidget>
#include <QFileDialog>
#include <QSignalMapper>



#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Painter.h"
#include "GraphicsFactory.h"
#include "DescriptionVisitor.h"
#include "drawVistor.h"
#include "Presentation.h"

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>

using namespace std;


class gui: public QMainWindow
{
    Q_OBJECT
    public:
        gui(Presentation * p);
        virtual ~gui();
        QGraphicsView *graphicsView;
        QGraphicsScene *scene;
        QWidget *widget;

        void DisplayModel();
        void CreateView();
        void MessageBox(const QString _message);

        void CreateAboutActions();
        void CreateFileActions();
        void CreateAddDelShapActions();
        void CreateRedoUndoActions();
        void CreateSepGroupActions();
        void CreateUpDownLevelActions();

        void CreateAboutMenus();
        void CreateFileMenus();
        void CreateAddMenus();

        void CreateToolBar();
        void SetActionConnection();

    protected:

    private:
        Presentation * m_presentation;
        QAction * aboutDeveloper;
        QAction * fileLoad;
        QAction * fileSave;
        QAction * addC;
        QAction * addS;
        QAction * addR;
        QAction * redo;
        QAction * undo;
        QAction * group;
        QAction * separate;
        QAction * del;
        QAction * upLevel;
        QAction * downLevel;

        QMenu *about;
        QMenu *file;
        QMenu *addShap;
        QToolBar *toolBar;

    private slots:
        void MessageDialog(QString title, QString mesg);
        void LoadFileDialog();
        void SaveFileDialog();
        void CreateShape(Graphics * g);
        void DeleteGraphics();
        void Group();
        void Separate();
        void Redo();
        void Undo();
        void UpLevel();
        void DownLevel();
};

#endif // GUI_H
