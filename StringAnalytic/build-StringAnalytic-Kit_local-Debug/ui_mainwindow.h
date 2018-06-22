/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *m_import_path;
    QToolButton *m_selectImportPath;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *m_import_importButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *m_import_keyLayout;
    QLabel *label_4;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *m_import_equalLayout;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *m_import_valueLayout;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *m_import_buttonLayout;
    QLabel *label_7;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *m_import_add;
    QSpacerItem *horizontalSpacer_15;
    QToolButton *m_import_run;
    QSpacerItem *horizontalSpacer_3;
    QTextEdit *m_import_text;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *m_import_export_path;
    QToolButton *m_selectExportPath;
    QSpacerItem *horizontalSpacer_11;
    QToolButton *m_import_toobutton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(551, 593);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(400, 400));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_import_path = new QLineEdit(centralWidget);
        m_import_path->setObjectName(QString::fromUtf8("m_import_path"));
        m_import_path->setMinimumSize(QSize(0, 27));
        m_import_path->setStyleSheet(QString::fromUtf8("border-style:solid;"));

        horizontalLayout_5->addWidget(m_import_path);

        m_selectImportPath = new QToolButton(centralWidget);
        m_selectImportPath->setObjectName(QString::fromUtf8("m_selectImportPath"));
        m_selectImportPath->setMinimumSize(QSize(27, 27));
        m_selectImportPath->setMaximumSize(QSize(27, 27));

        horizontalLayout_5->addWidget(m_selectImportPath);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        m_import_importButton = new QPushButton(centralWidget);
        m_import_importButton->setObjectName(QString::fromUtf8("m_import_importButton"));

        horizontalLayout_5->addWidget(m_import_importButton);

        horizontalLayout_5->setStretch(0, 10);
        horizontalLayout_5->setStretch(2, 1);
        horizontalLayout_5->setStretch(3, 2);

        verticalLayout_8->addLayout(horizontalLayout_5);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setStyleSheet(QString::fromUtf8("border-style:solid;"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 531, 217));
        horizontalLayout_7 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_import_keyLayout = new QVBoxLayout();
        m_import_keyLayout->setSpacing(6);
        m_import_keyLayout->setObjectName(QString::fromUtf8("m_import_keyLayout"));
        m_import_keyLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        m_import_keyLayout->setContentsMargins(0, -1, -1, -1);
        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font;
        font.setPointSize(9);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);

        m_import_keyLayout->addWidget(label_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_import_keyLayout->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(m_import_keyLayout);

        m_import_equalLayout = new QVBoxLayout();
        m_import_equalLayout->setSpacing(6);
        m_import_equalLayout->setObjectName(QString::fromUtf8("m_import_equalLayout"));
        label_5 = new QLabel(scrollAreaWidgetContents);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        m_import_equalLayout->addWidget(label_5);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_import_equalLayout->addItem(verticalSpacer_6);


        horizontalLayout_4->addLayout(m_import_equalLayout);

        m_import_valueLayout = new QVBoxLayout();
        m_import_valueLayout->setSpacing(6);
        m_import_valueLayout->setObjectName(QString::fromUtf8("m_import_valueLayout"));
        label_6 = new QLabel(scrollAreaWidgetContents);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(16777215, 16777215));
        label_6->setAlignment(Qt::AlignCenter);

        m_import_valueLayout->addWidget(label_6);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_import_valueLayout->addItem(verticalSpacer_2);


        horizontalLayout_4->addLayout(m_import_valueLayout);

        m_import_buttonLayout = new QVBoxLayout();
        m_import_buttonLayout->setSpacing(6);
        m_import_buttonLayout->setObjectName(QString::fromUtf8("m_import_buttonLayout"));
        label_7 = new QLabel(scrollAreaWidgetContents);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        m_import_buttonLayout->addWidget(label_7);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        m_import_buttonLayout->addItem(verticalSpacer_5);


        horizontalLayout_4->addLayout(m_import_buttonLayout);

        horizontalLayout_4->setStretch(0, 6);
        horizontalLayout_4->setStretch(1, 3);
        horizontalLayout_4->setStretch(2, 24);
        horizontalLayout_4->setStretch(3, 3);

        horizontalLayout_7->addLayout(horizontalLayout_4);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_8->addWidget(scrollArea);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_13);

        m_import_add = new QPushButton(centralWidget);
        m_import_add->setObjectName(QString::fromUtf8("m_import_add"));

        horizontalLayout_3->addWidget(m_import_add);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_15);

        m_import_run = new QToolButton(centralWidget);
        m_import_run->setObjectName(QString::fromUtf8("m_import_run"));
        m_import_run->setMinimumSize(QSize(85, 27));
        m_import_run->setPopupMode(QToolButton::InstantPopup);

        horizontalLayout_3->addWidget(m_import_run);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_8->addLayout(horizontalLayout_3);

        m_import_text = new QTextEdit(centralWidget);
        m_import_text->setObjectName(QString::fromUtf8("m_import_text"));
        m_import_text->setEnabled(true);
        m_import_text->setStyleSheet(QString::fromUtf8("border-style:solid;\n"
"background-color:white;"));

        verticalLayout_8->addWidget(m_import_text);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        m_import_export_path = new QLineEdit(centralWidget);
        m_import_export_path->setObjectName(QString::fromUtf8("m_import_export_path"));
        m_import_export_path->setMinimumSize(QSize(0, 27));
        m_import_export_path->setStyleSheet(QString::fromUtf8("border-style:solid;"));

        horizontalLayout_8->addWidget(m_import_export_path);

        m_selectExportPath = new QToolButton(centralWidget);
        m_selectExportPath->setObjectName(QString::fromUtf8("m_selectExportPath"));
        m_selectExportPath->setMinimumSize(QSize(27, 27));
        m_selectExportPath->setMaximumSize(QSize(27, 27));

        horizontalLayout_8->addWidget(m_selectExportPath);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_11);

        m_import_toobutton = new QToolButton(centralWidget);
        m_import_toobutton->setObjectName(QString::fromUtf8("m_import_toobutton"));
        QFont font1;
        font1.setPointSize(11);
        m_import_toobutton->setFont(font1);
        m_import_toobutton->setPopupMode(QToolButton::InstantPopup);
        m_import_toobutton->setAutoRaise(false);
        m_import_toobutton->setArrowType(Qt::NoArrow);

        horizontalLayout_8->addWidget(m_import_toobutton);

        horizontalLayout_8->setStretch(0, 10);
        horizontalLayout_8->setStretch(2, 1);
        horizontalLayout_8->setStretch(3, 2);

        verticalLayout_8->addLayout(horizontalLayout_8);

        verticalLayout_8->setStretch(0, 2);
        verticalLayout_8->setStretch(1, 12);
        verticalLayout_8->setStretch(2, 3);
        verticalLayout_8->setStretch(3, 8);
        verticalLayout_8->setStretch(4, 2);

        horizontalLayout->addLayout(verticalLayout_8);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 551, 27));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        m_selectImportPath->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        m_import_importButton->setText(QApplication::translate("MainWindow", "Import", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "key", 0, QApplication::UnicodeUTF8));
        label_5->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "value", 0, QApplication::UnicodeUTF8));
        label_7->setText(QString());
        m_import_add->setText(QApplication::translate("MainWindow", "Add", 0, QApplication::UnicodeUTF8));
        m_import_run->setText(QApplication::translate("MainWindow", "Run", 0, QApplication::UnicodeUTF8));
        m_selectExportPath->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        m_import_toobutton->setText(QApplication::translate("MainWindow", "  Export  ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
