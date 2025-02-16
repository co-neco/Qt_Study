#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qevent.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;
    virtual void hideEvent(QHideEvent *event) override;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
