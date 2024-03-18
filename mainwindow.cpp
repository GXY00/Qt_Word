#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeySequence>
#include <QShortcut>
#include <QTextDocumentWriter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Word编辑器");
    setWindowIcon(QIcon(":new/head/img/Word.png"));
    setFixedHeight(593);
    setFixedWidth(802);
    this->color=new Color();
    this->initUI();
    //创建菜单栏
    QMenuBar* menubar = new QMenuBar(this);
    this->setMenuBar(menubar);
    QStringList heads={"文件","开始","插入","页面"};
    QMenu *menu1=new QMenu(heads[0],this);
    QMenu *menu2=new QMenu(heads[1],this);
    QMenu *menu3=new QMenu(heads[2],this);
    QMenu *menu4=new QMenu(heads[3],this);

    menubar->addMenu(menu1);
    menubar->addMenu(menu2);
    menubar->addMenu(menu3);
    menubar->addMenu(menu4);

    QStringList actions={"新建(N)","打开(O)","保存(S)","另存为(A)","上传云端(C)","帮助(H)","选项(S)"};
    QAction *act1=new QAction(QIcon(":new/head/img/new.png"),actions[0]);
    QAction *act2=new QAction(QIcon(":new/head/img/open.png"),actions[1]);
    QAction *act3=new QAction(QIcon(":new/head/img/save.png"),actions[2]);
    QAction *act4=new QAction(QIcon(":new/head/img/asave.png"),actions[3]);
    QAction *cloud = new QAction(QIcon(":new/head/img/cloud.png"),actions[4]);
    QAction *act5=new QAction(QIcon(":new/head/img/help.png"),actions[5]);
    QAction *act6=new QAction(QIcon(":new/head/img/setting.png"),actions[6]);
    menu1->addAction(act1);
    menu1->addAction(act2);
    menu1->addAction(act3);
    menu1->addAction(act4);
    menu1->addAction(act5);
    menu1->addAction(act6);

    QAction *insertTable=new QAction(QIcon(":new/head/img/table.png"),"表格");
    QAction *insetImage=new QAction(QIcon(":new/head/img/imgs.png"),"图片");
    QAction *insertIcon=new QAction(QIcon(":new/head/img/shape.png"),"图标");

    menu3->addAction(insertTable);
    menu3->addAction(insetImage);
    menu3->addAction(insertIcon);

    //新建文件
    connect(act1,&QAction::triggered,this,[=](){
        this->filepath.clear();
        ui->textEdit->clear();
    });

    //打开文件
    connect(act2,&QAction::triggered,this,[=](){
        QString filePath = QFileDialog::getOpenFileName(this, "打开文件", "", "Microsoft Word文件(*.doc *.docx)");
        if(filePath.isEmpty()) {
            return;
        }

        QFile file(filePath);
        if(!file.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "错误", "无法打开文件: " + file.errorString());
            return;
        }
        this->filepath = filePath;
        QTextStream in(&file);
        QString content = in.readAll();
        //qDebug() << content;
        QTextDocument *doc = ui->textEdit->document();
        doc->setPlainText(content);

        file.close();
        QMessageBox::information(this, "成功", "文件打开成功");
    });

    //另存为
    QShortcut *ASave_shortcut = new QShortcut(QKeySequence("Ctrl+Shift+A"),this);
    connect(ASave_shortcut,&QShortcut::activated,[=](){
            if (this->filepath.isEmpty()) {
                // 如果文件路径为空，提示用户首先保存文件
                QMessageBox::warning(this, "错误", "请首先保存文件");
                return;
            }

            QFile file(this->filepath);
            if (!file.open(QFile::WriteOnly | QFile::Text)) {
                QMessageBox::warning(this, "错误", "无法保存: " + file.errorString());
                return;
            }

            QTextDocument *doc = ui->textEdit->document();
            QTextStream out(&file);
            out << doc->toHtml();

            file.close();
            qDebug() << "保存成功";
    });

    //保存
    QShortcut *Save_shortcut = new QShortcut(QKeySequence("Ctrl+S"),this);
    connect(Save_shortcut,&QShortcut::activated,[=](){
        if (this->filepath.isEmpty()) {
            // 如果文件路径为空，提示用户首先保存文件
            QMessageBox::warning(this, "错误", "请首先保存文件");
            return;
        }

        QFile file(this->filepath);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "错误", "无法保存: " + file.errorString());
            return;
        }

        QTextDocument *doc = ui->textEdit->document();
        QTextStream out(&file);
        out << doc->toHtml();

        file.close();
        qDebug() << "保存成功";
    });

    connect(act3,&QAction::triggered,this,[=](){
        QString filePath = QFileDialog::getSaveFileName(this, "选择路径", "", "Microsoft Word97-2003文件(*.doc)");
        if(filePath.isEmpty()) {
            return;
        }

        this->filepath=filePath;

        QFile file(filePath);
        if(!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "错误", "无法保存: " + file.errorString());
            return;
        }

        QTextDocument *doc = ui->textEdit->document();
        QTextStream out(&file);
        out << doc->toHtml();

        file.close();
        QMessageBox::information(this, "成功", "保存成功");
    });

    //云存储
    connect(cloud,&QAction::triggered,this,&MainWindow::upload2Cloud);

    connect(act4,&QAction::triggered,this,[=](){
        QString filePath = QFileDialog::getSaveFileName(this, "选择路径", "", "Microsoft Word97-2003文件(*.doc)");
        if(filePath.isEmpty()) {
            return;
        }

        this->filepath=filePath;

        QFile file(filePath);
        if(!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "错误", "无法保存: " + file.errorString());
            return;
        }

        QTextDocument *doc = ui->textEdit->document();
        QTextStream out(&file);
        out << doc->toHtml();

        file.close();
        QMessageBox::information(this, "成功", "另存为成功");
    });

    connect(act6,&QAction::triggered,this,[=](){
        this->set=new Setting();
        connect(set,SIGNAL(updateshortcut(QString&)),this,SLOT(handleText(QString&)));
        set->show();
    });

    connect(ui->style,&QComboBox::currentIndexChanged,this,[=](){
        //qDebug()<<ui->style->currentIndex();
        // 创建一个 QTextCharFormat 对象
        QTextCharFormat textFormat;
        textFormat.setFontFamily(ui->style->currentText()); // 设置字体
        // 获取当前光标
        QTextCursor cursor = ui->textEdit->textCursor();

        QString selectedText=cursor.selectedText();
        // 将样式应用到光标选中的文本上
        cursor.mergeCharFormat(textFormat);

        // 将新的光标设置为 QTextEdit 的光标
        ui->textEdit->setTextCursor(cursor);
    });

    connect(ui->size,&QComboBox::currentIndexChanged,this,[=](){
        QTextCharFormat textFormat;
        int fs = ui->size->currentText().toInt();
        //qDebug()<<typeid(fs).name();
        textFormat.setFontPointSize(fs);
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.mergeCharFormat(textFormat);
        ui->textEdit->setTextCursor(cursor);
    });

    connect(insetImage,&QAction::triggered,this,[=](){
        QString imagePath = QFileDialog::getOpenFileName(this, "选择要插入的图片", "", "Images (*.png *.jpg *.jpeg *.bmp)");
        if (!imagePath.isEmpty()) {
            QImage image(imagePath);
            if (image.isNull()) {
                // 图片加载失败
                return;
            }

            // 将QImage转换为QPixmap
            QPixmap pixmap = QPixmap::fromImage(image);

            // 创建一个QTextDocument
            QTextDocument *doc = ui->textEdit->document();

            // 将图片插入到QTextDocument中
            doc->addResource(QTextDocument::ImageResource, QUrl(imagePath), QVariant(pixmap));

            // 创建一个QTextCursor
            QTextCursor cursor = ui->textEdit->textCursor();

            // 插入图片
            QTextImageFormat imageFormat;
            imageFormat.setWidth(pixmap.width());
            imageFormat.setHeight(pixmap.height());
            imageFormat.setName(imagePath);
            cursor.insertImage(imageFormat);

            // 应用插入的图片
            ui->textEdit->setTextCursor(cursor);
        }
    });

    connect(insertTable,&QAction::triggered,this,[=](){
        QDialog *tabledlg = new QDialog(this);
        tabledlg->setWindowTitle("插入表格");
        row = new QLineEdit(tabledlg);
        row->setPlaceholderText("行数");
        column = new QLineEdit(tabledlg);
        column->setPlaceholderText("列数");
        QPushButton *confirm = new QPushButton(tr("确定"),tabledlg);

        QVBoxLayout *layou = new QVBoxLayout(tabledlg);
        layou->addWidget(row);
        layou->addWidget(column);
        layou->addWidget(confirm);
        connect(confirm,&QPushButton::clicked,this,&MainWindow::InsertTable);
        tabledlg->show();

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::upload2Cloud()
{
    QString ip = "127.0.0.1";
    unsigned short port = 8080;
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress(ip),port);
    isConnected = false;
    connect(socket,&QTcpSocket::connected,this,[=](){
        isConnected = true;
    });
    if(!isConnected)
    {
        QMessageBox::critical(this,"错误","与服务器连接失败");
    }
    connect(socket,&QTcpSocket::disconnected,this,[=](){
        socket->close();
    });
    QString path = QFileDialog::getOpenFileName(this, "选择路径", "", "Microsoft Word97-2003文件(*.doc)");
}

void MainWindow::initUI()
{
    ui->brush->setIcon(QIcon(":/new/head/img/brush.png"));
    ui->paste->setIcon(QIcon(":/new/head/img/paste.png"));
    ui->cut->setIcon(QIcon(":/new/head/img/cut.png"));
    ui->copy->setIcon(QIcon(":/new/head/img/copy.png"));
    ui->overbold->setIcon(QIcon(":/new/head/img/B.png"));
    ui->italics->setIcon(QIcon(":/new/head/img/I.png"));
    ui->underline->setIcon(QIcon(":/new/head/img/underline.png"));
    ui->addsize->setIcon(QIcon(":/new/head/img/psize.png"));
    ui->reducesize->setIcon(QIcon(":/new/head/img/rsize.png"));
    ui->fontcolor->setIcon(QIcon(":/new/head/img/fontcolor.png"));
    ui->unorder->setIcon(QIcon(":/new/head/img/unorder.png"));
    ui->order->setIcon(QIcon(":/new/head/img/123.png"));
    ui->left->setIcon(QIcon(":/new/head/img/left.png"));
    ui->mid->setIcon(QIcon(":/new/head/img/mid.png"));
    ui->right->setIcon(QIcon(":/new/head/img/right.png"));
    ui->find->setIcon(QIcon(":/new/head/img/find.png"));
    ui->find->setIconSize(QSize(50,50));
    ui->GIcon->setIcon(QIcon(":/new/head/img/g.png"));

    QStringList styles={"宋体","黑体","隶书","楷体","华文仿宋","华文行楷"};
    for(int i=0;i<6;i++)
    {
        ui->style->addItem(styles[i]);
    }
    for(int i=1;i<=40;i++)
    {
        ui->size->addItem(QString::number(i));
    }

}

void MainWindow::on_copy_clicked()
{
    QClipboard *clip = QApplication::clipboard();
    QString selectedText = ui->textEdit->textCursor().selectedText();
    qDebug()<<selectedText;
    clip->setText(selectedText);
}


void MainWindow::on_cut_clicked()
{
    QClipboard *clip = QApplication::clipboard();
    QString selectedText = ui->textEdit->textCursor().selectedText();
    clip->setText(selectedText);
    QTextCursor textCursor = ui->textEdit->textCursor();
    textCursor.removeSelectedText();
    ui->textEdit->setTextCursor(textCursor);
}


void MainWindow::on_paste_clicked()
{
    QClipboard *clip=QApplication::clipboard();
    QString orginaltext = clip->text();
    QTextCursor textCursor = ui->textEdit->textCursor();
    textCursor.insertText(orginaltext);
    ui->textEdit->setTextCursor(textCursor);
}


//void MainWindow::on_style_currentIndexChanged(int index)
//{
//    // 创建一个 QTextCharFormat 对象
//    QTextCharFormat textFormat;
//    QStringList styles={"宋体","黑体","隶书","楷体","华文仿宋","华文行楷"};
//    textFormat.setFontFamily("楷体"); // 设置字体
//    // 如果需要设置其他样式，比如字号、颜色等，也可以在这里设置

//    // 获取当前光标
//    QTextCursor cursor = ui->textEdit->textCursor();

//    // 将样式应用到光标选中的文本上
//    cursor.mergeCharFormat(textFormat);

//    // 将新的光标设置为 QTextEdit 的光标
//    ui->textEdit->setTextCursor(cursor);
//}




// 在槽函数中根据标记变量的值来切换字体样式
void MainWindow::on_overbold_clicked()
{
    bool isBold = false;
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;

    if (isBold) {
        format.setFontWeight(QFont::Normal); // 恢复原状
        isBold = false;
    } else {
        format.setFontWeight(QFont::Bold); // 加粗字体
        isBold = true;
    }

    cursor.mergeCharFormat(format);
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_italics_clicked()
{
    bool isItalics=false;
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;
    if(!isItalics)
    {
        format.setFontItalic(true);
        isItalics=true;
    }
    else
    {
        format.setFontItalic(false);
        isItalics=false;
    }
    cursor.mergeCharFormat(format);
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_underline_clicked()
{
    bool isUnderLine=false;
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;
    if (isUnderLine) {
        format.setFontUnderline(false); // 取消下划线
        isUnderLine = false;
    } else {
        format.setFontUnderline(true); // 设置下划线
        isUnderLine = true;
    }
    cursor.mergeCharFormat(format);
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_addsize_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;

    // 获取当前字体大小
    int currentSize = cursor.charFormat().fontPointSize();
    if (currentSize == -1) {
        currentSize = QApplication::font().pointSize(); // 使用应用程序的默认字体大小
    }

    // 增大字体大小
    format.setFontPointSize(currentSize + 1);

    cursor.mergeCharFormat(format);
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_reducesize_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;

    // 获取当前字体大小
    int currentSize = cursor.charFormat().fontPointSize();
    if (currentSize == -1) {
        currentSize = QApplication::font().pointSize(); // 使用应用程序的默认字体大小
    }

    // 增大字体大小
    format.setFontPointSize(currentSize - 1);

    cursor.mergeCharFormat(format);
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_fontcolor_clicked()
{
    this->color=new Color();
    color->show();
    QTextCursor cursor = ui->textEdit->textCursor();
    m_selectionStart = cursor.selectionStart();
    m_selectionEnd = cursor.selectionEnd();
    connect(color, &Color::colorPicked, this, &MainWindow::onColorPicked);
}

void MainWindow::onColorPicked(const QString &hexColor)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;

    format.setForeground(QColor(hexColor));

    // 将选中的文本设置为所选颜色
    cursor.setPosition(m_selectionStart);
    cursor.setPosition(m_selectionEnd, QTextCursor::KeepAnchor);
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}


void MainWindow::on_find_clicked()
{
    findDlg = new QDialog(this);
    findDlg->setWindowTitle(tr("查找"));
    findLineEdit = new QLineEdit(findDlg);
    findLineEdit->setPlaceholderText("查找");
    //changeLineEdit = new QLineEdit(findDlg);
    //changeLineEdit->setPlaceholderText("替换");
    QPushButton *findbt= new QPushButton(tr("查找"), findDlg);
    //QPushButton *changebt = new QPushButton(tr("替换"), findDlg);
    QVBoxLayout *layou= new QVBoxLayout(findDlg);
    layou->addWidget(findLineEdit);
    //layou->addWidget(changeLineEdit);
    layou->addWidget(findbt);
    //layou->addWidget(changebt);
    connect(findbt, &QPushButton::clicked, this, &MainWindow::showFindText);
    //connect(changebt, &QPushButton::clicked, this, &MainWindow::ChangeText);
    findDlg->show();
}

void MainWindow::showFindText()
{
    QString str = findLineEdit->text();
    QTextCursor cursor(ui->textEdit->textCursor());
    cursor.movePosition(QTextCursor::Start);
    bool found = ui->textEdit->find(str, QTextDocument::FindBackward);
    if (!found)
    {
        QMessageBox::warning(this, tr("查找"), tr("未找到：%1").arg(str));
    }
}

void MainWindow::ChangeText()
{
    QString toChange = changeLineEdit->text();
    QString toFind = findLineEdit->text();
    QTextCursor cursor(ui->textEdit->textCursor());
    cursor.movePosition(QTextCursor::Start);
    bool found = false;
    while (!cursor.isNull() && !cursor.atEnd())
    {
        found = ui->textEdit->find(toFind, QTextDocument::FindBackward);
        if (found)
        {
            cursor.insertText(toChange);
            ui->textEdit->setTextCursor(cursor);  // 设置文本光标为当前位置
        }
    }
    if (!found)
    {
        QMessageBox::warning(this, tr("查找"), tr("未找到：%1").arg(toFind));
    }

}


void MainWindow::on_mid_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    int selectStart = cursor.selectionStart();
    int selectEnd = cursor.selectionEnd();
    cursor.setPosition(selectStart, QTextCursor::MoveAnchor);
    cursor.setPosition(selectEnd, QTextCursor::KeepAnchor);
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignCenter);
    cursor.setBlockFormat(format);

    // 应用对齐设置
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_left_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    int selectStart = cursor.selectionStart();
    int selectEnd = cursor.selectionEnd();
    cursor.setPosition(selectStart, QTextCursor::MoveAnchor);
    cursor.setPosition(selectEnd, QTextCursor::KeepAnchor);
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignLeft);
    cursor.setBlockFormat(format);

    // 应用对齐设置
    ui->textEdit->setTextCursor(cursor);
}


void MainWindow::on_right_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    int selectStart = cursor.selectionStart();
    int selectEnd = cursor.selectionEnd();
    cursor.setPosition(selectStart, QTextCursor::MoveAnchor);
    cursor.setPosition(selectEnd, QTextCursor::KeepAnchor);
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignRight);
    cursor.setBlockFormat(format);

    // 应用对齐设置
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::InsertTable()
{
    int r=row->text().toInt();
    int c=column->text().toInt();

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTableFormat format;
    format.setWidth(200);
//    format.setHeight(50);
    cursor.insertTable(r,c,format);

    ui->textEdit->setTextCursor(cursor);
    tabledlg->close();
}

void MainWindow::handleText( QString& text)
{
    qDebug() << "Receive:" << text;
}
