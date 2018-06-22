#include "dataprocessing.h"

dataProcessing::dataProcessing()
{
}

dataProcessing::~dataProcessing()
{
}

//void dataProcessing::parsing_date(QString line, QList<QStringList> stationInfo)
//{
//    getConsoleData(line);
//    parsingProcess();
//}

void dataProcessing::clearData()
{
    stationInfo.clear();
    _middleResults.clear();
    _data.data.clear();
}

void dataProcessing::getConsoleData(QString line)
{
    QRegExp rx("(\=|\;)+");
    rx.setMinimal(false);

    QStringList list1 = line.split(rx,QString::SkipEmptyParts);
    QStringList list2;
    QString strSingle;
    QStringList::iterator i;

    for(i = list1.begin(); i != list1.end(); ++i)
    {
        strSingle = (*i).trimmed();
        list2.push_back(strSingle);
    }
    stationInfo.push_back(list2);
}

void dataProcessing::getFileData(QString inFileName, QList<QStringList> &stationInfo)
{
    //Open read-only file
    QFile file(inFileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can't open the file!";
        return ;
    }
    QTextStream in(&file);
    QString line;

    //Read all the data in the file
    while(!in.atEnd()){
        QRegExp rx("(\=|\;)+");
        rx.setMinimal(false);
        line = in.readLine();
        QStringList list1 = line.split(rx,QString::SkipEmptyParts);
        QStringList list2;
        QString strSingle;
        QStringList::iterator i;
        for(i = list1.begin(); i != list1.end(); ++i){
            strSingle = (*i).trimmed();
            list2.push_back(strSingle);
        }
        stationInfo.push_back(list2);
    }
    file.close();
}

void dataProcessing::analyticalData(QStringList &tempList)
{
    QRegExp rx("range[(]+[\\s]*(\-)?[\\d]+(\.?[\\d]+)?[\\s]*,[\\s]*(\-)?[\\d]+(\.?[\\d]+)?[\\s]*,[\\s]*(\-)?[\\d]+(\.?[\\d]+)?[\\s]*[)]+");
    QRegExp zx("[\\s]*[(a-z)|(A-Z)][\\s]*[~][\\s]*[(a-z)|(A-Z)][\\s]*[:]+[\\s]*(\-)?[\\d]+[\\s]*");
    QRegExp mx("range[(]+[\\s]*[(a-z)|(A-Z)]+[\\s]*,[\\s]*[(a-z)|(A-Z)]+[\\s]*,[\\s]*(\-)?[\\d]+[\\s]*[)]");
    QRegExp sx("[\\s]*(\-)?[\\d]+(\.?[\\d]+)?[\\s]*[~][\\s]*(\-)?[\\d]+(\.?[\\d]+)?[\\s]*[\\:]+[\\s]*(\-)?[\\d]+(\.?[\\d]+)?[\\s]*");
    QRegExp dx("[\\.]+");
    QStringList::iterator strk;

    //Traverse all the data
    struct LineData lineTemp;
    struct LineData lineSave;
    for(strk = (tempList).begin(); strk != (tempList).end(); ++strk){
//        int n=0;
        if(strk == (tempList).begin()){
            lineTemp.name = *strk;
        } else if(rx.indexIn(*strk) != -1){
            QString str,str1,str2,str3;
            str = rx.cap(0);
            str = str.right(str.length()-6);
            str = str.left(str.length()-1);
            QStringList list = str.split(",",QString::SkipEmptyParts);
            str1 = list.at(0).trimmed();
            str2 = list.at(1).trimmed();
            str3 = list.at(2).trimmed();
            lineTemp.line += matchNumber(*strk,str1,str2,str3);
        } else if(mx.indexIn(*strk) != -1){
            QString str,str1,str2,str3;
            str = mx.cap(0);
            str = str.right(str.length()-6);
            str = str.left(str.length()-1);
            QStringList list = str.split(",",QString::SkipEmptyParts);
            str1 = list.at(0).trimmed();
            str2 = list.at(1).trimmed();
            str3 = list.at(2).trimmed();
            lineTemp.line += matchString(*strk,str1,str2,str3);
        } else if(sx.indexIn(*strk) != -1){
            QString str,str1,str2,str3,strTemp;
            str = sx.cap(0);
            int index1 = str.indexOf("~");
            int index2 = str.indexOf(":");
            str1 = str.left(index1).trimmed();
            strTemp = str.left(index2);
            str2 = strTemp.right(strTemp.length()-index1-1).trimmed();
            str3 = str.right(str.length()-index2-1).trimmed();
            lineTemp.line += matchNumber(*strk,str1,str2,str3);
        } else if(zx.indexIn(*strk) != -1){
            QString str,str1,str2,str3,strTtemp;
            str = zx.cap(0);
            int index1 = str.indexOf("~");
            int index2 = str.indexOf(":");
            str1 = str.left(index1).trimmed();
            strTtemp = str.left(index2);
            str2 = strTtemp.right(strTtemp.length()-index1-1).trimmed();
            str3 = str.right(str.length()-index2-1).trimmed();
            lineTemp.line += matchString(*strk,str1,str2,str3);
        } else if(isInteger(*strk)){
            if(dx.indexIn(*strk) != -1){
                lineTemp.line.append(QVariant(*strk).toDouble());
            } else{
                lineTemp.line.append(QVariant(*strk).toInt());
            }
        } else{
            lineSave.line.append(QVariant(*strk));
         }
    }
    lineSave.name = lineTemp.name;
    lineSave.line += lineTemp.line;
    _data.data.push_back(lineSave);
}

