#include "Viewrs.h"

TableViewr::TableViewr(QLayout* l)
{
    tablemodel = new Model();
    tableview = new QTableView();
    tableview->setModel(tablemodel);
    l->addWidget(tableview);
}

TableViewr::~TableViewr()
{
    delete tablemodel;
    delete tableview;
}

void TableViewr::UpdateBrowser(QList<AllInf>& inform) const
{
    tablemodel->setModel(inform);
}



PieViewr::PieViewr(QLayout *l) : Charts(l) {}
QAbstractSeries *PieViewr::AddInf(const QList<AllInf>& inform) const
{
    QPieSeries* s = new QPieSeries();
    s->setPieSize(1);
    for (auto y : inform)
    {
        s->append(y.path_ + " (" + y.percent_.toHtmlEscaped() + ")", y.ratio_);
    }
    return s;
}



BarViewr::BarViewr(QLayout *l) : Charts(l) {}
QAbstractSeries *BarViewr::AddInf(const QList<AllInf>& inform) const
{
    QBarSeries* s = new QBarSeries();
    s->setBarWidth(1);
    for (auto y :inform)
    {
        QBarSet* set = new QBarSet(y.path_ + " (" + y.percent_.toHtmlEscaped() + ")");
        set->append(y.ratio_);
        s->append(set);
    }
    return s;
}


