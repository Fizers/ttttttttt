#ifndef MODELINFORM_H
#define MODELINFORM_H
#include <QString>

struct AllInf
{
    QString path_;
    QString size_;
    QString percent_;
    AllInf(QString path, QString size, QString percent):path_(path),size_(size),percent_(percent)
    {}
};



#endif // MODELINFORM_H
