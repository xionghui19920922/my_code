#include "myqtextedit.h"

myQTextEdit::myQTextEdit()
{

}

void myQTextEdit::mouseDoubleClickEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
        Q_EMIT clicked();
}

