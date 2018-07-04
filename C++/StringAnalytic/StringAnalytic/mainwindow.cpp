#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    Qt::WindowFlags flags = 0;
//    //flags |= Qt::WindowCloseButtonHint;
//    setWindowFlags(flags);
//    setFixedSize(502,435);

    ui->m_import_text->setReadOnly(true);

    m_import_dataProcessing = new dataProcessing();
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{

    on_m_import_add_clicked();

    //import import begin
    QMenu * m_menu_import = new QMenu(this);
    QAction * import_action_txt = new QAction("&DEFAULT", this);
    QAction * import_action_json = new QAction("&JSON", this);

    m_menu_import->addAction(import_action_txt);
    m_menu_import->addAction(import_action_json);

    ui->m_import_toobutton->setMenu(m_menu_import);

    connect(import_action_txt, SIGNAL(triggered()), this, SLOT(on_m_import_for_txt_triggered()));
    connect(import_action_json, SIGNAL(triggered()), this, SLOT(on_m_import_for_json_triggered()));
    //import import end

    //import Run begin
    QMenu * m_menu_import_run = new QMenu(this);
    QAction * import_action_run_default = new QAction("&DEFAULT", this);
    QAction * import_action_run_json = new QAction("&JSON", this);
    QAction * import_action_run_middle = new QAction("&MIDDLE", this);


    m_menu_import_run->addAction(import_action_run_default);
    m_menu_import_run->addAction(import_action_run_json);
    m_menu_import_run->addAction(import_action_run_middle);

    ui->m_import_run->setMenu(m_menu_import_run);

    connect(import_action_run_default, SIGNAL(triggered()), this, SLOT(on_m_run_for_default_triggered()));
    connect(import_action_run_json, SIGNAL(triggered()), this, SLOT(on_m_run_for_json_triggered()));
    connect(import_action_run_middle, SIGNAL(triggered()), this, SLOT(on_m_run_for_middle_triggered()));
    //import Run end

}

//import_begin

void MainWindow::on_m_import_add_clicked()
{
    DynamicallyCreatingControl * m_DynamicallyCreatingControl = new DynamicallyCreatingControl();

    m_listDynamicallyCreatingControl.append(m_DynamicallyCreatingControl);

    ui->m_import_keyLayout->addWidget(m_DynamicallyCreatingControl->getKeyName());
    ui->m_import_equalLayout->addWidget(m_DynamicallyCreatingControl->getEqualName());
    ui->m_import_valueLayout->addWidget(m_DynamicallyCreatingControl->getValueName());
    ui->m_import_buttonLayout->addWidget(m_DynamicallyCreatingControl->getButtonName());

    connect(m_DynamicallyCreatingControl, SIGNAL(deleteSignal()), this, SLOT(on_m_del_clicked()));

}

void MainWindow::on_m_import_importButton_clicked()
{
    m_import_dataProcessing->clearData();

    QString string_path;
    QString stringl_out;
    QList<QStringList>  data_stringlist;
    QStringList data_text_string_list;
    QList<QStringList>::const_iterator const_iter;

    string_path = ui->m_import_path->text();

    m_import_dataProcessing->getFileData(string_path);

    m_import_dataProcessing->parsingProcess();

    //key and value      begin
    data_stringlist = m_import_dataProcessing->getStationInfo();

    for(int i = 1; i < data_stringlist.size(); i++)
    {
        on_m_import_add_clicked();
    }

    QString temp_string;
    int h = 0;;

    for (const_iter = data_stringlist.begin();const_iter != data_stringlist.end(); const_iter++)
    {
        temp_string = "";

        for(int k = 1; k < (*const_iter).size(); k++)
        {
            temp_string += (*const_iter)[k];
            temp_string += ";";
        }

        if ((m_listDynamicallyCreatingControl[h])->getKeyName()->text().isEmpty() && (m_listDynamicallyCreatingControl[h])->getValueName()->text().isEmpty())
        {
            (m_listDynamicallyCreatingControl[h])->getKeyName()->setText((*const_iter)[0]);
            (m_listDynamicallyCreatingControl[h])->getValueName()->setText(temp_string);
        }
        h++;

    }

    //key and value      end


    //m_import_text   begin
    m_import_dataProcessing->middleDataOut();

    data_text_string_list = m_import_dataProcessing->getMiddleData();

    for (int i = 0; i < data_text_string_list.size(); i++)
    {
        stringl_out += data_text_string_list[i];
        stringl_out += "\n";
    }

    ui->m_import_text->clear();
    ui->m_import_text->setText(stringl_out);
    //m_import_text   end

}

