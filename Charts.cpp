#include "Charts.h"

Charts::~Charts()
{
    delete ChartModel;
}

Charts::Charts(QLayout *l)
{
    ChartModel = new QChart();
    ChartView = new QChartView();
    ChartView->setChart(ChartModel);
    AddLayout(l);
}

void Charts::setChart( QList<AllInf>& inform) const
{
    qint64 AllSize = 0;
    for (auto x : inform)
    {
        AllSize += x.size_.toLongLong();
    }

    ChartModel->setTitle("");

    if (AllSize == 0 || inform.isEmpty())
    {
        ChartModel->setTitle("Luke im not your papka again");
        ChartModel->removeAllSeries();
        return;
    }

    if (inform.size() > 3)
    {
        qint64 others_size = 0;
        auto s = inform.begin() + 2;
        while (s != inform.end())
        {
            others_size += s->size_.toLongLong();
            s = inform.erase(s);
        }
        double percent = double(others_size * 100) / AllSize;
        inform.push_back(AllInf("Others", QString::number(others_size), QString::number(percent, 'f', 2).append(" %"), (qreal)others_size / AllSize));
    }

    SetInf(inform);
}


void Charts::AddLayout(QLayout *l)
{
    l->addWidget(ChartView);
}

void Charts::UpdateBrowser( QList<AllInf> inf) const
{
    setChart(inf);
}


void Charts::SetInf( QList<AllInf>& inform) const
{
    RemoveSeries(ChartModel);
    QAbstractSeries* s = AddInf(inform);
    AddSeries(s);
}


void Charts::RemoveSeries(QChart *c) const
{
    c->removeAllSeries();
}

void Charts::AddSeries(QAbstractSeries *s) const
{
    ChartModel->addSeries(s);
}






