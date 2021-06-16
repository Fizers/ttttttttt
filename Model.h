#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QDebug>
#include "ModelInform.h"

class Model : public QAbstractTableModel
{
    Q_OBJECT

private:
    QList<AllInf> information;
    enum class ColumName
    {
        NAME = 0,
        SIZE,
        PERCENT
    };

public:
    Model() = default;
    ~Model() = default;
    explicit Model(const QList<AllInf>& inform, QObject* parent = nullptr);
    void setModel(const QList<AllInf>& inform);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

};

#endif // MODEL_H
