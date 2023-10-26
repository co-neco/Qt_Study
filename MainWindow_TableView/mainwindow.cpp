#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QStringList>

#define TABLE_ROW 2
#define TABLE_COL 6

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new QStandardItemModel(TABLE_ROW, TABLE_COL, this);
    _selectionModel = new QItemSelectionModel(_model, this);
    connect(_selectionModel, &QItemSelectionModel::currentChanged, this, &MainWindow::do_currentChanged);

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
    
}