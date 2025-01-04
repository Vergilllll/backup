#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include "backup.h"
#include "restore.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class widget;
}
QT_END_NAMESPACE

class widget : public QMainWindow
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    ~widget();

private:
    Ui::widget *ui;
    backup *bu;
    restore *rst;
private slots:
    void new_bakwidget();
    void new_rstwidget();
    void resizeEvent(QResizeEvent *event);
};
#endif // WIDGET_H
