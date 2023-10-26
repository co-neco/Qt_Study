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


void MainWindow::on_btnClearList_clicked()
{
    m_model->removeRows(0, m_model->rowCount());
}


void MainWindow::on_btnMoveDown_clicked()
{
    auto curRow = ui->listView->currentIndex().row();
    m_model->moveRow(QModelIndex(), curRow, QModelIndex(), curRow+2);
}


void MainWindow::on_btnAddItem_clicked()
{
    m_model->insertRow(m_model->rowCount());
    auto index = m_model->index(m_model->rowCount()-1, 0);
    m_model->setData(index, "new item", Qt::DisplayRole);
}


void MainWindow::on_btnInsertItem_clicked()
{
    auto index = ui->listView->currentIndex();
    m_model->insertRow(index.row());
    m_model->setData(index, "insert new item", Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_btnDeleteItem_clicked()
{
    m_model->removeRow(ui->listView->currentIndex().row());
}


void MainWindow::on_btnMoveUp_clicked()
{
    auto curRow = ui->listView->currentIndex().row();
    m_model->moveRow(QModelIndex(), curRow, QModelIndex(), curRow-1);
}


void MainWindow::on_chkEditable_clicked(bool checked)
{
    if (checked)
        ui->listView->setEditTriggers(
            QAbstractItemView::DoubleClicked | 
            QAbstractItemView::SelectedClicked);
    else 
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void MainWindow::on_btnOrder_clicked(bool checked)
{
    if (checked)
        m_model->sort(0, Qt::AscendingOrder);
    else
        m_model->sort(0, Qt::DescendingOrder);
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString str = QString::asprintf("model index: row=%d, col=%d; ", index.row() , index.column());
    auto var = m_model->data(index, Qt::DisplayRole);
    str = str + var.toString();
    ui->statusbar->showMessage(str);
}


void MainWindow::on_btnClearText_clicked()
{
    ui->modelTextEdit->clear();
}


void MainWindow::on_btnShowText_clicked()
{
    ui->modelTextEdit->clear();
    auto strList = m_model->stringList();
    for (int i = 0; i < strList.size(); ++i) {
        ui->modelTextEdit->appendPlainText(strList.at(i));  
    }
}