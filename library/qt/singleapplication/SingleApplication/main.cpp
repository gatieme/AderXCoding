#include "singleapplication.h"
#include <QApplication>
#include <QtSingleApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QtSingleApplication app(argc, argv);
    if (app.isRunning())
    {
        QMessageBox::information(NULL, "GLMPlayer",
                                 "Your GLMPLayer is already running ...",
                         QMessageBox::Ok);
        app.sendMessage("raise_window_noop");
        return EXIT_SUCCESS;
    }

    SingleApplication w;
    w.show();

    return app.exec();
}
