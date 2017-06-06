#include <QApplication>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>
#include <QTimer>
#include "lamp.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LampHandle * lh = lamp_init();

    QApplication::setQuitOnLastWindowClosed(false);
    QAction* red = new QAction(QObject::tr("Red"), nullptr);
    QAction* green = new QAction(QObject::tr("Green"), nullptr);
    QAction* blue = new QAction(QObject::tr("Blue"), nullptr);
    QAction* yellow = new QAction(QObject::tr("Yellow"), nullptr);
    QAction* quit = new QAction(QObject::tr("Quit"), nullptr);

    QTimer* timer = new QTimer(nullptr);

    // BusyLight will timeout after 30 seconds
    timer->setInterval(15000);
    timer->start();

    a.connect(timer, &QTimer::timeout, [lh](){ lamp_setColor(lh->cRed, lh->cGreen, lh->cBlue, lh); });

    a.connect(quit, &QAction::triggered, &a, &QCoreApplication::quit);
    a.connect(red, &QAction::triggered, &a, [lh]() { lamp_setColor(255, 0, 0, lh); });
    a.connect(green, &QAction::triggered, &a, [lh]() { lamp_setColor(0, 255, 0, lh); });
    a.connect(blue, &QAction::triggered, &a, [lh]() { lamp_setColor(0, 0, 255, lh); });
    a.connect(yellow, &QAction::triggered, &a, [lh]() { lamp_setColor(255, 255, 0, lh); });

    QMenu* menu = new QMenu(nullptr);
    menu->addAction(red);
    menu->addAction(green);
    menu->addAction(blue);
    menu->addAction(yellow);
    menu->addSeparator();
    menu->addAction(quit);

    QSystemTrayIcon* icon = new QSystemTrayIcon(nullptr);
    icon->setIcon(QIcon(":/heart.png"));
    icon->setContextMenu(menu);
    icon->show();

    return a.exec();
}

