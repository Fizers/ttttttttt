#ifndef MODELINFORM_H
#define MODELINFORM_H
#include <QString>

struct AllInf
{
    QString path_;
    QString size_;
    QString percent_;
    qreal ratio_;
    AllInf(const QString path,const QString size, const QString percent, qreal ratio)
        :path_(path),size_(size),percent_(percent), ratio_(ratio)
    {}
};



#endif // MODELINFORM_H
