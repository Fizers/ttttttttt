#ifndef VIEWRS_H
#define VIEWRS_H
#include "Charts.h"

class TableViewr : public BrowserModel
{
private:
    Model* tablemodel;
    QTableView* tableview;
public:
    explicit TableViewr(QLayout* l);
    ~TableViewr();

    void UpdateBrowser(  QList<AllInf> inf) const;
};

class PieViewr : public Charts
{
public:
    explicit PieViewr(QLayout* l);
    PieViewr() = default;
    QAbstractSeries* AddInf(const QList<AllInf> &inform) const;
};

class BarViewr : public Charts
{
public:
    explicit BarViewr(QLayout* l);
    BarViewr() = default;
    QAbstractSeries* AddInf(const QList<AllInf>& inform) const;
};



#endif // VIEWRS_H
