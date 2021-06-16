#ifndef BROWSER_H
#define BROWSER_H
#include <QDir> //Класс QDir обеспечивает доступ к структурам каталогов и их содержимому
#include <QFileInfo> //QFileInfo предоставляет информацию об имени файла и позиции (пути) в файловой системе, его правах доступа и о том,
                      // является ли он каталогом или символической ссылкой и т.д.
#include <QTextStream>
#include <QDebug>
#include "ModelInform.h"

class IBrowser
{
public:
    virtual QList<AllInf> browser(const QString& path) = 0;
    virtual ~IBrowser() {}
};

class Browser
{
private:
    IBrowser *b;
public:
    Browser ()=default;
    explicit Browser(IBrowser* l) : b(l) {}
    QList<AllInf> browser(const QString& path)
    {
        b->browser(path);
    }
    void setStrategy(IBrowser* strategy)
    {
        if (b)
            delete b;
        b = strategy;
    }
    ~Browser()
    {
        if (b)
            delete b;
    }

};

#endif // BROWSER_H
