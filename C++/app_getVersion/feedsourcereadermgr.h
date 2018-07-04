#ifndef FEEDSOURCEREADERMGR_H
#define FEEDSOURCEREADERMGR_H

#include <iostream>
#include <string>
#include <QString>
#include <QDir>
#include <QStringList>
#include <QDirIterator>
#include <QDebug>
#include "jsoncpp/json.h"
#include <fstream>
#include <jsoncpp/forwards.h>
#include <QFile>
#include <QFile>

using namespace std;

class IFeesReader {

};

class FeedSourceReaderMgr
{
public:
    static FeedSourceReaderMgr * getinstance();

    static IFeesReader * createReader(const QString &filePath);
private:
    IFeesReader* _createReader(const QString &source, const QString &version) {
        qDebug() << source;
        qDebug() << version;
        return nullptr;
    }

    FeedSourceReaderMgr();

    FeedSourceReaderMgr(const FeedSourceReaderMgr&);

    FeedSourceReaderMgr& operator=(const FeedSourceReaderMgr&);

    static FeedSourceReaderMgr * _instance;

    QString getFmtFilePath(const QString& filePath);

    void parseJson(const QString &filePath, QString &source, QString &version);
};

#endif // FEEDSOURCEREADERMGR_H
