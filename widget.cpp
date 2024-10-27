#include "widget.h"
#include "ui_widget.h"

int w_oldWidth;
int w_oldHeight;
QList<QObject*> w_objList;
QMap<QObject*, QRect> w_objMap;

widget::widget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);

    w_oldWidth=this->width();
    w_oldHeight=this->height();
    w_objList = this->centralWidget()->children();
     foreach (QObject* obj, w_objList)
      {
          w_objMap.insert(obj, obj->property("geometry").toRect());
      }

    bu = new backup();
    bu->hide();
    rst = new restore();
    rst->hide();
    connect(this->ui->backup,SIGNAL(clicked(bool)),this,SLOT(new_bakwidget()));
    connect(this->ui->restore,SIGNAL(clicked(bool)),this,SLOT(new_rstwidget()));
    connect(bu,&backup::return_to_main,this,&widget::show);
    connect(rst,&restore::return_to_main,this,&widget::show);
}

widget::~widget()
{
    delete ui;
}
void widget::new_bakwidget(){
    this->hide();
    bu->show();
}

void widget::new_rstwidget(){
    this->hide();
    rst->show();
}


void widget::resizeEvent(QResizeEvent *event)
{
    int Width = this->width();
    int Height = this->height();

    double  scaleX = Width*1.0/w_oldWidth*1.0;
    double  scaleY = Height*1.0/w_oldHeight*1.0;
    QMap<QObject*, QRect>::iterator iter;
       for (iter = w_objMap.begin(); iter != w_objMap.end(); iter++)
       {
           iter.key()->setProperty("geometry", QRect(iter.value().x() * scaleX, iter.value().y() * scaleY,
                                                     iter.value().width() * scaleX, iter.value().height() * scaleY));
       }
}
