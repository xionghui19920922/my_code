#ifndef MYQLABEL_H
#define MYQLABEL_H

#include <QTextEdit>
#include <QMouseEvent>
#include <QDebug>

class myQTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    myQTextEdit();

protected:
    void mouseDoubleClickEvent(QMouseEvent * event);

Q_SIGNALS:
    void clicked();

};

#endif // MYQLABEL_H
