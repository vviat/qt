#include "Pointer.h"
#include <QDebug>
Pointer::Pointer() : mp(NULL){

}

Pointer::Pointer(QImage* p) : mp(p){

}

Pointer::Pointer(const Pointer& obj) : mp(obj.mp) {

}

Pointer::~Pointer() {
    qDebug() << "~Pointer()";
    delete mp;
}

Pointer& Pointer::operator = (const Pointer& obj) {
    if(this != &obj) {
        delete mp;
        mp = obj.mp;
        const_cast<Pointer&>(obj).mp = NULL;
    }
    return *this; //连续赋值
}

QImage* Pointer::operator ->() {
    return mp;
}

QImage& Pointer::operator * () {
    return *mp;
}

QImage* Pointer::getImage() const {
    return mp;
}