QList<QVariant> dataProcessing::matchNumber(QString &str, QString &begNum, QString &endNum, QString &interval)
{
    QRegExp dx("[\\.]+");
    LineData lineTemp;
    int n=0;
    if((dx.indexIn(begNum) != -1) || (dx.indexIn(endNum) != -1) || (dx.indexIn(interval) != -1)){
        double strBeg = begNum.toDouble();
        double strAdd = interval.toDouble();
        double strEnd = endNum.toDouble();
        if(strAdd >0 && strBeg < strEnd){
            if(strBeg >= strEnd-strAdd){
                lineTemp.line.append(QVariant(strBeg));
                return lineTemp.line;
            }
            while(strEnd - strBeg - strAdd > 0.0000000001){
                if(n==0){
                    lineTemp.line.append(QVariant(strBeg));
                    n++;
                }
                strBeg += strAdd;
                if (strBeg > -0.0000000001 && strBeg < 0.0000000001) {
                    lineTemp.line.append(QVariant(0));
                } else {
                    lineTemp.line.append(QVariant(strBeg));
                }
            }
            return lineTemp.line;
        } else if(strAdd < 0 && strBeg > strEnd){
            if(strBeg <= strEnd-strAdd){
                lineTemp.line.append(QVariant(strBeg));
                return lineTemp.line;
            }
            while(strBeg > (strEnd-strAdd)){
                if(n==0){
                    lineTemp.line.append(QVariant(strBeg));
                    n++;
                }
                strBeg += strAdd;
                lineTemp.line.append(QVariant(strBeg));
            }
            return lineTemp.line;
        } else{
            lineTemp.line.append(QVariant(str));
            return lineTemp.line;
        }
    } else{
        int strBeg = begNum.toInt(0,10);
        int strAdd = interval.toInt(0,10);
        int strEnd = endNum.toInt(0,10);
        if(strAdd > 0 && strBeg < strEnd){
            if(strBeg >= strEnd-strAdd){
                lineTemp.line.append(QVariant(strBeg));
                return lineTemp.line;
            }
            while(strBeg < strEnd-strAdd){
                if(n==0){
                    lineTemp.line.append(QVariant(strBeg));
                    n++;
                }
                strBeg += strAdd;
                lineTemp.line.append(QVariant(strBeg));
            }
            return lineTemp.line;
        } else if(strAdd < 0 && strBeg > strEnd){
            if(strBeg <= strEnd-strAdd){
                lineTemp.line.append(QVariant(strBeg));
                return lineTemp.line;
            }
            while(strBeg > strEnd-strAdd){
                if(n==0){
                    lineTemp.line.append(QVariant(strBeg));
                    n++;
                }
                strBeg += strAdd;
                lineTemp.line.append(QVariant(strBeg));
            }
            return lineTemp.line;
        } else{
            lineTemp.line.append(QVariant(str));
            return lineTemp.line;
        }
    }
}

