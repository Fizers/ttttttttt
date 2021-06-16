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
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_treeView_doubleClicked(const QModelIndex &index);
    void comboBoxChanged(int Type);
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QFileSystemModel *path;
    Type type;
    Browser *b;
    IBrowser *btype;
    QList<AllInf> inf;
    std::shared_ptr<Model> fmodel;

};
#endif // WIDGET_H
