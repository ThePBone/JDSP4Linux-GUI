 #ifndef MAIN
#define MAIN
#endif

#include "mainwindow.h"
#include "main.h"
#include "settings.h"
#include <QApplication>
#include <string>
#include <iostream>
#include <clocale>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed( false );
    app = &a;
 
    QLocale::setDefault(QLocale::c());
    std::setlocale(LC_NUMERIC, "C");
 
    MainWindow w;
    mainwin = &w;
   // w.setFixedSize(w.geometry().width(),w.geometry().height());
    w.setWindowFlags(Qt::WindowContextHelpButtonHint | Qt::WindowCloseButtonHint);
QApplication::setDesktopSettingsAware(true);
    w.show();
    QApplication::setQuitOnLastWindowClosed( true );

    return QApplication::exec();
}
