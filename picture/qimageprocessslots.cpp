#include "QImageProcess.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>
#include <QBuffer>
#include <QByteArray>
#include <QApplication>
#include <QPixmap>
#include <QSize>
#include <QImage>
#include <QPixmap>
#include <QColor>
#include <cmath>

void QImageProcess::actionOpen() {
       QString fileName = QFileDialog::getOpenFileName(this, "Open File", "/Users/wrf/Desktop/", "ALL(*);;Images (*.png *.bmp *.jpg)");
       if (!fileName.isEmpty()) {
            QImage image1(fileName);
            image = image1;
            if (image1.isNull()) {
                QMessageBox::information(this, tr("Image Viewer"),
                                         tr("Cannot load %1.").arg(fileName));
                return;
            }
            display1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            display1->setPixmap(QPixmap::fromImage(image));
            display1->setScaledContents(true);
       }
    return;
}

void QImageProcess::actionSave() {
    QFileDialog *saveDlg = new QFileDialog(this);
        saveDlg->setAttribute(Qt::WA_DeleteOnClose);
        QString fileSaveName = QFileDialog::getSaveFileName(this, "Save Image", "/", "Images (*.png *.bmp*.jpg)");
        if(fileSaveName == NULL) {
            QMessageBox msgBox;
            msgBox.setText("The document has been modified.");
            msgBox.exec();
        } else {
            QPixmap::fromImage(image2).save(fileSaveName);
        }
    return;
}

void QImageProcess::actionSaveAs() {

    return ;
}


void QImageProcess::actionExit() {
    this->close();
    return;
}

void QImageProcess::actionSetOld() {
    QPixmap pix = QPixmap::fromImage(image);
    display2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    display2->setPixmap(pix);
    display2->setScaledContents(true);
    return;
}

void QImageProcess::actionSetSobel() {
    Pointer imagetemp = setSobel(&image);
    image2 = *(imagetemp.getImage());
    display2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    display2->setPixmap(QPixmap::fromImage(image2));
    display2->setScaledContents(true);
    return;
}

void QImageProcess::actionSetGray() {
    Pointer imagetemp = setGray(&image);
    image2 =  *(imagetemp.getImage());
    display2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    display2->setPixmap(QPixmap::fromImage(image2));
    display2->setScaledContents(true);
    return ;
}

Pointer QImageProcess::setGray(QImage* oldpic) {
    Pointer newPic = new QImage(oldpic->width(), oldpic->height(), QImage::Format_ARGB32);
    for(int i = 1; i < newPic->width(); ++i) {
        for(int j = 1; j < newPic->height(); ++j) {
            QColor oldColor(oldpic->pixel(i, j));
            int average = (oldColor.red() + oldColor.green() + oldColor.blue()) / 3;
            newPic->setPixel(i, j, qRgb(average,average,average));
        }
    }
    return newPic;
}

