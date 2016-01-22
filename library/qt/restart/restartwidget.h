#ifndef RESTARTWIDGET_H
#define RESTARTWIDGET_H

#include <QWidget>
#include <QProcess>

namespace Ui {
class RestartWidget;
}

//  773 = 'r'+'e'+'s'+'t'+'a'+'r'+'t'
//  ==>restart
#define EXIT_RESTART   773

class RestartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RestartWidget(QWidget *parent = 0);
    ~RestartWidget();


///  槽函数信息
public slots :
    void soltExitRestart();          ///  使用事件循环进行重启

    void slotProceeRestart();        ///  使用进程控制实现重启
private:
    Ui::RestartWidget *ui;
};

#endif // RESTARTWIDGET_H
