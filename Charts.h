#ifndef CHARTS_H
#define CHARTS_H
#include "Browser.h"
#include "BrowserModel.h"
#include "Model.h"
#include <QWidget>
#include <QtCharts/QChartGlobal>
#include <memory>
#include <QtCharts/QAbstractSeries>
#include <QBarSeries>
#include <QPieSeries>
#include <QBarSet>
#include <QGraphicsLayout>
#include <QChartView>
#include <QLayout>
#include <QChartView>
#include <QHeaderView>
#include <QTableView>

using namespace QtCharts;

class Charts : public BrowserModel
{
private:
    QChartView* ChartView;
    QChart* ChartModel;

public:
    Charts() = default;
    virtual ~Charts();
    Charts(QLayout* l);

    void setChart( QList<AllInf>& inform) const;
    void AddLayout(QLayout* l);
    void UpdateBrowser( QList<AllInf> inf) const;
    void SetInf( QList<AllInf>& inform) const;
    void RemoveSeries(QChart* s) const;
    void AddSeries(QAbstractSeries* s) const;
    virtual QAbstractSeries* AddInf(const QList<AllInf>& inform) const = 0;
};


#endif // CHARTS_H
