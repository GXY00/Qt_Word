#ifndef SETTING_H
#define SETTING_H

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class Setting;
}

class Setting : public QMainWindow
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void updateshortcut( QString& text);
private:
    Ui::Setting *ui;
};

#endif // SETTING_H
