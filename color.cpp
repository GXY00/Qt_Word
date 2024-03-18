#include "color.h"
#include "ui_color.h"

Color::Color(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Color)
{
    ui->setupUi(this);
    setWindowTitle("颜色");
    this->initCollect();
    ui->label->setStyleSheet("background-color:rgb(46, 47, 48);");
    ui->DeepRed->setStyleSheet("background-color:rgb(192, 0, 0)");
    ui->red->setStyleSheet("background-color:rgb(255, 0, 0)");
    ui->Eyellow->setStyleSheet("background-color:rgb(255, 192, 0)");
    ui->yellow->setStyleSheet("background-color:rgb(255, 255, 0)");
    ui->lgreen->setStyleSheet("background-color:rgb(146, 208, 80)");
    ui->dgreen->setStyleSheet("background-color:rgb(0, 176, 80)");
    ui->skyBlue->setStyleSheet("background-color:rgb(0, 176, 240)");
    ui->dblue->setStyleSheet("background-color:rgb(0, 112, 192)");
    ui->sblue->setStyleSheet("background-color:rgb(0, 32, 96)");
    ui->purple->setStyleSheet("background-color:rgb(112, 48, 160)");
    ui->RlineEdit->setText("46");
    ui->GlineEdit->setText("47");
    ui->BlineEdit->setText("48");
}

Color::~Color()
{
    delete ui;
}

void Color::on_cancel_clicked()
{
    this->close();
}

void Color::initCollect()
{
    ui->RSlider->setMaximum(255);
    ui->RSlider->setMinimum(0);
    ui->GSlider->setMaximum(255);
    ui->GSlider->setMinimum(0);
    ui->BSlider->setMaximum(255);
    ui->BSlider->setMinimum(0);
    connect(ui->RlineEdit, &QLineEdit::textChanged, this, &Color::updateLabelColor);
    connect(ui->GlineEdit, &QLineEdit::textChanged, this, &Color::updateLabelColor);
    connect(ui->BlineEdit, &QLineEdit::textChanged, this, &Color::updateLabelColor);
    connect(ui->confirm,&QPushButton::clicked,this,&Color::on_confirm_clicked);
}

void Color::on_RSlider_valueChanged(int value)
{
    ui->RlineEdit->setText(QString::number(value));
}


void Color::on_GSlider_valueChanged(int value)
{
    ui->GlineEdit->setText(QString::number(value));
}


void Color::on_BSlider_valueChanged(int value)
{
    ui->BlineEdit->setText(QString::number(value));
}

void Color::on_RlineEdit_textChanged(const QString &arg1)
{
    ui->RSlider->setSliderPosition(arg1.toInt());
}


void Color::on_GlineEdit_textChanged(const QString &arg1)
{
    ui->GSlider->setSliderPosition(arg1.toInt());
}


void Color::on_BlineEdit_textChanged(const QString &arg1)
{
    ui->BSlider->setSliderPosition(arg1.toInt());
}

void Color::updateLabelColor()
{
    // 获取三个QLineEdit的值
    int red = ui->RlineEdit->text().toInt();
    int green = ui->GlineEdit->text().toInt();
    int blue = ui->BlineEdit->text().toInt();

    // 设置QLabel的背景色
    ui->label->setStyleSheet(QString("background-color: rgb(%1, %2, %3)").arg(red).arg(green).arg(blue));
}

QString Color::toHEX(int r,int g,int b)
{
    QColor color(r, g, b);
    QString hexColor = color.name();
    return hexColor;
}

void Color::on_confirm_clicked()
{
    int r=ui->RlineEdit->text().toInt();
    int g=ui->GlineEdit->text().toInt();
    int b=ui->BlineEdit->text().toInt();
    QString hex = toHEX(r,g,b);
    emit colorPicked(hex);
    this->close();
}


void Color::on_DeepRed_clicked()
{
    QString hex = toHEX(192,0,0);
    emit colorPicked(hex);
    this->close();
}


void Color::on_red_clicked()
{
    QString hex = toHEX(255,0,0);
    emit colorPicked(hex);
    this->close();
}


void Color::on_Eyellow_clicked()
{
    QString hex = toHEX(255,192,0);
    emit colorPicked(hex);
    this->close();
}


void Color::on_yellow_clicked()
{
    QString hex = toHEX(255,255,0);
    emit colorPicked(hex);
    this->close();
}


void Color::on_lgreen_clicked()
{
    QString hex = toHEX(146,208,80);
    emit colorPicked(hex);
    this->close();
}


void Color::on_dgreen_clicked()
{
    QString hex = toHEX(0,176,80);
    emit colorPicked(hex);
    this->close();
}


void Color::on_skyBlue_clicked()
{
    QString hex = toHEX(0,176,240);
    emit colorPicked(hex);
    this->close();
}


void Color::on_dblue_clicked()
{
    QString hex = toHEX(0,112,192);
    emit colorPicked(hex);
    this->close();
}


void Color::on_sblue_clicked()
{
    QString hex = toHEX(0,32,96);
    emit colorPicked(hex);
    this->close();
}


void Color::on_purple_clicked()
{
    QString hex = toHEX(112,48,160);
    emit colorPicked(hex);
    this->close();
}

