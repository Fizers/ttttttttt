#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QFileInfo>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    path = new QFileSystemModel(this);
    path->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir:: Hidden);
    path->setRootPath("");
    ui->treeView->setModel(path);
    connect(ui->treeView, SIGNAL(doubleClicked(QModelIndex)),this,
            SLOT(on_treeView_doubleClicked(QModelIndex)));

    table = new QStandardItemModel( 5,3,this );
    ui->tableView->setModel(table);
    QModelIndex inde;
    for(int row=0; row< table->rowCount();++row)
    {
        for(int col=0; col< table->columnCount();++col)
        {
            inde = table->index(row, col);
            table->setData(inde,0);
        }
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_treeView_doubleClicked(const QModelIndex &index)
{
    ui->textEdit->clear();
    QTreeView* treeView = (QTreeView*)sender();
    QFileInfo mydir = path->fileInfo(index);
    auto pp = mydir.absoluteFilePath();
    ui->textEdit->insertPlainText(pp);
}

void Widget::on_pushButton_clicked()
{

}
