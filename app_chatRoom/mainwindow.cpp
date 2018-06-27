#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainToolBar->hide();

    _myQTextEdit = new myQTextEdit();

    ui->m_infoLayout->addWidget(_myQTextEdit);

    _myQTextEdit->setReadOnly(true);
    ui->m_imageButton->setStyleSheet("QPushButton{border-image: url(../app_chatRoom/image.png);}"
                                     "border-style:solid;\nbackground-color:white;");
    _myQTextEdit->setStyleSheet("border-style:solid;\nbackground-color:white;");

    QScrollBar * scrollBary = _myQTextEdit->verticalScrollBar();
    if(scrollBary)
    {
        scrollBary->setSliderPosition(scrollBary->maximum());
    }

    _timer = new QTimer(this);

    connect(_timer, SIGNAL(timeout()), this, SLOT(getNewMessage()));
    connect(this, SIGNAL(showNewMessageSignal(QString, QString)), this, SLOT(showNewMessage(QString, QString)));

    connect(_myQTextEdit, SIGNAL(clicked()), this, SLOT(showEnlargeImage()));
    _shearPlate = QApplication::clipboard();

    connectServer();
}

MainWindow::~MainWindow()
{
    delete _myQTextEdit;
    _timer->stop();
    _client.sync_close();
    _client.clear_con_listeners();
    delete ui;
}

void MainWindow::connectServer()
{
    _client.set_socket_open_listener([&](std::string const& nsp)
    {
        _lock.lock();
        _cond.notify_all();
        _connect_finish = true;
        _lock.unlock();
    });
    _client.set_socket_close_listener([&](std::string const& nsp){
        exit(0);
    });
    _client.set_reconnect_listener([&](unsigned test1, unsigned test2){
        exit(0);
    });

    _client.connect("wss://192.168.77.4:3000");

    sleep(1);

    _lock.lock();
    if(!_connect_finish)
    {
        _cond.wait(_lock);
    }
    _lock.unlock();

    _current_socket = _client.socket();

    QString nickname = "test";

    _current_socket->emit("add user", nickname.toStdString());

    _timer->start(500);
}

void MainWindow::getNewMessage()
{
    QString user;
    QString message;

    _current_socket->on("new message", sio::socket::event_listener_aux([&](string const& name, message::ptr const& data, bool isAck,message::list &ack_resp)
   {
        _lock.lock();
        user = QString::fromStdString(data->get_map()["username"]->get_string());
        message = QString::fromStdString(data->get_map()["message"]->get_string());
        Q_EMIT showNewMessageSignal(message, user);

        _lock.unlock();
   }));
}

void MainWindow::showNewMessage(const QString newMessage, const QString user)
{
    QByteArray bateArrayResult;
    QImage imageresult;
    if (newMessage.isEmpty())
        return;

    QDateTime dateTime = QDateTime::currentDateTime();
    QString strDataTime = dateTime.toString("yyyy.MM.dd hh:mm:ss.zzz");

    QString mUser = user.trimmed() + strDataTime + ":";
    _myQTextEdit->append(mUser);

    if ("base64::" == newMessage.mid(0, 8))
    {
        bateArrayResult = newMessage.mid(8).toUtf8();

        imageresult = base64_to_image(bateArrayResult).toImage();

        _base64Map.insert(mUser, bateArrayResult);

        imageresult = imageresult.scaled(100, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        QTextCursor cursor = _myQTextEdit->textCursor();

        cursor.movePosition(QTextCursor::End);
        cursor.insertText("\n");
        cursor.insertImage(imageresult);
    }
    else
    {
        _myQTextEdit->append(newMessage.trimmed());
//        _base64Map.insert(user, newMessage);

    }
    _myQTextEdit->moveCursor(QTextCursor::End);
}

void MainWindow::sendNewMessage(const QString newMessage)
{
    if(newMessage.length()>0)
    {
        _current_socket->emit("new message", newMessage.toStdString());
    }
}

void MainWindow::on_m_imageButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(ui->m_imageButton,tr("Open_Image"),"/home",tr("Image　Files(*)"));
    QImage * image= new QImage(path);

    QByteArray bateArrayResult;
    QPixmap imageresult;

    bateArrayResult = image_to_base64(*image);
    imageresult = base64_to_image(bateArrayResult);

    sendNewMessage("base64::" + QString::fromLocal8Bit(bateArrayResult));

    Q_EMIT showNewMessageSignal("base64::" + QString::fromLocal8Bit(bateArrayResult), "mine");
}

