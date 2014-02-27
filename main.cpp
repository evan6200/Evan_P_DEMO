#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setFixedSize(900,700);
    //----center a window on the screen-----
    w.setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    w.size(),
                    qApp->desktop()->availableGeometry()
                ));


    return a.exec();
}


