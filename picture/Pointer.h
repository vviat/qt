#ifndef _POINTER_H_
#define _POINTER_H_
#include "Pointer.h"
#include <QImage>
class Pointer {
    private :
        QImage* mp;
    public:
        Pointer();
        Pointer(QImage* p);
        Pointer(const Pointer& obj);
        ~Pointer();
        Pointer& operator = (const Pointer& obj);
        QImage* operator ->();
        QImage& operator * ();
        QImage* getImage() const;
};
#endif
