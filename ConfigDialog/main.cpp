#include "ConfigDialog.h"

#include "Model1/TreeModel.h"
#include "Model2/ValueTreeModel.h"

#include <QtWidgets/QApplication>

#include <QFile>
#include <QTreeView>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QFile file("c:/Repository/QtWidgetApp/ConfigDialog/default.txt");
   file.open(QIODevice::ReadOnly);
   TreeModel model(file.readAll());
   file.close();

   Configuration config;
   ValueTreeModel model2{ config };

   QTreeView view;
   view.setModel(&model);
   view.setWindowTitle(QObject::tr("Simple Tree Model"));
   view.show();
   return app.exec();

   //ConfigDialog w;
   //w.show();
   //return a.exec();
}
