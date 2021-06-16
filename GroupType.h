#ifndef GROUPTYPE_H
#define GROUPTYPE_H
#include "Browser.h"
#include "ModelInform.h"

class GroupType : public IBrowser
{
public:
    explicit GroupType() = default;
    virtual ~GroupType() = default;
    QList<AllInf> browser(const QString& path);
private:
    void getTypeSize(const QString& path, QMap<QString, qint64>& TypeList);
    QMap<QString, double> getTypePercent(qint64& totalSize, QMap<QString, qint64>& TypeList) const;
    QList<QPair<double, QString>> sortPercent(const QMap<QString, double>& TypePercant);
    void PrintTypeAllInf(const QMap<QString, qint64>& FileTypesList, const QList<QPair<double, QString>> TypePercant) const;
    QList<AllInf> FormInf(const QMap<QString, qint64>& FolderType, const QList<QPair<double, QString> >& FolderPercent);

};

#endif // GROUPTYPE_H