QList<QVariant> dataProcessing::matchString(QString &str, QString &begStr, QString &endStr, QString &interval)
{
    int n=0;
    LineData lineTemp;
    QChar strBeg = begStr[0];
    QChar strEnd = endStr[0];
    char stra = strBeg.toAscii();
    char strb = strEnd.toAscii();
    int strAdd = interval.toInt(0,10);
    if(strAdd > 0 && stra < strb){
        if(stra >= strb-strAdd){
            lineTemp.line.append(QVariant(QString(stra)));
            return lineTemp.line;
        }
        while(stra < strb-1){
            if(n == 0){
                lineTemp.line.append(QVariant(QString(stra)));
                n++;
            }
            stra += strAdd;
            lineTemp.line.append(QVariant(QString(stra)));
        }
        return lineTemp.line;
    }
    else if(strAdd < 0 && stra > strb){
        if(stra <= strb-strAdd){
            lineTemp.line.append(QVariant(QString(stra)));
            return lineTemp.line;
        }
        while(stra > strb+1){
            if(n == 0){
                lineTemp.line.append(QVariant(QString(stra)));
                n++;
            }
            stra += strAdd;
            lineTemp.line.append(QVariant(QString(stra)));
        }
        return lineTemp.line;
    } else{
        lineTemp.line.append(QVariant(str));
        return lineTemp.line;
    }
}

bool dataProcessing::isInteger(QString strNum)
{
    QRegExp hx("[0-9]|[\\.]");
    QRegExp dx("[\\.]+");
    for(int i = 0; i < strNum.count(); ++i){
        if((i == 0) && (dx.indexIn(strNum.at(i)) != -1)){
            return false;
        } else if((i == strNum.count()-1) && (dx.indexIn(strNum.at(i)) != -1)){
            return false;
        }
        if(hx.indexIn(strNum.at(i)) == -1){
            return false;
        }
    }
    return true;
}

void dataProcessing::getFileData(QString inPathName)
{
    //Open read-only file
    QFile file(inPathName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return ;
    }
    QTextStream in(&file);
    QString line;

    //Read all the data in the file
    while(!in.atEnd()){
        QRegExp rx("(\=|\;)+");
        rx.setMinimal(false);
        line = in.readLine();
        QStringList list1 = line.split(rx,QString::SkipEmptyParts);
        QStringList list2;
        QString strSingle;
        QStringList::iterator i;
        for(i = list1.begin(); i != list1.end(); ++i){
            strSingle = (*i).trimmed();
            list2.push_back(strSingle);
        }
        stationInfo.push_back(list2);
    }
    file.close();
}

void dataProcessing::toHeavy()
{
    QList<QVariant>::iterator j,k;
    QList<LineData>::iterator i;
    struct Data dataTemp;
    int n = 0;
    for(i = _data.data.begin(); i != _data.data.end(); ++i){
        n++;
        struct LineData lineTemp;
        for(j = (*i).line.begin(); j != (*i).line.end()-1; ++j){
            bool single = true;
            for(k = j+1; k != (*i).line.end(); ++k){
                if(((*j).typeName() == QString("int")) && ((*k).typeName() == QString("int"))){
                    if((*j).toInt() == (*k).toInt()){
                        single = false;
                        break;
                    }
                } else if(((*j).typeName() == QString("double")) && ((*k).typeName() == QString("double"))){
                    if((*j).toDouble() == (*k).toDouble()){
                        single = false;
                        break;
                    }
                } else if(((*j).typeName() == QString("QString")) && ((*k).typeName() == QString("QString"))){
                    if((*j).toString() == (*k).toString()){
                        single = false;
                        break;
                    }
                } else{
                    single = true;
                }
            }
            if(single == true){
                lineTemp.line.append(*j);
            }
        }
        lineTemp.name = (*i).name;
        lineTemp.line.append(*j);
        dataTemp.data.append(lineTemp);
    }
    _data.data = dataTemp.data;
}

void dataProcessing::parsingProcess()
{
    QList<QStringList>::iterator stri;
    for(stri = stationInfo.begin(); stri != stationInfo.end(); ++stri){
        analyticalData(*stri);
    }
    toHeavy();
}

void dataProcessing::middleDataOut()
{
    QStringList result;
    QList<QVariant>::iterator k;
    QList<LineData>::iterator i;
    for(i = _data.data.begin(); i != _data.data.end(); ++i){
        QStringList middleTemp;
        middleTemp << (*i).name << "=";
        for(k = (*i).line.begin(); k != (*i).line.end(); ++k){
            if(k == (*i).line.end()-1){
                middleTemp << (*k).toString();
            }
            else{
                middleTemp << (*k).toString() << ",";
            }
        }
        result.append(middleTemp.join(""));
    }
    _middleResults.append(result);
}