Pointer QImageProcess::setSobel(QImage* oldpic) {
    Pointer newPicx = new QImage(oldpic->width(), oldpic->height(), QImage::Format_RGB32);
    Pointer newPicy = new QImage(oldpic->width(), oldpic->height(), QImage::Format_RGB32);
    Pointer newPic = new QImage(oldpic->width(), oldpic->height(), QImage::Format_RGB32);
    Pointer newGrayPic = new QImage(oldpic->width(), oldpic->height(), QImage::Format_RGB32);
    // to gray
    for(int i = 0; i < newPic->width(); ++i) {
        for(int j = 0; j < newPic->height(); ++j) {
            QColor oldColor(oldpic->pixel(i, j));
            int average = (oldColor.red() + oldColor.green() + oldColor.blue()) / 3;
            newGrayPic->setPixel(i, j, qRgb(average,average,average));
        }
    }
    // sobel
    for(int i = 1; i < oldpic->width() - 1; ++i) {
       for(int j = 1; j < oldpic->height() - 1; ++j) {
            int rx, gx, bx, ry, gy, by;
            QColor newPicxColor1(newGrayPic->pixel(i - 1, j + 1));
            QColor newPicxColor2(newGrayPic->pixel(i, j + 1));
            QColor newPicxColor3(newGrayPic->pixel(i + 1, j + 1));
            QColor newPicxColor7(newGrayPic->pixel(i - 1, j - 1));
            QColor newPicxColor8(newGrayPic->pixel(i, j - 1));
            QColor newPicxColor9(newGrayPic->pixel(i + 1, j - 1));

            QColor newPicyColor1(newGrayPic->pixel(i - 1, j + 1));
            QColor newPicyColor3(newGrayPic->pixel(i + 1, j + 1));
            QColor newPicyColor4(newGrayPic->pixel(i - 1, j));
            QColor newPicyColor6(newGrayPic->pixel(i + 1, j));
            QColor newPicyColor7(newGrayPic->pixel(i - 1, j - 1));
            QColor newPicyColor9(newGrayPic->pixel(i + 1, j - 1));
            //x dir grad
            int rx1 = newPicxColor1.red();
            int gx1 = newPicxColor1.green();
            int bx1 = newPicxColor1.blue();

            int rx2 = newPicxColor2.red();
            int gx2 = newPicxColor2.green();
            int bx2 = newPicxColor2.blue();

            int rx3 = newPicxColor3.red();
            int gx3 = newPicxColor3.green();
            int bx3 = newPicxColor3.blue();

            int rx7 = newPicxColor7.red();
            int gx7 = newPicxColor7.green();
            int bx7 = newPicxColor7.blue();

            int rx8 = newPicxColor8.red();
            int gx8 = newPicxColor8.green();
            int bx8 = newPicxColor8.blue();

            int rx9 = newPicxColor9.red();
            int gx9 = newPicxColor9.green();
            int bx9 = newPicxColor9.blue();
            //y dir grad
            int ry1 = newPicyColor1.red();
            int gy1 = newPicyColor1.green();
            int by1 = newPicyColor1.blue();

            int ry3 = newPicyColor3.red();
            int gy3 = newPicyColor3.green();
            int by3 = newPicyColor3.blue();

            int ry4 = newPicyColor4.red();
            int gy4 = newPicyColor4.green();
            int by4 = newPicyColor4.blue();

            int ry6 = newPicyColor6.red();
            int gy6 = newPicyColor6.green();
            int by6 = newPicyColor6.blue();

            int ry7 = newPicyColor7.red();
            int gy7 = newPicyColor7.green();
            int by7 = newPicyColor7.blue();

            int ry9 = newPicyColor9.red();
            int gy9 = newPicyColor9.green();
            int by9 = newPicyColor9.blue();

            rx = (-1) * rx1 + (-1) * rx2 + (-1) * rx3 + rx7 + rx8 + rx9;
            gx = (-1) * gx1 + (-1) * gx2 + (-1) * gx3 + gx7 + gx8 + gx9;
            bx = (-1) * bx1 + (-1) * bx2 + (-1) * bx3 + bx7 + bx8 + bx9;

            rx = qBound(0, rx, 255);
            gx = qBound(0, gx, 255);
            bx = qBound(0, bx, 255);

            newPicx->setPixel(i, j, qRgb(rx, gx, bx));

            ry = (-1) * ry1 + ry3 + (-1) * ry4 + ry6 + (-1) * ry7 + ry9;
            gy = (-1) * gy1 + gy3 + (-1) * gy4 + gy6 + (-1) * gy7 + gy9;
            by = (-1) * by1 + by3 + (-1) * by4 + by6 + (-1) * by7 + by9;

            ry = qBound(0, ry, 255);
            gy = qBound(0, gy, 255);
            by = qBound(0, by, 255);

            newPicy->setPixel(i, j, qRgb(ry, gy, by));
       }
    }

    for(int i = 1; i < oldpic->width(); ++i) {
        for(int j = 1; j < oldpic->height(); ++j) {
            QColor newxColor(newPicx->pixel(i, j));
            QColor newyColor(newPicy->pixel(i, j));
            int rx = newxColor.red();
            int gx = newxColor.green();
            int bx = newxColor.blue();

            int ry = newyColor.red();
            int gy = newyColor.green();
            int by = newyColor.blue();

            int r = (sqrt(rx * rx + ry * ry) >= 50 ) ? 255 : 0;
            int g = (sqrt(gx * gx + gy * gy) >= 50 ) ? 255 : 0;
            int b = (sqrt(bx * bx + by * by) >= 50 ) ? 255 : 0;

            newPic->setPixel(i, j, qRgb(r, g, b));
        }
    }
    return newPic;
}

