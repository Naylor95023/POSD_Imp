#include "gui.moc"

gui::gui()
{
//    ctor
    CreateView();
    CreateFileActions();
    CreateAboutActions();
    CreateFileMenus();
    CreateAboutMenus();
    CreateToolBar();
    SetActionConnection();
    QString title = "Hello ,This is my first Qt Project,Many Thanks ~";
    setWindowTitle(title);
    setMinimumSize(800, 600);
}

gui::~gui()
{
    delete widget;
    delete scene;
    //dtor
}

void gui::CreateView(){
    widget = new QWidget();//繪製painter item的物件
    setCentralWidget(widget);

    graphicsView = new QGraphicsView(widget);//要調整生成的位置
    QString gView = "graphicView";
    graphicsView->setObjectName(gView);

    toolBar = new QToolBar(widget);
    QString barName = "ToolBar";
    toolBar->setObjectName(barName);

    scene = new QGraphicsScene();//管理painter item的物件
    graphicsView->setScene(scene);

    QVBoxLayout *layout = new QVBoxLayout;//呈現畫面
    layout->setMargin(0);
    layout->addWidget(graphicsView);
    widget->setLayout(layout);
}

void gui::SetActionConnection() {
    connect(aboutDeveloper, &QAction::triggered, this,
            [this]{(MessageDialog("Drawer",
                               "StudentId : 104598020\nName : Naylor"));});
    connect(fileLoad, SIGNAL(triggered()), this, SLOT(LoadFileDialog()));
    connect(fileSave, SIGNAL(triggered()), this, SLOT(SaveFileDialog()));
}

void gui::CreateAboutActions() {
    aboutDeveloper = new QAction("aboutDeveloper", widget);
}
void gui::CreateFileActions() {
    fileLoad = new QAction(QIcon("Ironman.ico"),"loadFile", widget);
    fileSave = new QAction(QIcon("Batman.ico"),"saveFile", widget);
}

void gui::CreateAboutMenus() {
     about = menuBar()->addMenu("About");
     about->addAction(aboutDeveloper);
}

void gui::CreateFileMenus() {
     file = menuBar()->addMenu("File");
     file -> addAction(fileLoad);
     file -> addAction(fileSave);
}

void gui::CreateToolBar() {
    toolBar -> addAction(fileLoad);
    toolBar -> addAction(fileSave);
}

void gui::Display() {
    drawVistor drawv(widget, scene);
    g->accept(drawv);
    drawv.setScene();
    scene->update();
}

void gui::MessageDialog(QString title, QString mesg) {
   /* QMessageBox msgbox;
    std::string message("104598020\n");
    message += std::string("author:Naylor\n");
    QString qstr = QString::fromStdString(message);
    msgbox.setText(qstr);
    msgbox.exec();*/
    QMessageBox::information(NULL, title, mesg);
}

void gui::LoadFileDialog() {
    QFileDialog open;
    GraphicsFactory gf;
    std::string s ="";
    s = open.getOpenFileName().toStdString();
    try{
        if(s != ""){
            g = gf.buildGraphicsFromFile(s.c_str());
            Display();
        }else{
            MessageDialog("Something Wrong...", "There's nothing to build");
        }
    }catch(exception& ex){
        //cout << ex << endl;
    }
}

void gui::SaveFileDialog() {
    QFileDialog open;
    FILE * file;
    DescriptionVisitor dv;
    std::string s ="";
    s = open.getSaveFileName().toStdString() + ".txt";

    try{
        if(s != "" && g != 0){
            file = fopen(s.c_str(), "w");
            g ->accept(dv);
            fprintf(file, "%s", dv.getDescription().c_str());
            fclose(file);
        }
        else{
            MessageDialog("There is some fail...", "Nothing to be created!");
        }
    }catch(exception& ex){
       // cout << ex << endl;
    }
}





