#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QFileInfo>
#include "GroupFolder.h"
#include "GroupType.h"

Widget::Widget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    path = new QFileSystemModel(this);
    path->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir:: Hidden);
    path->setRootPath("");

    type=Type::GroupByFolder;

    fmodel = std::make_shared<Model>();
    b=new Browser(new GroupFolder);

    ui->treeView->setModel(path);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView->setModel(fmodel.get());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(ui->treeView, SIGNAL(doubleClicked(QModelIndex)),this,
            SLOT(on_treeView_doubleClicked(QModelIndex)));

    connect(ui->comboBox,QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Widget::comboBoxChanged);

    connect(ui->pushButton, SIGNAL(released()),this, SLOT (on_pushButton_clicked()));

}



void Widget::on_treeView_doubleClicked(const QModelIndex &index)
{
    ui->textEdit->clear();
    QFileInfo mydir = path->fileInfo(index);
    auto pp = mydir.absoluteFilePath();
    ui->textEdit->insertPlainText(pp);
}

void Widget::on_pushButton_clicked()
{
   QString dir=ui->textEdit->toPlainText();
   if (dir.isEmpty())
       return;
   switch (type)
   {
     case Type::GroupByFolder:
     b->setStrategy(new GroupFolder);
     break;

     case Type::GroupByType:
     b->setStrategy(new GroupType);
     break;

     default:
       b->setStrategy(new GroupFolder);
       break;
   }
   inf=b->browser(dir);//на след строчке установить данные в модель
   fmodel->setModel(inf);

}


Widget::~Widget()
{
    delete ui;
    delete path;
    delete b;
}

void Widget::comboBoxChanged( int index)
{
    switch (index)
    {
    case 0:
        type=Type::GroupByFolder;
        break;
    case 1:
        type=Type::GroupByType;
        break;
    default:
        type=Type::GroupByFolder;
        break;
    }

}
