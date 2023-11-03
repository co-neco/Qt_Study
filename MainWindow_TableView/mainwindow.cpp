#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ComboBoxDelegate.h"
#include "FloatSpinDelegate.h"

#include <QFileDialog>
#include <QStringList>

#define TABLE_ROW 2
#define TABLE_COL 6

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new QStandardItemModel(this);
    _selectionModel = new QItemSelectionModel(_model, this);
    connect(_selectionModel, &QItemSelectionModel::currentChanged, this, &MainWindow::do_currentChanged);
    connect(ui->actLeft, &QAction::triggered, this, &MainWindow::alignText);
    connect(ui->actCenter, &QAction::triggered, this, &MainWindow::alignText);
    connect(ui->actRight, &QAction::triggered, this, &MainWindow::alignText);

    ui->tableView->setModel(_model);


    ui->tableView->setSelectionModel(_selectionModel);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    setCentralWidget(ui->splitter);

    _labCurFile = new QLabel("Current file: ", this);
    _labCurFile->setMinimumWidth(200);
    _labCellPos = new QLabel("Current cell position: ", this);
    _labCellPos->setMinimumWidth(180);
    _labCellPos->setAlignment(Qt::AlignHCenter);
    _labCellText = new QLabel("Cell content: ", this);
    _labCellText->setMinimumWidth(150);
    ui->statusbar->addWidget(_labCurFile);
    ui->statusbar->addWidget(_labCellPos);
    ui->statusbar->addWidget(_labCellText);

    _alignActionGroup = new QActionGroup(this);
    _alignActionGroup->addAction(ui->actLeft);
    _alignActionGroup->addAction(ui->actCenter);
    _alignActionGroup->addAction(ui->actRight);
    _alignActionGroup->setExclusive(true);

    auto spinBoxDelegate = new FloatSpinDelegate(this);
    ui->tableView->setItemDelegateForColumn(1, spinBoxDelegate);
    ui->tableView->setItemDelegateForColumn(2, spinBoxDelegate);
    ui->tableView->setItemDelegateForColumn(3, spinBoxDelegate);

    QStringList itemList;
    itemList << "优" << "良" << "一般" << "不合格";
    auto comboBoxDelegate = new ComboBoxDelegate(this, itemList);
    ui->tableView->setItemDelegateForColumn(4, comboBoxDelegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_currentChanged(const QModelIndex &cur, const QModelIndex &prev) 
{
    Q_UNUSED(prev);
    if (!cur.isValid())
        return;

    _labCellPos->setText(QString::asprintf("Current cell position: %d row, %d col", cur.row(), cur.column()));
    QStandardItem* item = _model->itemFromIndex(cur);
    _labCellText->setText("Cell content: " + item->text());
}

void MainWindow::on_actOpen_triggered()
{
    QString curDir = QCoreApplication::applicationDirPath();
    QString filePath = QFileDialog::getOpenFileName(this, "Open a file", curDir, "Data file(*.txt);;All files(*.*)");

    if (filePath.isEmpty())
        return;

    QStringList fileContent;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream fileStream(&file);
    ui->plainTextEdit->clear();
    while (!fileStream.atEnd()) {
        
        QString str = fileStream.readLine();
        ui->plainTextEdit->appendPlainText(str);
        fileContent.append(str);
    }

    file.close();

    if (!fileContent.size())
        return;

    _labCurFile->setText("Current file: " + filePath);
    ui->actAddRow->setEnabled(true);
    ui->actInsertRow->setEnabled(true);
    ui->actDeleteRow->setEnabled(true);
    ui->actSave->setEnabled(true);
    InitModelData(fileContent);
}

void MainWindow::InitModelData(QStringList &fileContent)
{
    int rowCount = fileContent.size();

    QString header = fileContent.at(0);
    QStringList headerList = header.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    _model->setHorizontalHeaderLabels(headerList);
    
    QStandardItem* item = nullptr;
    
    for (int i = 1; i < rowCount; ++i) {
         
        QStringList rowContent = fileContent.at(i).split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        assert(rowContent.size() == TABLE_COL);

        for (int j = 0; j < rowContent.size() - 1; ++j) {
            item = new QStandardItem(rowContent.at(j));
            _model->setItem(i-1, j, item);
        }

        item = new QStandardItem(headerList.at(rowContent.size() - 1));
        item->setCheckable(true);
        item->setBackground(QBrush(Qt::yellow));

        item->setCheckState(rowContent.at(0) == "0" ? Qt::Unchecked : Qt::Checked);
        _model->setItem(i - 1, rowContent.size() - 1, item);
    }
}

void MainWindow::on_actAddRow_triggered()
{
    QList<QStandardItem*> itemList;
    QStandardItem* item = nullptr;

    for (int i = 0; i < TABLE_COL - 2; i++) {
        item = new QStandardItem("0");
        itemList << item;
    }
    
    itemList << new QStandardItem("良");

    QString str = _model->headerData(_model->columnCount() - 1, Qt::Horizontal, Qt::DisplayRole).toString();
    item = new QStandardItem(str);
    item->setCheckable(true);
    item->setBackground(QBrush(Qt::yellow));
    item->setCheckState(Qt::Unchecked);
    itemList << item;

    _model->appendRow(itemList);
    
    QModelIndex curIndex = _model->index(_model->rowCount() - 1, 0);
    _selectionModel->clearSelection();
    _selectionModel->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}


void MainWindow::on_actInsertRow_triggered()
{
    QList<QStandardItem*> itemList;
    QStandardItem* item = nullptr;

    for (int i = 0; i < TABLE_COL - 2; i++) {
        item = new QStandardItem("0");
        itemList << item;
    }

    itemList << new QStandardItem("良");
    
    QString str = _model->headerData(_model->columnCount() - 1, Qt::Horizontal, Qt::DisplayRole).toString();
    item = new QStandardItem(str);
    item->setCheckable(true);
    item->setBackground(QBrush(Qt::yellow));
    item->setCheckState(Qt::Unchecked);
    itemList << item;

    QModelIndex index = ui->tableView->currentIndex();
    _model->insertRow(index.row(), itemList);

    _selectionModel->clearSelection();
    _selectionModel->setCurrentIndex(index, QItemSelectionModel::Select);
}


void MainWindow::on_actDeleteRow_triggered()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (index.row() == _model->rowCount() - 1)
        _model->removeRow(index.row());
    else {
        _selectionModel->clearSelection();
        _selectionModel->setCurrentIndex(index, QItemSelectionModel::Select);
    }
}

