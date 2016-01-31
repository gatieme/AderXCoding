#include "singleapplication.h"
#include "ui_singleapplication.h"

SingleApplication::SingleApplication(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleApplication)
{
    ui->setupUi(this);
}

SingleApplication::~SingleApplication()
{
    delete ui;
}
