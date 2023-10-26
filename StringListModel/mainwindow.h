#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnRestoreList_clicked();
    void on_btnClearList_clicked();
    void on_btnMoveDown_clicked();
    void on_btnAddItem_clicked();
    void on_btnInsertItem_clicked();
    void on_btnDeleteItem_clicked();
    void on_btnMoveUp_clicked();
    void on_chkEditable_clicked(bool checked);
    void on_btnOrder_clicked(bool checked);

    void on_listView_clicked(const QModelIndex &index);

    void on_btnClearText_clicked();

    void on_btnShowText_clicked();

private:
    Ui::MainWindow *ui;

private:
    QStringList m_strList;
    QStringListModel *m_model;
};
#endif // MAINWINDOW_H
