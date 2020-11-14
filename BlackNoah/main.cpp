#include "mainwindow.h"
#include "os_check.h"
#include "default_settings.h"
#include "launchmethods.h"
#include <QApplication>
#include <QIcon>

static OS_Check os_Check;          // Import classes from OS_Check

int main(int argc, char *argv[])
{
    os_Check.CheckOS();
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/blacknoah.svg"));
    MainWindow w;
    w.show();

    return a.exec();
}
