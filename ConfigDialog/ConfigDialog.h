#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ConfigDialog.h"

class ConfigDialog : public QMainWindow
{
    Q_OBJECT

public:
    ConfigDialog(QWidget *parent = Q_NULLPTR);

private:
    Ui::ConfigDialogClass ui;
};
