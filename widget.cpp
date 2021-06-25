#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QFileInfo>
#include "GroupFolder.h"
#include "GroupType.h"
#include "Viewrs.h"
#include "BrowserModel.h"

Widget::Widget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Widget),
    FolderGrouping(new GroupFolder()),
    TypesGrouping(new GroupType()),
    groupingStrategy(FolderGrouping)
{
    ui->setupUi(this);
    path = new QFileSystemModel(this);
    path->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir:: Hidden);
    path->setRootPath("");

    type=Type::GroupByFolder;
    typeview=TypeViewrs::tablevie;

    table = new TableViewr(ui->stackedWidget->layout());
    pie = new PieViewr(ui->stackedWidget->layout());
    bar = new BarViewr(ui->stackedWidget->layout());
    ModelView = table;
    groupingStrategy->Attach(ModelView);

    ui->treeView->setModel(path);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(ui->treeView, SIGNAL(doubleClicked(QModelIndex)),this,
            SLOT(on_treeView_doubleClicked(QModelIndex)));

    connect(ui->comboBox,QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Widget::comboBoxChanged);
    connect(ui->erte,QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Widget::comboBoxChanged2);

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
     case GroupByFolder:
     groupingStrategy= FolderGrouping;
     break;

     case GroupByType:
     groupingStrategy= TypesGrouping;
     break;

     default:
       groupingStrategy= FolderGrouping;
       break;
   }

   groupingStrategy->Attach(ModelView);
   groupingStrategy->browser(dir);
   switch (typeview)
   {
     case tablevie:
     ModelView = table;
     break;

     case pievie:
     ModelView = pie;
     break;

     case barvie:
     ModelView = bar;
     break;

     default:
       ModelView = table;
       break;
   }
   groupingStrategy->Attach(ModelView);
   groupingStrategy->browser(dir);
   ui->stackedWidget->setCurrentIndex(typeview);
}








Widget::~Widget()
{
    delete ui;
    delete path;

    delete table;
    delete pie;
    delete bar;

    delete FolderGrouping;
    delete TypesGrouping;
}


void Widget::comboBoxChanged( int Type)
{
    switch (Type)
    {
    case GroupByFolder:
        type=Type::GroupByFolder;
        break;
    case GroupByType:
        type=Type::GroupByType;
        break;
    default:
        type=Type::GroupByFolder;
        break;
    }

}

void Widget::comboBoxChanged2( int TypeViewrs)
{
    switch (TypeViewrs)
    {
    case tablevie:
        typeview=TypeViewrs::tablevie;
        break;
    case pievie:
        typeview=TypeViewrs::pievie;
        break;
    case barvie:
        typeview=TypeViewrs::barvie;
        break;
    default:
        typeview=TypeViewrs::tablevie;
        break;
    }
}
