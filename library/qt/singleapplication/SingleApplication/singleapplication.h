#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QWidget>

namespace Ui {
class SingleApplication;
}

class SingleApplication : public QWidget
{
    Q_OBJECT

public:
    explicit SingleApplication(QWidget *parent = 0);
    ~SingleApplication();

private:
    Ui::SingleApplication *ui;
};

#endif // SINGLEAPPLICATION_H