Pointer QImageProcess::setUp(QImage* oldpic) {
    Pointer newPic = new QImage(oldpic->width(), oldpic->height(), QImage::Format_ARGB32);
    for(int i = 1; i < oldpic->width(); i = i + 2) {
        for(int j = 1; j < oldpic->height(); j = j + 2) {
            QColor newColor(oldpic->pixel(i, j));
            newPic->setPixel(i / 2, j / 2, qRgb(newColor.red(), newColor.green(), newColor.blue()));
        }
    }
    return newPic;
}

void QImageProcess::actionSetDown() {
    Pointer imagetemp = setUp(&image);
    image2 = *(imagetemp.getImage());
    display2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    display2->setPixmap(QPixmap::fromImage(image2));
    display2->setScaledContents(true);
    return ;
}

Pointer QImageProcess::setY(QImage* oldpic) {
    Pointer newPic = new QImage(oldpic->width(), oldpic->height(), QImage::Format_ARGB32);
    for(int i = 1; i < oldpic->width(); ++i) {
        for(int j = 1; j < oldpic->height(); ++j) {
              QColor newColor(oldpic->pixel(i, j));
              int r = newColor.red();
              int g = newColor.green();
              int b = newColor.blue();
              newPic->setPixel(i, oldpic->height() - j, qRgb(r, g, b));
        }
    }
    return newPic;
}

void QImageProcess::actionSetY() {
    Pointer imagetemp = setY(&image);
    image2 = *(imagetemp.getImage());
    display2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    display2->setPixmap(QPixmap::fromImage(image2));
    display2->setScaledContents(true);
    return;
}

void QImageProcess::actionSetX() {
    Pointer imagetemp = setX(&image);
    image2 = *(imagetemp.getImage());
    display2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    display2->setPixmap(QPixmap::fromImage(image2));
    display2->setScaledContents(true);
    return;
}

Pointer QImageProcess::setX(QImage* oldpic) {
    Pointer newPic = new QImage(oldpic->width(), oldpic->height(), QImage::Format_ARGB32);
    for(int i = 1; i < oldpic->width(); ++i) {
        for(int j = 1; j < oldpic->height(); ++j) {
              QColor newColor(oldpic->pixel(i, j));
              int r = newColor.red();
              int g = newColor.green();
              int b = newColor.blue();
              newPic->setPixel(oldpic->width() - i,  j, qRgb(r, g, b));
        }
    }
    return newPic;
}

Pointer QImageProcess::eraseIamge(QImage* oldpic) {
    Pointer newPic = new QImage(oldpic->width(), oldpic->height(), QImage::Format_ARGB32);
    for(int i = 0; i < oldpic->width(); ++i) {
        for(int j = 0; j < oldpic->height(); ++j) {

            QColor newColor(oldpic->pixel(i, j));
            int r = erase(newColor.red());
            int g = erase(newColor.green());
            int b = erase(newColor.blue());
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);
            newPic->setPixel(i, j, qRgb(r, g, b));
        }
    }
    return newPic;
}

int QImageProcess::erase(int n) {
    return  2*n + 10;
}

void QImageProcess::actionErase() {
    Pointer imagetemp = eraseIamge(&image);
    image2 = *(imagetemp.getImage());
    display2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    display2->setPixmap(QPixmap::fromImage(image2));
    display2->setScaledContents(true);
    return;
}







