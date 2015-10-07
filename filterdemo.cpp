#include "filterdemo.h"
#include "ui_filterdemo.h"

FilterDemo::FilterDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FilterDemo)
{
    ui->setupUi(this);
}

FilterDemo::~FilterDemo()
{
    delete ui;
}
