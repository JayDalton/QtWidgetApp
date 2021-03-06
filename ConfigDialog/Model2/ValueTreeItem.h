#pragma once

#include <memory>

#include "../Config/Configuration.h"

struct VariantValue
{

};

struct ValueTreeItem
{
   //using Item = std::unique_ptr<ValueTreeItem>;

   ValueTreeItem(ValueTreeItem* parent = nullptr);
   ~ValueTreeItem();

   ValueTreeItem(ValueTreeItem&& other);
   ValueTreeItem& operator=(ValueTreeItem&& other);

   void appendChild(ValueTreeItem item);

   ValueTreeItem& child(int row);
   ValueTreeItem& child(int row) const;

   int childCount() const;
   int columnCount() const;
   const ParameterVariant& data(int column) const;
   
   int row(const ValueTreeItem& item) const;
   int row() const;

   const ValueTreeItem* parentItem() const;

private:
   struct Impl;
   std::unique_ptr<Impl> m;
};

