#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QClipboard>
#include <QImage>
#include <QPixmap>
#include <QByteArray>
#include <QBuffer>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <fstream>
#include <QMessageBox>
#include <string>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <unistd.h>
#include <QScreen>
#include <QtGui/QApplication>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_m_get_menu_clicked();

    void on_m_import_menu_clicked();

    void on_m_import_image_menu_clicked();

    void on_m_save_menu_clicked();

private:
    Ui::MainWindow *ui;

    QByteArray m_bateArrayResult;
//    QPixmap m_imageresult;
    QMenu * m_menu;
    QClipboard * board;

    QByteArray image_to_base64(QImage image);
    QPixmap base64_to_image(QByteArray base64);
    void showImageAndBase64(QByteArray bateArrayResult, QPixmap imageresult);
};

#endif // MAINWINDOW_H
