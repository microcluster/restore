#include "MainWindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion("0.0.1");
    a.setApplicationName("restore");
    MainWindow w;
    w.show();
    return a.exec();
}
