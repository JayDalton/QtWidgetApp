#pragma once

#include "../Config/Configuration.h"

#include "ValueTreeItem.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

struct ValueTreeModel : public QAbstractItemModel
{
   Q_OBJECT

public:
   explicit ValueTreeModel(const Configuration& config, QObject *parent = nullptr);
   ~ValueTreeModel() = default;

   QVariant data(const QModelIndex &index, int role) const override;
   Qt::ItemFlags flags(const QModelIndex &index) const override;
   QVariant headerData(int section, Qt::Orientation orientation,
      int role = Qt::DisplayRole) const override;
   QModelIndex index(int row, int column,
      const QModelIndex &parent = QModelIndex()) const override;
   QModelIndex parent(const QModelIndex &index) const override;
   int rowCount(const QModelIndex &parent = QModelIndex()) const override;
   int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
   void setupModelData(const QStringList& lines, ValueTreeItem* parent);

   ValueTreeItem m_rootItem;
};

