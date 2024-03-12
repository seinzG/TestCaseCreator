#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon("icon1.png"));
    MainWindow w;

        // Get the primary screen
    QScreen *screen = QGuiApplication::primaryScreen();

    // Get the screen geometry
    QRect screenGeometry = screen->geometry();

    // Calculate the desired window height as 80% of the screen height
    int windowHeight = screenGeometry.height() * 0.7;
    int windowWidth = screenGeometry.width() * 0.15;
    w.resize(windowWidth, windowHeight);
    w.show();
    return a.exec();
}
