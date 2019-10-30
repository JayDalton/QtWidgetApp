#include "ValueTreeItem.h"

struct ValueTreeItem::Impl
{
   Impl(ValueTreeItem* parent) : parent(parent) {}

   std::vector<ValueTreeItem> childs;
   std::vector<ParameterVariant> values;
   ValueTreeItem* parent{ nullptr };
};

ValueTreeItem::ValueTreeItem(ValueTreeItem* parent/*, NodeData data*/)
   : m(std::make_unique<Impl>(parent))
{
}

ValueTreeItem::~ValueTreeItem() = default;
ValueTreeItem::ValueTreeItem(ValueTreeItem&& other) = default;
ValueTreeItem& ValueTreeItem::operator=(ValueTreeItem&& other) = default;

void ValueTreeItem::appendChild(ValueTreeItem item)
{
   m->childs.push_back(std::move(item));
}

ValueTreeItem& ValueTreeItem::child(int row)
{
   return m->childs.at(row);
}

int ValueTreeItem::childCount() const
{
   return m->childs.size();
}

int ValueTreeItem::columnCount() const
{
   return m->values.size();
}

const ParameterVariant& ValueTreeItem::data(int column) const
{
   return m->values.at(column);
}

int ValueTreeItem::row(const ValueTreeItem& item) const
{
   auto found = std::find_if(
      m->childs.cbegin(), m->childs.cend(), 
      [&item](const ValueTreeItem& treeItem) {
         return &treeItem == &item;
      }
   );
   if (found != m->childs.cend())
   {
      return std::distance(m->childs.cbegin(), found);
   }
   return 0;
}

int ValueTreeItem::row() const
{
   if (m->parent)
   {
      return m->parent->row(*this);
   }
   return 0;
}

const ValueTreeItem* ValueTreeItem::parentItem() const
{
   return m->parent;
}
