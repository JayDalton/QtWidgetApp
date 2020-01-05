#include "Application.h"

Application::Application(int argc, char* argv[], std::string_view title)
   : QApplication(argc, argv)
{
   QApplication::setOrganizationName("NoneProfitAG");
   QApplication::setApplicationName(title.data());
   QApplication::setApplicationVersion("0.1");


   auto con = connect(this, &QApplication::lastWindowClosed, this, &QApplication::quit);

   //m_dialog->show();
}

// Codepage: UTF-8 (ÜüÖöÄäẞß)
