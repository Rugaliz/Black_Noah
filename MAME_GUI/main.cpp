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

    if (os_Check.OperatingSystem == "Linux") {
        system("echo 'This is running Linux'");
    }
    else {
        system("echo 'could not be read'");
    }
    std::cout <<"\n"+ os_Check.OperatingSystem+"\n";
    std::cout <<os_Check.numberB;
    std::cout <<"\n";
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/img/images/panther.svg"));
    MainWindow w;
    w.show();

    return a.exec();
}