void MainWindow::alignText()
{
    if (!_selectionModel->hasSelection())
        return;

    Qt::Alignment textAlign = Qt::AlignVCenter;
    if (ui->actLeft->isChecked())
        textAlign |= Qt::AlignLeft;
    else if (ui->actCenter->isChecked())
        textAlign |= Qt::AlignCenter;
    else if (ui->actRight->isChecked())
        textAlign |= Qt::AlignRight;

    QModelIndexList indices = _selectionModel->selectedIndexes();
    for (int i = 0; i < indices.size(); ++i) {
        QModelIndex index = indices.at(i);
        QStandardItem* item = _model->itemFromIndex(index);
        item->setTextAlignment(textAlign);
    }
    
}

void MainWindow::on_actPreviewData_triggered()
{
    ui->plainTextEdit->clear();
    QStandardItem* item = nullptr;
    QString str;

    if (_model->rowCount() == 0)
        return;

    for (int i = 0; i < _model->columnCount(); ++i) {
        item = _model->horizontalHeaderItem(i);
        str.append(item->text() + "\t");
    }

    ui->plainTextEdit->appendPlainText(str);

    for (int i = 0; i < _model->rowCount(); ++i) {
        str.clear();
        for (int j = 0; j < _model->columnCount() - 1; ++j) {
            item = _model->item(i, j);
            str.append(item->text() + "\t");
        }

        item = _model->item(i, _model->columnCount() - 1);
        if (item->checkState() == Qt::Checked)
            str.append("1");
        else
            str.append("0");

        ui->plainTextEdit->appendPlainText(str);
    }
}
