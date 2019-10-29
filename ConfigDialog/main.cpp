#include "ConfigDialog.h"

#include "Model/TreeModel.h"

#include <QtWidgets/QApplication>

#include <QFile>
#include <QTreeView>

int main(int argc, char *argv[])
{
   //Q_INIT_RESOURCE(simpletreemodel);

   QApplication app(argc, argv);

   QFile file("c:/Repository/QtWidgetApp/ConfigDialog/default.txt");
   file.open(QIODevice::ReadOnly);
   TreeModel model(file.readAll());
   file.close();

   QTreeView view;
   view.setModel(&model);
   view.setWindowTitle(QObject::tr("Simple Tree Model"));
   view.show();
   return app.exec();

    //QApplication a(argc, argv);
    //ConfigDialog w;
    //w.show();
    //return a.exec();
}
