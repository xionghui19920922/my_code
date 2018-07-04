#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->m_image_label->setScaledContents(true);

    m_menu = new QMenu("menu");

    QAction * m_get_action = new QAction("get", this);
    m_menu->addAction(m_get_action);

    QAction * m_import_base64_action = new QAction("importBase64", this);
    m_menu->addAction(m_import_base64_action);

    QAction * m_import_image_action = new QAction("importImage", this);
    m_menu->addAction(m_import_image_action);

    QAction * m_save_action = new QAction("save", this);
    m_menu->addAction(m_save_action);

    ui->menuBar->addMenu(m_menu);

    ui->m_text_label->setReadOnly(true);

    connect(m_get_action, SIGNAL(triggered()), this, SLOT(on_m_get_menu_clicked()));
    connect(m_import_base64_action, SIGNAL(triggered()), this, SLOT(on_m_import_menu_clicked()));
    connect(m_import_image_action, SIGNAL(triggered()), this, SLOT(on_m_import_image_menu_clicked()));
    connect(m_save_action, SIGNAL(triggered()), this, SLOT(on_m_save_menu_clicked()));

    board = QApplication::clipboard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_m_get_menu_clicked()
{
    ui->m_image_label->clear();
    ui->m_text_label->clear();

    QImage m_image;

    if (board->image().isNull())
    {
        return;
    }

    while (1)
    {
        m_image = board->image();
        if (!m_image.isNull())
        {
            break;
        }
    }

    QByteArray bateArrayResult;
    QPixmap imageresult;

    bateArrayResult = image_to_base64(m_image);
    imageresult = base64_to_image(bateArrayResult);

    m_bateArrayResult = bateArrayResult;

    showImageAndBase64(bateArrayResult, imageresult);
}

void MainWindow::on_m_import_menu_clicked()
{
    ui->m_image_label->clear();
    ui->m_text_label->clear();

    QString path = QFileDialog::getOpenFileName(m_menu,tr("Open_Image"),"/home",tr("Image　Files(*)"));

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }


    QTextStream bateArray(&file);
    QString lineStr;
    while(!bateArray.atEnd())
    {
        lineStr = bateArray.readLine();
    }

    QByteArray bateArrayResult;
    QPixmap imageresult;

    bateArrayResult = lineStr.toUtf8();

    file.close();

    imageresult = base64_to_image(bateArrayResult);

    m_bateArrayResult = bateArrayResult;

    showImageAndBase64(bateArrayResult, imageresult);
}

void MainWindow::on_m_import_image_menu_clicked()
{
    QString path = QFileDialog::getOpenFileName(m_menu,tr("Open_Image"),"/home",tr("Image　Files(*)"));
    QImage * image= new QImage(path);

    QByteArray bateArrayResult;
    QPixmap imageresult;

    bateArrayResult = image_to_base64(*image);
    imageresult = base64_to_image(bateArrayResult);

    m_bateArrayResult = bateArrayResult;

    showImageAndBase64(bateArrayResult, imageresult);
}

void MainWindow::on_m_save_menu_clicked()
{
    QString path = QFileDialog::getSaveFileName(this,tr("Save base64"),"/home",tr("base64 (*)"));
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream txtOutput(&file);

    QByteArray bateArray(m_bateArrayResult);

    txtOutput << bateArray;

    file.close();

    QPixmap imageresult = base64_to_image(m_bateArrayResult);

    QString imagePath = QFileDialog::getSaveFileName(this,tr("Save Image"),"/home",tr("Image (*.*)"));

    imageresult.save(imagePath);
}

QByteArray MainWindow::image_to_base64(QImage image)
{

    QByteArray m_bateArray;

    QBuffer m_buffer(&m_bateArray);

    image.save(&m_buffer,"PNG",20);

    QByteArray bateArrayResult;

    bateArrayResult = m_bateArray.toBase64();

    m_buffer.close();

    return bateArrayResult;
}

QPixmap MainWindow::base64_to_image(QByteArray base64)
{
    QByteArray Ret_bytearray;

    Ret_bytearray = QByteArray::fromBase64(base64);

    QBuffer buffer(&Ret_bytearray);

    buffer.open(QIODevice::WriteOnly);

    QPixmap imageresult;

    imageresult.loadFromData(Ret_bytearray);

    return imageresult;

}

void MainWindow::showImageAndBase64(QByteArray bateArrayResult, QPixmap imageresult)
{
    ui->m_text_label->setText(bateArrayResult);
    ui->m_image_label->setPixmap(imageresult);
}





















