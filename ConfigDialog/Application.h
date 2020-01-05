#pragma once

#include <QApplication>

class Application : public QApplication
{
   Q_OBJECT

public:
   explicit Application(int argc, char* argv[], std::string_view title);


private:
};

// Codepage: UTF-8 (ÜüÖöÄäẞß)
