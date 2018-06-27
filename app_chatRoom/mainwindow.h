#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
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
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QScrollBar>
#include <QWidget>
#include <QDialog>
#include <QUrl>
#include <QLabel>
#include <QMap>
#include <QTextLayout>
#include <QTextCursor>
#include <QTextBlock>
#include <QTextEdit>
#include <QDateTime>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>


#include <sio_client.h>
#include <sio_message.h>
#include <sio_socket.h>

#include <mutex>
#include <condition_variable>
#include <string>
#include <QtGui/QApplication>

#include "myqtextedit.h"

using namespace sio;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyReleaseEvent( QKeyEvent *key );

private Q_SLOTS:
    void on_m_imageButton_clicked();

    void on_m_sendButton_clicked();

    void getNewMessage();

    void showNewMessage(const QString newMessage, const QString user);

    void showEnlargeImage();


Q_SIGNALS:
    void showNewMessageSignal(const QString newMessage, const QString user);

private:
    Ui::MainWindow *ui;
    QByteArray image_to_base64(const QImage image);
    QPixmap base64_to_image(const QByteArray base64);

    void connectServer();

    void sendNewMessage(const QString newMessage);

    QString getDataFromShearPlate();

    socket::ptr _current_socket;
    bool _connect_finish = false;
    std::mutex _lock;

    std::condition_variable_any _cond;
    sio::client _client;

    QTimer * _timer;

    QClipboard * _shearPlate;

    myQTextEdit * _myQTextEdit;

    QMap<QString, QByteArray> _base64Map;
};

#endif // MAINWINDOW_H
