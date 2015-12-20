#include "restartwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int ret = -1;
    do
    {
        RestartWidget w;
        w.show();

        ret = a.exec();

    }while(ret != 0);

    return ret;
}
