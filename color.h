#ifndef COLOR_H
#define COLOR_H

#include <QWidget>
#include <QPalette>

namespace Ui {
class Color;
}

class Color : public QWidget
{
    Q_OBJECT

public:
    explicit Color(QWidget *parent = nullptr);
    ~Color();
    void initCollect();
    QString toHEX(int r,int g,int b);

signals:
    void colorPicked(const QString &hexColor);

private slots:
    void on_cancel_clicked();

    void on_RSlider_valueChanged(int value);

    void on_GSlider_valueChanged(int value);

    void on_BSlider_valueChanged(int value);

    void on_RlineEdit_textChanged(const QString &arg1);

    void on_GlineEdit_textChanged(const QString &arg1);

    void on_BlineEdit_textChanged(const QString &arg1);
    void updateLabelColor();

    void on_confirm_clicked();

    void on_DeepRed_clicked();

    void on_red_clicked();

    void on_Eyellow_clicked();

    void on_yellow_clicked();

    void on_lgreen_clicked();

    void on_dgreen_clicked();

    void on_skyBlue_clicked();

    void on_dblue_clicked();

    void on_sblue_clicked();

    void on_purple_clicked();

private:
    Ui::Color *ui;
};

#endif // COLOR_H
