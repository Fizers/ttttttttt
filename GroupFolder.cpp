#include "GroupFolder.h"
#include "Size.h"



qint64 getDirSize(const QString& path)
{
    qint64 AllSize = 0;
    QDir myDir(path);
    for (const auto& s : myDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot , QDir::Name | QDir::Type))
        AllSize += s.size();
    return AllSize;
}

QMap<QString, qint64> GroupFolder::getFolderSize(const QString& path) const
{
    QFileInfo folder(path);

    QMap<QString, qint64> FolderList;

    auto thisDirPath = folder.absoluteFilePath();
    FolderList.insert(thisDirPath, getDirSize(thisDirPath));

    for (auto& x : QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden, QDir::Name | QDir::Type))
    {
        auto TotalPath = x.absoluteFilePath();
        FolderList.insert(TotalPath, Total::getAllSize(TotalPath));
    }
    return FolderList;
}


QMap<QString, double> GroupFolder::getPercentFolder(qint64& AllSize, QMap<QString, qint64>& FolderList) const
{
    QMap<QString, double> FolderListPercent;
    double percent;
    for (auto s = FolderList.begin(); s != FolderList.end(); ++s)
    { if (s.value() == 0)
         percent = 0;
      else
        { percent= double(s.value() * 100) / AllSize;
        if (percent < 0.01)
            percent = -percent;
        }
        FolderListPercent.insert(s.key(), percent);
    }
    return FolderListPercent;
}

QList<QPair<double, QString>> sortPercent(const QMap<QString, double>& FolderPercent)
{
    QList<QPair<double, QString>> sortList;
    for (auto x : FolderPercent.keys())
    {
      sortList.append(QPair<double, QString>(FolderPercent[x], x));
    }

    std::sort(sortList.begin() + 1, sortList.end(), std::greater<QPair<double, QString>>());
    return sortList;
}

QList<AllInf> GroupFolder::FormInf(const QMap<QString, qint64> &FolderType, const QList<QPair<double, QString>>& FolderPercent) const
{
    QList<AllInf> inform;
    auto AllSize = Total::GiveSize(FolderType);
    for (auto& x : FolderPercent)
    {
        if (x.first < 0)
        {
            inform.push_back(AllInf(x.second, QString::number(FolderType.value(x.second)), QString("< 0.01 %"), (qreal)FolderType.value(x.second)/ AllSize));
        }
        else
        {
            inform.push_back(AllInf(x.second, QString::number(FolderType.value(x.second)), QString::number(x.first, 'f', 2).append(" %"),(qreal)FolderType.value(x.second)/ AllSize));
        }
    }
    return inform;
}

void GroupFolder::browser(const QString& path)
{
    QTextStream cout(stdout);
    QFileInfo folder(path);
    if (!folder.exists() && !folder.isReadable())
    {
        cout << "Error!Luke I'm not your papka(" << "\n";
        exit(-1);
    }
    auto FolderList = getFolderSize(path);
    auto AllSize = Total::GiveSize(FolderList);
    auto FolderPercent = getPercentFolder(AllSize, FolderList);
    auto sortFolderPercent = sortPercent(FolderPercent);
    auto inform=FormInf(FolderList,sortFolderPercent);
    OnFinish( QList<AllInf> (inform));;

    //PrintFolderAllInf(FolderList, sortFolderPercent);
}




//void GroupFolder::PrintFolderAllInf(const QMap<QString, qint64>& FolderType, const QList<QPair<double, QString> >& FolderPercent) const
//{QTextStream cout(stdout);
//    for (auto x : FolderPercent)
//    {
//            cout << qSetFieldWidth(28) << Qt::left << x.second << qSetFieldWidth(10)  << FolderType.value(x.second) / 1024.0
//                      << qSetFieldWidth(10)<< " KB";
//            if (x.first < 0 || x.first == 0) {
//               cout << qSetFieldWidth(8) << "< 0.01 %\n";
//            }
//            else
//                cout << qSetFieldWidth(8) << QString::number(x.first, 'f', 2).append(" %") << "\n";
//    }
//}


