#include "QImageProcess.h"
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QDebug>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

QImageProcess::QImageProcess(QWidget *parent)
    : QMainWindow(parent), display1(NULL), image("./")
{
    createUi();
}

QImageProcess::~QImageProcess()
{

}
// 2018-05-9
void QImageProcess::createUi() {
    this->setWindowTitle("Qt Image Process ToolKit");
    this->resize(480, 640);
    createMenuBar();
    createToolBar();
    createCentraWidget();
}

void QImageProcess::createMenuBar() {
    this->menuBar()->setNativeMenuBar(false);
    QMenu *mb = this->menuBar()->addMenu("&File");
    QMenu *mb1 = this->menuBar()->addMenu("&Operate");
    QAction *openAction = new QAction("Open", mb);
    QAction *saveAction = new QAction("Save", mb);
    QAction *saveAsAction = new QAction("Save As", mb);
    QAction *exitAction = new QAction("Exit", mb);
    QAction *zoomUp = new QAction("set Old", mb1);
    QAction *zoomDown = new QAction("Set sobel", mb1);
    QAction *zoomNormalSize = new QAction("set Gray", mb1);
    QAction *actionDown = new QAction("Change", mb1);
    QAction *actionSetY = new QAction("Y", mb1);
    QAction *actionSetX = new QAction("X", mb1);
    QAction *actionErase = new QAction("Erase", mb1);
    mb->addAction(openAction);
    mb->addAction(saveAction);
    mb->addAction(saveAsAction);
    mb->addSeparator();
    mb->addAction(exitAction);
    mb1->addAction(zoomUp);
    mb1->addAction(zoomDown);
    mb1->addAction(zoomNormalSize);
    mb1->addAction(actionDown);
    mb1->addAction(actionSetY);
    mb1->addAction(actionSetX);
    mb1->addAction(actionErase);
    QObject::connect(openAction, SIGNAL(triggered(bool)), this, SLOT(actionOpen()));
    QObject::connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(actionSave()));
    QObject::connect(saveAsAction, SIGNAL(triggered(bool)), this, SLOT(actionSaveAs()));
    QObject::connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(actionExit()));
    QObject::connect(zoomUp, SIGNAL(triggered(bool)), this, SLOT(actionSetOld()));
    QObject::connect(zoomDown, SIGNAL(triggered(bool)), this, SLOT(actionSetSobel()));
    QObject::connect(zoomNormalSize, SIGNAL(triggered(bool)), this, SLOT(actionSetGray()));
    QObject::connect(actionDown, SIGNAL(triggered(bool)), this, SLOT(actionSetDown()));
    QObject::connect(actionSetY, SIGNAL(triggered(bool)), this, SLOT(actionSetY()));
    QObject::connect(actionSetX, SIGNAL(triggered(bool)), this, SLOT(actionSetX()));
    QObject::connect(actionErase, SIGNAL(triggered(bool)), this, SLOT(actionErase()));
    return;
}

void QImageProcess::createToolBar() {
    QToolBar *tb = this->addToolBar("File");
    QAction *openAction = new QAction(QIcon(":/toolicon/ico/open.ico"), "&Open", tb);
    QAction *setAction= new QAction(QIcon(":/toolicon/ico/set.ico"), "&Set", tb);
    QAction *newAction = new QAction(QIcon(":/toolicon/ico/new.ico"), "&New", tb);
    tb->addAction(openAction);
    tb->addAction(setAction);
    tb->addAction(newAction);
    QObject::connect(openAction, SIGNAL(triggered(bool)), this, SLOT(actionOpen()));
    return ;
}

void QImageProcess::createCentraWidget() {
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(centralWidget);
    display1 = new QLabel(this);
    display2 = new QLabel(this);
    display1->setText("原图");
    display2->setText("处理后图");
    layout->addWidget(display1);
    layout->addWidget(display2);
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);
    return;
}
