#include "GroupType.h"
#include "Size.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QTextStream>


void GroupType::getTypeSize(const QString& path, QMap<QString, qint64>& TypeList)
{
    QDir myDir(path);
    for (const auto t : myDir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot
                                              | QDir::Hidden, QDir::Name | QDir::Type | QDir::Size))
    {
            if (t.isDir() && !t.isSymLink())
            {
                getTypeSize(t.absoluteFilePath(), TypeList);
            }
            else
            {
                if (TypeList.keys().contains(t.suffix().toLower()))
                {
                    TypeList[t.suffix()] += t.size();
                }
                else
                {
                    TypeList.insert(t.suffix().toLower(), t.size());
                }
            }
    }
}

QMap<QString, double> GroupType::getTypePercent(qint64& AllSize, QMap<QString, qint64>& TypeList) const
{
    QMap<QString, double> TypeListPercent;
    double percent;
    for (auto t = TypeList.begin(); t != TypeList.end(); ++t)
    {
        if (t.value() == 0)
            percent=0;
        else
        { percent = double(t.value() * 100) / AllSize;
        if (percent < 0.01)
            percent = -percent;
        }
        TypeListPercent.insert(t.key(), percent);
    }
    return TypeListPercent;
}

QList<QPair<double, QString>> GroupType::sortPercent(const QMap<QString, double>& TypePercant)
{
    QList<QPair<double, QString>> sortList;
    for (auto x : TypePercant.keys())
    {
      sortList.append(QPair<double, QString>(TypePercant[x], x));
    }
    std::sort(sortList.begin(), sortList.end(), std::greater<QPair<double, QString>>());
    return sortList;
}

void GroupType::PrintTypeAllInf(const QMap<QString, qint64>& TypeList, const QList<QPair<double, QString>> TypePercant) const
{QTextStream cout(stdout);
    if (TypePercant.isEmpty())
    {
        return;
    }
    for (auto x : TypePercant)
    {
        cout << qSetFieldWidth(20) <<   "*." + x.second <<
                    qSetFieldWidth(15) << TypeList.value(x.second) /1024.0 <<
                    qSetFieldWidth(5) << "KB";
                    if (x.first < 0) {
                        cout << qSetFieldWidth(10) << "< 0.01 %\n";
                    } else
                        cout << qSetFieldWidth(10) << QString::number(x.first, 'f', 2).append(" %") << "\n";
    }
    cout.reset();
}

QList<AllInf> GroupType::FormInf(const QMap<QString, qint64> &TypeList, const QList<QPair<double, QString> > &TypePercant)
{
    QList<AllInf> inform;
    for (auto x : TypePercant) {
        if (x.first < 0) {
            inform.push_back(AllInf(x.second, QString::number(TypeList.value(x.second)), QString("< 0.01 %")));
        } else {
        inform.push_back(AllInf("*." + x.second, QString::number(TypeList.value(x.second)), QString::number(x.first, 'f', 2).append(" %")));
        }
    }
    return inform;
}

QList<AllInf> GroupType::browser(const QString& path)
{QTextStream cout(stdout);
    QDir folder(path);
    if (!folder.exists() && !folder.isReadable()) {
        cout << "Error!" << "\n";
        return QList<AllInf> ();
    }
    if (folder.isEmpty())
    {
        cout << "Folder is empty!" << "\n";
        return QList<AllInf> ();
    }
    QMap<QString, qint64> TypeList;
    getTypeSize(path, TypeList);
    auto AllSize = Total::GiveSize(TypeList);
    auto TypePercant = getTypePercent(AllSize, TypeList);
    auto sortTypePercant = sortPercent(TypePercant);
    //PrintTypeAllInf(TypeList, sortTypePercant);
    auto inform=FormInf(TypeList,sortTypePercant);
    return inform;
}

