#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QStandardItemModel>
#include <Browser.h>
#include "ModelInform.h"
#include "Model.h"
#include "Viewrs.h"
#include "BrowserModel.h"

namespace Ui
{
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    enum Type
    {
       GroupByFolder,
       GroupByType
    };
    enum TypeViewrs
    {
       tablevie,
       pievie,
       barvie,
    };
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_treeView_doubleClicked(const QModelIndex &index);
    void comboBoxChanged(int Type);
    void comboBoxChanged2(int TypeViewrs);
    void on_pushButton_clicked();


private:
    Ui::Widget *ui;
    QFileSystemModel *path;
    Type type;
    TypeViewrs typeview;
    IBrowser* FolderGrouping;
    IBrowser* TypesGrouping;
    IBrowser* groupingStrategy;
    QList<AllInf> inf;
    BrowserModel* ModelView;
    BrowserModel* table;
    BrowserModel* pie;
    BrowserModel* bar;
    std::shared_ptr<Model> fmodel;

};


#endif // WIDGET_H
