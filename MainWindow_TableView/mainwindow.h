#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QActionGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    void InitModelData(QStringList& fileContent);

private slots:
    void do_currentChanged(const QModelIndex& cur, const QModelIndex& prev);

    void on_actOpen_triggered();

private:
    QLabel* _labCurFile;
    QLabel* _labCellPos;
    QLabel* _labCellText;
    QActionGroup* _alignActionGroup;

    QStandardItemModel* _model;
    QItemSelectionModel* _selectionModel;
};
#endif // MAINWINDOW_H
