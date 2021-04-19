#include "mainwindow.h"
#include "launchmethods.h"
#include <QApplication>
#include <QIcon>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/blacknoah.svg"));
    MainWindow w;
    w.show();
    return a.exec();
}
