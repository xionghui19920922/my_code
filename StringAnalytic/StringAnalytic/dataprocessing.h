#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <QTextStream>
#include <iostream>
#include <QChar>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QVariant>
#include <QVariantList>
#include <QMap>
#include <QMessageBox>
#include <QMainWindow>

#include "datastructure.h"

enum FORMAT {DEFAULT, JSON, XML};

class dataProcessing :public QMainWindow
{
public:

    dataProcessing();
    ~dataProcessing();
    void init(const QStringList &inputData);

    //Parsing special format data
    void analyticalData(QStringList &tempList);

    void getConsoleData(QString line);

    Data getData() {return this->_data;}
    QStringList getMiddleData() const {return this->_middleResults;}
    QList<QStringList> getStationInfo(){return this->stationInfo;}

//    void parsing_date(QString line, QList<QStringList> stationInfo);

    void parsingProcess();

    void middleDataOut();

    //Get file data
    void getFileData(QString inFileName);

    QStringList getFinalData(FORMAT format = FORMAT::DEFAULT);

    void outputFinalData(QString outPathName, FORMAT format);

//    void outputMiddleData(QString outFileName);



    void clearData();


private:

    //Weight each row of data
    void toHeavy();

    //Get file data
    void getFileData(QString inFileName, QList<QStringList> &stationInfo);

    //Determine whether an integer is an integer
    bool isInteger(QString strNum);

    //Matches an extended format with a number
    QList<QVariant> matchNumber(QString &str, QString &begNum, QString &endNum, QString &interval);

    //Matches an extended format with a letters
    QList<QVariant> matchString(QString &str, QString &begStr, QString &endStr, QString &interval);

    //Output json format data
    QStringList toJsonData(Data &dataTemp);

    //Output data in default format
    QStringList toDefaultData(Data &dataTemp);


    //Get file data
    QVariant getVariant(QList<QVariant> &line, int len, int index, QVector<int> &cols, bool &flag);

    QList<QStringList> stationInfo;
    QStringList _middleResults;
    Data _data;


};

#endif // DATAPROCESSING_H