QStringList dataProcessing::getFinalData(FORMAT format)
{
    struct Data dataTemp;
    QList<LineData>::iterator i;
    int strCount = 1;

    for(i = _data.data.begin(); i != _data.data.end(); ++i){
        strCount *= (*i).line.count();
    }
    int strRows = _data.data.count();
    QVector<int> strCols(strRows,0);
    for(int r = 0; r < strCount; ++r){
        bool flag = true;
        struct LineData lineTemp;
        for(int i = strRows-1; i >= 0; i--){
            QVariant var = getVariant(_data.data[i].line,_data.data[i].line.count(),i,strCols,flag);
            lineTemp.line.push_front(var);
        }

        dataTemp.data.append(lineTemp);
    }

    if(format == JSON){
        return toJsonData(dataTemp);
    } else if(format == DEFAULT){
        return toDefaultData(dataTemp);
    }
    return QStringList();
}

QStringList dataProcessing::toJsonData(struct Data &dataTemp)
{
    QList<QVariant>::iterator j;
    QList<LineData>::iterator i;
    QStringList result;
    //Result resultMap;
    for(i = dataTemp.data.begin(); i != dataTemp.data.end(); ++i){
        QStringList finalTemp;
        int n = 0;
        finalTemp << "\{";
        for(j = (*i).line.begin(); j != (*i).line.end(); ++j){
            if(j != (*i).line.end()-1){
                if((*j).typeName() == QString("int")){
                    finalTemp << "\"" << _data.data[n].name << "\"" << ":" << (*j).toString() << ", ";
                    //resultMap .line.insert(_data.data[n].name,(*j).toInt());
                }
                else if((*j).typeName() == QString("double")){
                    finalTemp << "\"" << _data.data[n].name<< "\"" << ":" << (*j).toString() << ", ";
                }
                else if((*j).typeName() == QString("QString")){
                    finalTemp << "\"" << _data.data[n].name << "\"" << ":" << "\"" << (*j).toString() << "\"" << ", ";
                }
            }
            else{
                if((*j).typeName() == QString("int")){
                    finalTemp << "\"" << _data.data[n].name << "\"" << ":" << (*j).toString();
                }
                else if((*j).typeName() == QString("double")){
                    finalTemp << "\"" << _data.data[n].name<< "\"" << ":" << (*j).toString();
                }
                else if((*j).typeName() == QString("QString")){
                    finalTemp << "\"" << _data.data[n].name << "\"" << ":" << "\"" << (*j).toString() << "\"";
                }
            }
            ++n;
        }
        finalTemp << "\}";
        result.append(finalTemp.join(""));
//        _finalResults.append(finalTemp);
    }
    return result;
}

QStringList dataProcessing::toDefaultData(struct Data &dataTemp)
{
    QList<QVariant>::iterator j;
    QList<LineData>::iterator i;
    QStringList result;
    for(i = dataTemp.data.begin(); i != dataTemp.data.end(); ++i){
        QStringList finalTemp;
        int n = 0;
        for(j = (*i).line.begin(); j != (*i).line.end(); ++j){
            if(j != (*i).line.end()-1){
                if((*j).typeName() == QString("int")){
                    finalTemp << _data.data[n].name << "=" << (*j).toString() << ", ";
                }
                else if((*j).typeName() == QString("double")){
                    finalTemp << _data.data[n].name << "=" << (*j).toString() << ", ";
                }
                else if((*j).typeName() == QString("QString")){
                    finalTemp << _data.data[n].name << "=" << (*j).toString() << ", ";
                }
            }
            else{
                if((*j).typeName() == QString("int")){
                    finalTemp << _data.data[n].name << "=" << (*j).toString();
                }
                else if((*j).typeName() == QString("double")){
                    finalTemp << _data.data[n].name << "=" << (*j).toString();
                }
                else if((*j).typeName() == QString("QString")){
                    finalTemp << _data.data[n].name << "=" << (*j).toString();
                }
            }
            ++n;
        }

        result.append(finalTemp.join(""));

//        _finalResults.append(finalTemp);
    }
    return result;
}

QVariant dataProcessing::getVariant(QList<QVariant> &line, int len, int index, QVector<int> &cols, bool &flag)
{
    QVariant var;
    if(flag){
        var = line[cols[index]++];
        if(cols[index] >= len){
            flag = true;
            cols[index] = 0;
            return var;
        }
        else {
            flag = false;
            return var;
        }
    }
    var = line[cols[index]];
    return var;
}

void dataProcessing::outputFinalData(QString outPathName, FORMAT format)
{

    QFile file(outPathName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::about(this,tr("Hint information"),tr("Can't open the file!"));
        return;
    }
    QTextStream stream(&file);
    QStringList finalList;
    finalList = getFinalData(format);
    for(const QString &str : finalList){
        stream << str << "\n";
    }

    QMessageBox::about(this,tr("Hint information"),tr("Export success!"));

    file.close();
}


