#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QStandardItemModel>
QT_BEGIN_NAMESPACE
namespace Ui
{
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QFileSystemModel *path;
    QStandardItemModel *table;

};
#endif // WIDGET_H
