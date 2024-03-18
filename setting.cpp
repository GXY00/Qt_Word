#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/new/head/img/setting.png"));
    setWindowTitle("设置");
    QStringList headers;
    headers << "操作" << "快捷键";
    QStandardItemModel * model = new QStandardItemModel(6,2,this);
    model->setHorizontalHeaderLabels(headers);
    QStringList op,shortcut;
    op << "新建" << "打开" << "保存" << "另存为" << "上传云端" << "帮助" << "选项";
    shortcut << "ctrl+n" << "ctrl+o" << "ctrl+s" << "ctrl+a" << "无" << "ctrl+h" << "ctrl+o";
    for(int i=0;i<op.size();i++)
    {
        QStandardItem *item1 = new QStandardItem(op[i]);
        QStandardItem *item2 = new QStandardItem(shortcut[i]);
        model->setItem(i,0,item1);
        model->setItem(i,1,item2);

    }
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setHidden(true);


}

Setting::~Setting()
{
    delete ui;
}

void Setting::on_pushButton_2_clicked()
{
    this->close();
}







void Setting::on_pushButton_3_clicked()
{
    QString text="hello world";
    qDebug() << "Send:" << text;
    emit updateshortcut(text);
}

