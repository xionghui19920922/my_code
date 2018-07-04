#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include "datastructure.h"
#include "dataprocessing.h"
#include "dynamicallycreatingcontrol.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_m_import_add_clicked();

    void on_m_import_importButton_clicked();


    void on_m_import_for_txt_triggered();
    void on_m_import_for_json_triggered();

    void on_m_run_for_default_triggered();
    void on_m_run_for_json_triggered();
    void on_m_run_for_middle_triggered();

    void on_m_del_clicked();

    void on_m_selectImportPath_clicked();

    void on_m_selectExportPath_clicked();

private:
    Ui::MainWindow *ui;

    QList<DynamicallyCreatingControl *> m_listDynamicallyCreatingControl;

    dataProcessing * m_import_dataProcessing;

    void init();
    void sendData();



};

#endif // MAINWINDOW_H
