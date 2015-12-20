#include "restartwidget.h"
#include "ui_restartwidget.h"

RestartWidget::RestartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RestartWidget)
{
    ui->setupUi(this);

    ///
    connect(this->ui->pushButtonExitRestart, SIGNAL(clicked( )),
            this, SLOT(soltExitRestart()));

    ///
    connect(this->ui->pushButtonProcess, SIGNAL(clicked()),
            this, SLOT(slotProceeRestart()));
}

RestartWidget::~RestartWidget()
{
    delete ui;
}


///  使用事件循环进行重启
void RestartWidget::soltExitRestart()
{
    //  773 = 'r'+'e'+'s'+'t'+'a'+'r'+'t'
    //  ==>restart
    //#define EXIT_RESTART  773
    qApp->exit(773);

}


///  使用进程控制实现重启
/// 执行如下操作
/// ①  退出当前程序  (QT下有6种方式实现)
/// ②  开启新的进程启动当前程序  (使用QProcess::startDetached)
///
/// ①  6种方式实现退出
///
//  方式一：QCoreApplication::exit(0);0是状态还可以是其他的值。
//  方式二：QCoreApplication::quit();
//  方式三：QApplication::exit(0);QApplication是继承QCoreApplication的。
//  方式四：QApplication::quit();
//  方式五：close();QApplicatio有个常用属性qApp->quitOnLastWindowClosed(true);当最后一个窗口关闭时自动调用前面的exit()。
//  方式六：QApplication::closeAllWindows();关闭多个窗口，比调用quit好，因为窗口可以接受到close事件。
///
/// ②  开启新的进程启动当前程序
///
//  在Qt中, 可以使用QProcess::startDetached开启一个新的进程
//  要启动当前程序的另一个进程，有要使二者没有"父子"关系
//  使用QProcess::startDetached(qApp->applicationFilePath(), QStringList());
//  其中QStringList()为参数列表
//  特别的, 如果程序的路径中没有空格也可以使用QProcess::startDetached(qApp->applicationFilePath());
void RestartWidget::slotProceeRestart()
{
    qApp->closeAllWindows();
    //qApp->quit();

    //  如果是在嵌入式arm板子上，需要加入 -qws 的参数
    //QStringList args;
    //args.append("-qws");        //  参数信息
    //args.append("&");           //  后台运行
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());


}
