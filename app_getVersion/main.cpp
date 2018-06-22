#include <QCoreApplication>
#include <iostream>
#include <string>
#include "feedsourcereadermgr.h"
#include <QString>

using namespace  std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString filePath;

    filePath = "/home/test/my_Code/app_getVersion/test.ltq";

    FeedSourceReaderMgr * feedsourcereadermgr = FeedSourceReaderMgr::getinstance();

    feedsourcereadermgr->createReader(filePath);

    return a.exec();
}