//import_end

void MainWindow::on_m_import_for_txt_triggered()
{
    m_import_dataProcessing->outputFinalData(ui->m_import_export_path->text(),FORMAT::DEFAULT);
}

void MainWindow::on_m_import_for_json_triggered()
{
    m_import_dataProcessing->outputFinalData(ui->m_import_export_path->text(),FORMAT::JSON);
}

void MainWindow::on_m_run_for_default_triggered()
{
    QString stringl_out;
    QStringList data_stringlist;

    sendData();

    m_import_dataProcessing->parsingProcess();

    m_import_dataProcessing->middleDataOut();

    data_stringlist = m_import_dataProcessing->getFinalData(FORMAT::DEFAULT);

    for (int i = 0; i < data_stringlist.size(); i++)
    {
        stringl_out += data_stringlist[i];
        stringl_out += "\n";
    }

    ui->m_import_text->clear();
    ui->m_import_text->setText(stringl_out);
}

void MainWindow::on_m_run_for_json_triggered()
{
    QString stringl_out;
    QStringList data_stringlist;

    sendData();

    m_import_dataProcessing->parsingProcess();

    m_import_dataProcessing->middleDataOut();

    data_stringlist = m_import_dataProcessing->getFinalData(FORMAT::JSON);

    for (int i = 0; i < data_stringlist.size(); i++)
    {
        stringl_out += data_stringlist[i];
        stringl_out += "\n";
    }

    ui->m_import_text->clear();
    ui->m_import_text->setText(stringl_out);
}

void MainWindow::on_m_run_for_middle_triggered()
{
    QString stringl_out;
    QStringList data_stringlist;

    sendData();

    m_import_dataProcessing->parsingProcess();

    m_import_dataProcessing->middleDataOut();

    data_stringlist = m_import_dataProcessing->getMiddleData();

    for (int i = 0; i < data_stringlist.size(); i++)
    {
        stringl_out += data_stringlist[i];
        stringl_out += "\n";
    }

    ui->m_import_text->clear();
    ui->m_import_text->setText(stringl_out);
}

void MainWindow::sendData()
{
    QString string_each_line;
    m_import_dataProcessing->clearData();

    for (int i = 0; i < m_listDynamicallyCreatingControl.size(); i++)
    {
        if (NULL == (m_listDynamicallyCreatingControl[i])->getKeyName())
            continue;

        if (!((m_listDynamicallyCreatingControl[i])->getKeyName()->text().isEmpty()||(m_listDynamicallyCreatingControl[i])->getValueName()->text().isEmpty()))
        {
            string_each_line = "";
            string_each_line += (m_listDynamicallyCreatingControl[i])->getKeyName()->text();
            string_each_line += (m_listDynamicallyCreatingControl[i])->getEqualName()->text();;
            string_each_line += (m_listDynamicallyCreatingControl[i])->getValueName()->text();
            m_import_dataProcessing->getConsoleData(string_each_line);
        }
        else
        {
            QMessageBox::about(this,tr("Hint information"),tr("Key and key values can't be empty!"));
            continue;
        }
    }

}

void MainWindow::on_m_del_clicked()
{
    for (int i = 0; i < m_listDynamicallyCreatingControl.size(); i++)
    {
        if (NULL == m_listDynamicallyCreatingControl[i]->getKeyName())
        {
            delete m_listDynamicallyCreatingControl[i];
            m_listDynamicallyCreatingControl.removeAt(i);
        }
    }
}

void MainWindow::on_m_selectImportPath_clicked()
{
    QString path = QFileDialog::getOpenFileName(ui->m_import_path,tr("Open_Image"),"/home",tr("Image　Files(*.*)"));
    ui->m_import_path->setText(path);
}

void MainWindow::on_m_selectExportPath_clicked()
{
    QString path = QFileDialog::getSaveFileName(0,tr("save_Image"),"",tr("Image　Files(*.*)"));
    ui->m_import_export_path->setText(path);
}
