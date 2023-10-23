#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // give m_strList member vairable 10 fruite
    m_strList << "apple" << "banana" << "cherry" << "date" << "elderberry";
    m_model = new QStringListModel(m_strList);
    m_model->setStringList(m_strList);
    ui->listView->setModel(m_model);
    ui->chkEditable->setChecked(true);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnRestoreList_clicked()
{
    m_model->setStringList(m_strList);
}

