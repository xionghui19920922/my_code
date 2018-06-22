#include "feedsourcereadermgr.h"

FeedSourceReaderMgr* FeedSourceReaderMgr::_instance = new FeedSourceReaderMgr();
FeedSourceReaderMgr* FeedSourceReaderMgr::getinstance(){
    return _instance;
}

FeedSourceReaderMgr::FeedSourceReaderMgr()
{

}

IFeesReader * FeedSourceReaderMgr::createReader(const QString &filePath)
{
    QString ltqFmtPath = _instance->getFmtFilePath(filePath);

    if (!ltqFmtPath.isEmpty())
    {
        QString source, version;

        _instance->parseJson(ltqFmtPath, source, version);

        return _instance->_createReader(source, version);
    }
    else
    {
        return nullptr;
    }
}

QString FeedSourceReaderMgr::getFmtFilePath(const QString& filePath)
{
    if (filePath.isEmpty()) {
        return "";
    }

    QString mFilePath = filePath;

    QString mFilePathTmp;

    if (QFile(mFilePath + ".fmt").exists()) {
        return mFilePath + ".fmt";
    }

    do
    {
        QFileInfo fileInfo(mFilePath);

        QString fileFmtPath = fileInfo.absoluteDir().path() + "/.ltq.fmt";

        if (QFile(fileFmtPath).exists()) {
            return fileFmtPath;
        }
        mFilePathTmp = mFilePath;
        mFilePath = QFileInfo(mFilePath).absoluteDir().path();

    }while (mFilePath != mFilePathTmp);

    return "";
}

void FeedSourceReaderMgr::parseJson(const QString &filePath, QString &source, QString &version)
{

    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Open failed";
        return;
    }

    QTextStream txtInput(&file);
    QString lineStr;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readAll();
    }

    file.close();

    Json::Value root;
    Json::Reader reader;

    lineStr.replace('"','\"');

    if(!reader.parse(lineStr.toStdString(), root))
    {
       qDebug() << "open file error!";
       return;
    }
    else
    {
        source = QString::fromStdString(root["source"].asString());
        version = QString::fromStdString(root["version"].asString());
    }
}

