#include "gui.moc"

gui::gui(Presentation * p)
{
    m_presentation = p;
    //ctor
    CreateView();
    CreateFileActions();
    CreateAboutActions();
    CreateAddDelShapActions();
    CreateRedoUndoActions();
    CreateSepGroupActions();
    CreateUpDownLevelActions();
    CreateFileMenus();
    CreateAboutMenus();
    CreateAddMenus();
    CreateToolBar();
    //set
    SetActionConnection();
    QString title = "Hello ,This is my first Qt Project,Many Thanks ~";
    setWindowTitle(title);
    setMinimumSize(1200, 600);
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
    scene->setSceneRect(-250,-250,800,800);
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

    connect(addC, &QAction::triggered, this,
            [this]{CreateShape(new SimpleGraphics(new Circle(0, 0, 50)));});
    connect(addS, &QAction::triggered, this,
            [this]{CreateShape(new SimpleGraphics(new Square(0, 0, 50)));});
    connect(addR, &QAction::triggered, this,
            [this]{CreateShape(new SimpleGraphics(new Rectangle(0, 0, 100, 50)));});
    connect(group, SIGNAL(triggered()), this, SLOT(Group()));
    connect(separate, SIGNAL(triggered()), this, SLOT(Separate()));
    connect(del, SIGNAL(triggered()), this, SLOT(DeleteGraphics()));
    connect(upLevel, SIGNAL(triggered()), this, SLOT(UpLevel()));
    connect(downLevel, SIGNAL(triggered()), this, SLOT(DownLevel()));
    connect(redo, SIGNAL(triggered()), this, SLOT(Redo()));
    connect(undo, SIGNAL(triggered()), this, SLOT(Undo()));

}

// set item icon>>
void gui::CreateAboutActions() {
    aboutDeveloper = new QAction(QIcon("Ironman.ico"),"aboutDeveloper", widget);
}

void gui::CreateFileActions() {
    fileLoad = new QAction(QIcon("open.png"),"loadFile", widget);
    fileSave = new QAction(QIcon("save.png"),"saveFile", widget);
}

void gui::CreateAddDelShapActions() {
    addC = new QAction(QIcon("C.png"),"Create Circle", widget);
    addS = new QAction(QIcon("S.png"),"Create Square", widget);
    addR = new QAction(QIcon("R.png"),"Create Rectangle", widget);
    del = new QAction(QIcon("del.png"),"Delete", widget);
}

void gui::CreateRedoUndoActions() {
    redo = new QAction(QIcon("redo.png"),"Redo", widget);
    undo = new QAction(QIcon("undo.png"),"Undo", widget);
}

void gui::CreateSepGroupActions() {
    group = new QAction(QIcon("comb.png"),"Group", widget);
    separate = new QAction(QIcon("sep.png"),"Separate", widget);
}

void gui::CreateUpDownLevelActions() {
    upLevel = new QAction(QIcon("up.png"),"UpLevel", widget);
    downLevel = new QAction(QIcon("down.png"),"DownLevel", widget);
}

//add item to menu>>
void gui::CreateAboutMenus() {
     about = menuBar()-> addMenu("About");
     about -> addAction(aboutDeveloper);
}

void gui::CreateFileMenus() {
     file = menuBar()-> addMenu("File");
     file -> addAction(fileLoad);
     file -> addAction(fileSave);
}

void gui::CreateAddMenus() {
     addShap = menuBar()->addMenu("Creat Shap");
     addShap -> addAction(addC);
     addShap -> addAction(addS);
     addShap -> addAction(addR);
}

//add item to toolBar>>
void gui::CreateToolBar() {
    toolBar -> setIconSize(QSize(32, 32));
    toolBar -> resize(1000, 64);
    toolBar -> addAction(fileLoad);
    toolBar -> addAction(fileSave);
    toolBar -> addAction(addC);
    toolBar -> addAction(addS);
    toolBar -> addAction(addR);
    toolBar -> addAction(del);
    toolBar -> addAction(group);
    toolBar -> addAction(separate);
    toolBar -> addAction(undo);
    toolBar -> addAction(redo);
    toolBar -> addAction(upLevel);
    toolBar -> addAction(downLevel);
}

//action>>

void gui::DisplayModel() {
    drawVistor drawv(widget, scene, m_presentation);
    for(auto g : m_presentation->m_model->m_graphics){
        g->accept(drawv);
    }
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
            gf.buildGraphicsFromFile(s.c_str(), m_presentation);
            DisplayModel();
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
        if(s != ""){
            file = fopen(s.c_str(), "w");
            for(auto g : m_presentation->m_model->m_graphics)
                g->accept(dv);
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

void gui::CreateShape(Graphics * s){
    m_presentation->addGraphics(s);
    DisplayModel();
}

void gui::Group(){
    m_presentation->Group();
    DisplayModel();
}

void gui::Separate(){
    m_presentation->Separate();
    DisplayModel();
}

void gui::DeleteGraphics(){
    m_presentation->Delete();
    DisplayModel();
}

void gui::UpLevel(){
    m_presentation->UpLevel();
    DisplayModel();
}

void gui::DownLevel(){
    m_presentation->DownLevel();
    DisplayModel();
}

void gui::Redo(){
    m_presentation->redo();
    DisplayModel();
}

void gui::Undo(){
    m_presentation->undo();
    DisplayModel();
}








