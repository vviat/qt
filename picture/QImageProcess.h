#ifndef QIMAGEPROCESS_H
#define QIMAGEPROCESS_H

#include <QMainWindow>
#include <QLabel>
#include <QImage>
#include <iostream>
#include <fstream>
#include "Pointer.h"
using  namespace std;

class QImageProcess : public QMainWindow
{
    Q_OBJECT
private:
    void createUi();
    void createMenuBar();
    void createToolBar();
    void createCentraWidget();
    QLabel *display1; // 显示原图
    QLabel *display2; // 显示处理后的图
    QImage image; // 原图
    QImage image2; // 处理后的图
    Pointer setGray(QImage* oldpic);
    Pointer setSobel(QImage* oldpic);
    Pointer setUp(QImage* oldpic);
    Pointer setY(QImage* oldpic);
    Pointer setX(QImage* oldpic);
    Pointer eraseIamge(QImage* oldpic);
    int erase(int n);

private slots:
    void actionOpen();
    void actionSave();
    void actionSaveAs();
    void actionExit();
    void actionSetOld();
    void actionSetSobel();
    void actionSetGray();
    void actionSetDown();
    void actionSetY();
    void actionSetX();
    void actionErase();
public:
    QImageProcess(QWidget *parent = 0);
    ~QImageProcess();
};

#endif // QIMAGEPROCESS_H
