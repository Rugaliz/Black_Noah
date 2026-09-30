#include "mainwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("blacknoah");
    QApplication::setDesktopFileName("blacknoah");
    app.setWindowIcon(QIcon(":/images/blacknoah.svg"));

    MainWindow window;
    window.show();

    return app.exec();
}
