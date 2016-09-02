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
    UpdateUI();
    //set
    SetActionConnection();
    QString title = "Hello ,This is my first Qt Project,Many Thanks ~";
    setWindowTitle(title);
    setMinimumSize(1200, 600);
    p->SetObserver(this);
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

void gui::UpdateModel() {
    drawVistor drawv(widget, scene, m_presentation);
    for(auto g : m_presentation->m_model->m_graphics){
        g->accept(drawv);
    }
    drawv.setScene();
    scene->update();
}

void gui::UpdateUI(){
    redo->setEnabled(m_presentation->redoEnable());
    undo->setEnabled(m_presentation->undoEnable());
    group->setEnabled(m_presentation->groupEnable());
    separate->setEnabled(m_presentation->separateEnable());
    del->setEnabled(m_presentation->delEnable());
    upLevel->setEnabled(m_presentation->upLevelEnable());
    downLevel->setEnabled(m_presentation->downLevelEnable());
}

void gui::MessageDialog(QString title, QString mesg) {
    QMessageBox::information(NULL, title, mesg);
}

void gui::LoadFileDialog() {
    if(m_presentation->IsModelChanged())SaveWarningMessage();
    QFileDialog open;
    GraphicsFactory gf;
    std::string s ="";
    s = open.getOpenFileName().toStdString();
    try{
        if(s != ""){
            //clear model first, then clear command
            m_presentation->clearAll();
            gf.buildGraphicsFromFile(s.c_str(), m_presentation);
            UpdateModel();
            m_presentation->cleaCommand();
        }else
            MessageDialog("Something Wrong...", "There's nothing to build");
    }catch(exception& ex){}
}

void gui::SaveWarningMessage(){
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
    std::string message("Do want to save ur change!?\n");
    QString qstr = QString::fromStdString(message);
    msgBox.setText(qstr);
    switch (msgBox.exec()) {
        case QMessageBox::Yes:
            SaveFileDialog();
            break;
        case QMessageBox::No:
            break;
        default:
            break;
    }
}

void gui::SaveFileDialog() {
    QFileDialog open;
    FILE * file;
    DescriptionVisitor dv;
    std::string s ="";
    s = open.getSaveFileName().toStdString() + ".txt";
    try{
        if(s != ".txt"){
            file = fopen(s.c_str(), "w");
            for(auto g : m_presentation->m_model->m_graphics)
                g->accept(dv);
            fprintf(file, "%s", dv.getDescription().c_str());
            fclose(file);
            m_presentation->getModelDescription();
        }else
            MessageDialog("There is some fail...", "Nothing to be created!");
    }catch(exception& ex){}
}

void gui::CreateShape(Graphics * s){
    m_presentation->addGraphics(s);
}

void gui::Group(){
    m_presentation->Group();
}

void gui::Separate(){
    m_presentation->Separate();
}

void gui::DeleteGraphics(){
    m_presentation->Delete();
}

void gui::UpLevel(){
    m_presentation->UpLevel();
}

void gui::DownLevel(){
    m_presentation->DownLevel();
}

void gui::Redo(){
    m_presentation->redo();
}

void gui::Undo(){
    m_presentation->undo();
}








