#include "ValueTreeModel.h"

ValueTreeModel::ValueTreeModel(const Configuration& config, QObject* parent)
   : QAbstractItemModel(parent), m_rootItem(nullptr)
{
   //m_rootItem = ValueTreeItem({tr("Title"), tr("Summary")});
   //m_rootItem = ValueTreeItem({tr("Title"), tr("Summary")});
   config;
   //setupModelData(data.split('\n'), rootItem);
}

int ValueTreeModel::columnCount(const QModelIndex &parent) const
{
   if (parent.isValid())
   {
      return static_cast<ValueTreeItem*>(parent.internalPointer())->columnCount();
   }
   return m_rootItem.columnCount();
}

QVariant ValueTreeModel::data(const QModelIndex &index, int role) const
{
   if (!index.isValid())
      return QVariant();

   if (role != Qt::DisplayRole)
      return QVariant();

   ValueTreeItem *item = static_cast<ValueTreeItem*>(index.internalPointer());

   item->data(index.column());

   return {};
}

Qt::ItemFlags ValueTreeModel::flags(const QModelIndex &index) const
{
   if (!index.isValid())
   {
      return Qt::NoItemFlags;
   }

   return QAbstractItemModel::flags(index);
}

QVariant ValueTreeModel::headerData(int section, Qt::Orientation orientation,
   int role) const
{
   if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
   {
      //auto current = m_rootItem.data(section).getValue();
      auto value = std::visit(GetCurrentVisitor, m_rootItem.data(section));
      value;
      //std::visit()
   }

   return QVariant();
}

QModelIndex ValueTreeModel::index(int row, int column, const QModelIndex &parent) const
{
   if (!hasIndex(row, column, parent))
      return QModelIndex();

   const ValueTreeItem* parentItem{ nullptr };

   if (!parent.isValid())
      parentItem = m_rootItem.parentItem();
   else
      parentItem = static_cast<ValueTreeItem*>(parent.internalPointer());

   ValueTreeItem& childItem = parentItem->child(row);
   
   return createIndex(row, column, const_cast<ValueTreeItem*>(parentItem));
}

QModelIndex ValueTreeModel::parent(const QModelIndex& index) const
{
   if (!index.isValid())
      return QModelIndex();

   ValueTreeItem *childItem = static_cast<ValueTreeItem*>(index.internalPointer());
   const ValueTreeItem *parentItem = childItem->parentItem();

   //if (parentItem == rootItem)
   //   return QModelIndex();

   //return createIndex(parentItem->row(), 0, parentItem);
   return {};
}

int ValueTreeModel::rowCount(const QModelIndex &parent) const
{
   ValueTreeItem *parentItem;
   if (parent.column() > 0)
      return 0;

   if (!parent.isValid())
   //   parentItem = rootItem;
   //else
      parentItem = static_cast<ValueTreeItem*>(parent.internalPointer());

   return parentItem->childCount();
}

void ValueTreeModel::setupModelData(const QStringList& lines, ValueTreeItem* parent)
{
   //QVector<TreeItem*> parents;
   //QVector<int> indentations;
   //parents << parent;
   //indentations << 0;

   //int number = 0;

   //while (number < lines.count()) {
   //   int position = 0;
   //   while (position < lines[number].length()) {
   //      if (lines[number].at(position) != ' ')
   //         break;
   //      position++;
   //   }

   //   const QString lineData = lines[number].mid(position).trimmed();

   //   if (!lineData.isEmpty()) {
   //      // Read the column data from the rest of the line.
   //      const QStringList columnStrings = lineData.split('\t', QString::SkipEmptyParts);
   //      QVector<QVariant> columnData;
   //      columnData.reserve(columnStrings.count());
   //      for (const QString &columnString : columnStrings)
   //         columnData << columnString;

   //      if (position > indentations.last()) {
   //         // The last child of the current parent is now the new parent
   //         // unless the current parent has no children.

   //         if (parents.last()->childCount() > 0) {
   //            parents << parents.last()->child(parents.last()->childCount()-1);
   //            indentations << position;
   //         }
   //      } else {
   //         while (position < indentations.last() && parents.count() > 0) {
   //            parents.pop_back();
   //            indentations.pop_back();
   //         }
   //      }

   //      // Append a new item to the current parent's list of children.
   //      parents.last()->appendChild(new TreeItem(columnData, parents.last()));
   //   }
   //   ++number;
   //}
}
