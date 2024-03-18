#include "find.h"
#include "ui_find.h"

Find::Find(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Find)
{
    ui->setupUi(this);
    QString str = ui->find->text();

}

Find::~Find()
{
    delete ui;
}
