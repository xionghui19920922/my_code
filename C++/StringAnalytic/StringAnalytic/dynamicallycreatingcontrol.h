#ifndef DYNAMICALLYCREATINGCONTROL_H
#define DYNAMICALLYCREATINGCONTROL_H


#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "datastructure.h"
#include "dataprocessing.h"
#include <QObject>

class DynamicallyCreatingControl : public QObject
{
    Q_OBJECT

public:
    DynamicallyCreatingControl(QObject *parent = 0);

    QLineEdit * getKeyName() {return _keyName;}
    QLineEdit * getEqualName() {return _equalName;}
    QLineEdit * getValueName() {return _valueName;}
    QPushButton * getButtonName() {return _buttonName;}

signals:
    void deleteSignal();

public slots:
    void deleteControl();

private:

    QLineEdit * _keyName;
    QLineEdit * _equalName;
    QLineEdit * _valueName;
    QPushButton * _buttonName;

    void createControl();
};

#endif // DYNAMICALLYCREATINGCONTROL_H
