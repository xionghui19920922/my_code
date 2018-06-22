#include "dynamicallycreatingcontrol.h"

DynamicallyCreatingControl::DynamicallyCreatingControl(QObject *parent)
    :QObject(parent)
{
    createControl();
}

void DynamicallyCreatingControl::createControl()
{
    _keyName = new QLineEdit();
    _keyName->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _keyName->setStyleSheet("border-style:solid;");
    _keyName->setMaximumHeight(27);
    _keyName->setMinimumHeight(27);

    QFont font;
    font.setBold(true);
    _keyName->setFont(font);

    _equalName = new QLineEdit("=");
    _equalName->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _equalName->setStyleSheet("border-style:solid;");
    _equalName->setEnabled(false);
    _equalName->setFont(font);
    _equalName->setMaximumHeight(27);
    _equalName->setMinimumHeight(27);

    _valueName = new QLineEdit();
    _valueName->setStyleSheet("border-style:solid;");
    _valueName->setMaximumHeight(27);
    _valueName->setMinimumHeight(27);

    _buttonName = new QPushButton();
    _buttonName->setMaximumHeight(27);
    _buttonName->setMinimumHeight(27);
    _buttonName->setMinimumWidth(27);
    _buttonName->setMaximumWidth(27);
    _buttonName->setText("X");
    _buttonName->setStyleSheet("color:red;");


    connect(_buttonName, SIGNAL(clicked()), this, SLOT(deleteControl()));

}

void DynamicallyCreatingControl::deleteControl()
{
    _keyName->deleteLater();
    _equalName->deleteLater();
    _valueName->deleteLater();
    _buttonName->deleteLater();

    delete _keyName;
    _keyName = NULL;
    delete _equalName;
    _equalName = NULL;
    delete _valueName;
    _valueName = NULL;
    delete _buttonName;
    _buttonName = NULL;

    emit deleteSignal();
}
