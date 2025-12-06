#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("QT Study");
    QApplication::setApplicationVersion("1.0");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}