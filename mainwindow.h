#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QClipboard>
#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTextCursor>
#include <QFileDialog>
#include <QTextTableFormat>
#include <QTcpSocket>
#include "setting.h"
#include "color.h"
#include "find.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initUI();

private slots:
    void upload2Cloud();

    void on_copy_clicked();

    void on_cut_clicked();

    void on_paste_clicked();

    void on_overbold_clicked();

    void on_italics_clicked();

    void on_underline_clicked();

    void on_addsize_clicked();

    void on_reducesize_clicked();

    void on_fontcolor_clicked();

    void onColorPicked(const QString &hexColor);

    void on_find_clicked();

    void showFindText();

    void ChangeText();

    void on_mid_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void InsertTable();

    void handleText( QString& text);

private:
    Ui::MainWindow *ui;
    Setting *set;
    Color *color;
    Find *f;
    int m_selectionStart;
    int m_selectionEnd;
    QLineEdit *findLineEdit;
    QDialog *findDlg;
    QDialog *tabledlg;
    QLineEdit *changeLineEdit;
    QLineEdit *row;
    QLineEdit *column;
    QString filepath;
    QTcpSocket *socket;
    bool isConnected;
};
#endif // MAINWINDOW_H
