#include <QApplication>
#include <QUdpSocket>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>
#include <QTimer>

const char * clearColor  = new char[5] {'B', 'L', (char)0x00, (char)0x00, (char)0x00};
const char * greenColor  = new char[5] {'B', 'L', (char)0x00, (char)0xFF, (char)0x00};
const char * redColor    = new char[5] {'B', 'L', (char)0xFF, (char)0x00, (char)0x00};
const char * blueColor   = new char[5] {'B', 'L', (char)0x00, (char)0x00, (char)0xFF};
const char * yellowColor = new char[5] {'B', 'L', (char)0xFF, (char)0xFF, (char)0x00};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    QUdpSocket socket;

    QActionGroup *group = new QActionGroup(nullptr);
    group->setExclusive(true);

    QAction* red = new QAction(QObject::tr("Red"), nullptr);
    red->setCheckable(true);

    QAction* green = new QAction(QObject::tr("Green"), nullptr);
    green->setCheckable(true);

    QAction* blue = new QAction(QObject::tr("Blue"), nullptr);
    blue->setCheckable(true);

    QAction* yellow = new QAction(QObject::tr("Yellow"), nullptr);
    yellow->setCheckable(true);

    group->addAction(red);
    group->addAction(green);
    group->addAction(blue);
    group->addAction(yellow);

    QAction* quit = new QAction(QObject::tr("Quit"), nullptr);

    QTimer* timer = new QTimer(nullptr);

    // BusyLight will timeout after 30 seconds
    timer->setInterval(5000);
    timer->start();

    a.connect(timer, &QTimer::timeout, [&](){ socket.writeDatagram(clearColor, 5, QHostAddress::Broadcast, 443); });
    a.connect(quit, &QAction::triggered, &a, &QCoreApplication::quit);
    a.connect(red, &QAction::triggered, &a, [&](){ socket.writeDatagram(redColor, 5, QHostAddress::Broadcast, 443); });
    a.connect(green, &QAction::triggered, &a, [&]() { socket.writeDatagram(greenColor, 5, QHostAddress::Broadcast, 443); });
    a.connect(blue, &QAction::triggered, &a, [&]() { socket.writeDatagram(blueColor, 5, QHostAddress::Broadcast, 443); });
    a.connect(yellow, &QAction::triggered, &a, [&]() { socket.writeDatagram(yellowColor, 5, QHostAddress::Broadcast, 443); });

    QMenu* menu = new QMenu(nullptr);
    menu->addActions(group->actions());
    menu->addSeparator();
    menu->addAction(quit);

    QSystemTrayIcon* icon = new QSystemTrayIcon(nullptr);
    icon->setIcon(QIcon(":/heart.png"));
    icon->setContextMenu(menu);
    icon->show();

    return a.exec();
}


