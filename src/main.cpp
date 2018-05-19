#include <QApplication>
#include <QUdpSocket>
#include <QMenu>
#include <QAction>
#include <QSystemTrayIcon>
#include <QTimer>

static const char colors[5][5]  =
    {
        {'B', 'L', (char)0x00, (char)0x00, (char)0x00},
        {'B', 'L', (char)0x00, (char)0xFF, (char)0x00},
        {'B', 'L', (char)0xFF, (char)0x00, (char)0x00},
        {'B', 'L', (char)0x00, (char)0x00, (char)0xFF},
        {'B', 'L', (char)0xFF, (char)0xFF, (char)0x00}
    };

static enum COLOR {
    Color_Clear = 0,
    Color_Green = 1,
    Color_Red   = 2,
    Color_Blue  = 3,
    Color_Yellow= 4
} currentColor = Color_Clear;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    QUdpSocket socket;

    QActionGroup *group = new QActionGroup(nullptr);
    group->setExclusive(true);

    QAction* clear = new QAction(QObject::tr("Clear"), nullptr);
    clear->setCheckable(true);
    clear->setChecked(true);

    QAction* red = new QAction(QObject::tr("Red"), nullptr);
    red->setCheckable(true);

    QAction* green = new QAction(QObject::tr("Green"), nullptr);
    green->setCheckable(true);

    QAction* blue = new QAction(QObject::tr("Blue"), nullptr);
    blue->setCheckable(true);

    QAction* yellow = new QAction(QObject::tr("Yellow"), nullptr);
    yellow->setCheckable(true);

    group->addAction(clear);
    group->addAction(red);
    group->addAction(green);
    group->addAction(blue);
    group->addAction(yellow);

    QAction* quit = new QAction(QObject::tr("Quit"), nullptr);

    QTimer* timer = new QTimer(nullptr);

    // BusyLight will timeout after 30 seconds
    timer->setInterval(5000);
    timer->start();

    a.connect(timer, &QTimer::timeout, [&](){ socket.writeDatagram(colors[currentColor], 5, QHostAddress::Broadcast, 443); });
    a.connect(quit, &QAction::triggered, &a, &QCoreApplication::quit);
    a.connect(clear, &QAction::triggered, &a, [&]() { currentColor = Color_Clear; socket.writeDatagram(colors[currentColor], 5, QHostAddress::Broadcast, 443); });
    a.connect(red, &QAction::triggered, &a, [&](){ currentColor = Color_Red; socket.writeDatagram(colors[currentColor], 5, QHostAddress::Broadcast, 443); });
    a.connect(green, &QAction::triggered, &a, [&]() { currentColor = Color_Green; socket.writeDatagram(colors[currentColor], 5, QHostAddress::Broadcast, 443); });
    a.connect(blue, &QAction::triggered, &a, [&]() { currentColor = Color_Blue; socket.writeDatagram(colors[currentColor], 5, QHostAddress::Broadcast, 443); });
    a.connect(yellow, &QAction::triggered, &a, [&]() { currentColor = Color_Yellow; socket.writeDatagram(colors[currentColor], 5, QHostAddress::Broadcast, 443); });

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


