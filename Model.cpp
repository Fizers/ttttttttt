#include "Model.h"


Model::Model(const QList<AllInf> &inform, QObject *parent) : QAbstractTableModel(parent)
{
    information = inform;
}

int Model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return information.count();
}


int Model::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return int(ColumName::PERCENT) + 1;
}

  QVariant Model::data(const QModelIndex& index, int role) const
  {
      if (!index.isValid() || information.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
      {
          return QVariant();
      }
      switch (index.column())
      {
        case 0:
          return information[index.row()].path_;

        case 1:
        {
            QLocale locale(QLocale::English);
            return locale.formattedDataSize(information[index.row()].size_.toDouble());
        }

        case 2:
          return information[index.row()].percent_;

        default:
          return QVariant();
      }
  }



  void Model::setModel(const QList<AllInf> &inform)
  {
      beginResetModel();
       information = inform;
      endResetModel();
  }

