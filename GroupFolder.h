#ifndef GROUPFOLDER_H
#define GROUPFOLDER_H
#include "Browser.h"
#include "ModelInform.h"

class GroupFolder : public IBrowser
{
public:
    explicit GroupFolder() = default;
    virtual ~GroupFolder() = default;
    QList<AllInf> browser(const QString& path);
private:
    QMap<QString, qint64> getFolderSize(const QString& path) const;
    QMap<QString, double> getPercentFolder(qint64& totalSize, QMap<QString, qint64>& FolderList) const;
    void PrintFolderAllInf(const QMap<QString, qint64>& FolderType, const QList<QPair<double, QString> >& FolderPercent) const;
    QList<AllInf> FormInf(const QMap<QString, qint64>& FolderType, const  QList<QPair<double, QString>> &FolderPercent) const;
};

#endif // GROUPFOLDER_H
