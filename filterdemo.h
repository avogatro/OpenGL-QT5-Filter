#ifndef FILTERDEMO_H
#define FILTERDEMO_H

#include <QMainWindow>

namespace Ui {
class FilterDemo;
}

class FilterDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit FilterDemo(QWidget *parent = 0);
    ~FilterDemo();

private:
    Ui::FilterDemo *ui;
};

#endif // FILTERDEMO_H
