#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QVariant>

struct LineData{
    QString name;
    QList<QVariant> line;
};

struct Data{
    QList<LineData> data;
};

/*
struct Result{
    QMap<QString, QVariant> line;
};

struct ResultList{
    QList<Result> data;
};
*/

#endif // DATASTRUCTURE_H
