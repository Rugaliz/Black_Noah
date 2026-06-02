#include "mainwindow.h"
#include "launchmethods.h"
#include <QApplication>
#include <QIcon>

// Main entry point for the application
int main(int argc, char *argv[])
{
    // Create the Qt application instance
    QApplication a(argc, argv);

    // Set the window icon using a SVG resource
    a.setWindowIcon(QIcon(":/images/blacknoah.svg"));

    // Create the main window
    MainWindow w;

    // Display the main window
    w.show();

    // Start the event loop and return the application exit code
    return a.exec();
}