void MainWindow::on_m_sendButton_clicked()
{
    sendNewMessage(ui->m_inputTextEdit->toPlainText());

    Q_EMIT showNewMessageSignal(ui->m_inputTextEdit->toPlainText(), "mine");

    ui->m_inputTextEdit->clear();
}

void MainWindow::keyReleaseEvent( QKeyEvent * key )
{
    QString newMessage;
    if((Qt::Key_V == key->key()) && (Qt::ControlModifier == key->modifiers()))
    {
        newMessage = getDataFromShearPlate();

        sendNewMessage(newMessage);

        Q_EMIT showNewMessageSignal(newMessage, "mine");
    }
}

void MainWindow::showEnlargeImage( )
{
    QTextCursor cursor = _myQTextEdit->textCursor();
    QTextLayout * layout = cursor.block().layout();

    int nCurpos = cursor.position() - cursor.block().position();
    int nTextline = nTextline = layout->lineForTextPosition(nCurpos).lineNumber() + cursor.block().firstLineNumber();

    //get absolute position
    int pos = cursor.document()->findBlockByNumber(nTextline -1).position();

    //move to pos
    cursor.setPosition(pos, QTextCursor::MoveAnchor);

    //Select the whole line
    cursor.select(QTextCursor::LineUnderCursor);//选择

    _myQTextEdit->setTextCursor(cursor);

    QString senderInfo = cursor.selectedText();

    if (_base64Map.contains(senderInfo))
    {
        QDialog * myDialog = new QDialog(this);

        QDesktopWidget * desktopWidget = QApplication::desktop();

        QRect desktop = desktopWidget->availableGeometry();

        myDialog->resize(desktop.width()-80, desktop.height()-60);

        QLabel * myLabel = new QLabel();
        myLabel->setScaledContents(true);

        QGridLayout * myBoxLayout = new QGridLayout();

        myBoxLayout->addWidget(myLabel);

        myDialog->setLayout(myBoxLayout);

        QPixmap imageResult = base64_to_image(_base64Map.find(senderInfo).value());

        imageResult = imageResult.scaled(myDialog->geometry().size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        myLabel->setPixmap(imageResult);

        myDialog->move((desktopWidget->width()-myDialog->width())/2,(desktopWidget->height() - myDialog->height())/2);

        myDialog->show();
    }
    cursor.clearSelection();
    _myQTextEdit->setTextCursor(cursor);
}

QByteArray MainWindow::image_to_base64(const QImage image)
{

    QByteArray m_bateArray;

    QBuffer m_buffer(&m_bateArray);

    image.save(&m_buffer,"PNG",20);

    QByteArray bateArrayResult;

    bateArrayResult = m_bateArray.toBase64();

    m_buffer.close();

    return bateArrayResult;
}

QPixmap MainWindow::base64_to_image(const QByteArray base64)
{
    QByteArray Ret_bytearray;

    Ret_bytearray = QByteArray::fromBase64(base64);

    QBuffer buffer(&Ret_bytearray);

    buffer.open(QIODevice::WriteOnly);

    QPixmap imageresult;

    imageresult.loadFromData(Ret_bytearray);

    return imageresult;

}

QString MainWindow::getDataFromShearPlate()
{
    QImage m_image;

    if (_shearPlate->image().isNull())
    {
        return "";
    }

    while (1)
    {
        m_image = _shearPlate->image();
        if (!m_image.isNull())
        {
            break;
        }
    }

    QByteArray bateArrayResult;

    bateArrayResult = image_to_base64(m_image);

    return "base64::" + QString::fromLocal8Bit(bateArrayResult);
}
