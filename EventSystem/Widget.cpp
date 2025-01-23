#include "Widget.h"
#include "./ui_Widget.h"

#include <QPainter>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/images/background.jpg"));
    QWidget::paintEvent(event);
}

void Widget::closeEvent(QCloseEvent *event)
{
    QString title = "Message box";
    QString info = "Sure to exit?";

    QMessageBox::StandardButton box = QMessageBox::question(this, title, info, 
    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (box == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint pt = event->pos();
        QString str = QString::asprintf("pos() = (%d, %d)", pt.x(), pt.y());

        ui->labMove->setText(str);
        ui->labMove->adjustSize();
        ui->labMove->move(pt);
    }

    QWidget::mousePressEvent(event);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    QPoint pt = ui->btnMove->pos();
    auto key = event->key();
    if ((key == Qt::Key_A) || (key == Qt::Key_Left)) {
        ui->btnMove->move(pt.x()-20, pt.y());
    }
    else if ((key == Qt::Key_D) || (key == Qt::Key_Right)) {
        ui->btnMove->move(pt.x()+20, pt.y());
    }
    else if ((key == Qt::Key_S) || (key == Qt::Key_Down)) {
        auto btnHeight = ui->btnMove->height();
        if (pt.y() + btnHeight + 20 >= this->height())
            ui->btnMove->move(pt.x(), this->height()-ui->btnMove->height());
        else
            ui->btnMove->move(pt.x(), pt.y()+20);
    }
    else if ((key == Qt::Key_W) || (key == Qt::Key_Up)) {
        if (pt.y() >= 20)
            ui->btnMove->move(pt.x(), pt.y()-20);
        else
            ui->btnMove->move(pt.x(), 0);
    }
    else if ((key == Qt::Key_Q) && (event->modifiers() & Qt::ControlModifier)) {
        if (pt.y() >= 20)
            ui->btnMove->move(pt.x(), pt.y()-20);
        else
            ui->btnMove->move(pt.x(), 0);
    }

    QWidget::keyPressEvent(event);
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    QPoint pt = ui->btnMove->pos();
    auto key = event->key();
    if ((key == Qt::Key_A) || (key == Qt::Key_Left)) {
        ui->btnMove->move(pt.x()-20, pt.y());
    }
    else if ((key == Qt::Key_D) || (key == Qt::Key_Right)) {
        ui->btnMove->move(pt.x()+20, pt.y());
    }
    else if ((key == Qt::Key_S) || (key == Qt::Key_Down)) {
        auto btnHeight = ui->btnMove->height();
        if (pt.y() + btnHeight + 20 >= this->height())
            ui->btnMove->move(pt.x(), this->height()-ui->btnMove->height());
        else
            ui->btnMove->move(pt.x(), pt.y()+20);
    }
    else if ((key == Qt::Key_W) || (key == Qt::Key_Up)) {
        if (pt.y() >= 20)
            ui->btnMove->move(pt.x(), pt.y()-20);
        else
            ui->btnMove->move(pt.x(), 0);
    }
    else if ((key == Qt::Key_Q) && (event->modifiers() & Qt::ControlModifier)) {
        if (pt.y() >= 20)
            ui->btnMove->move(pt.x(), pt.y()-20);
        else
            ui->btnMove->move(pt.x(), 0);
    }

    QWidget::keyReleaseEvent(event);
}

void Widget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    qDebug("Widget show event");
}

void Widget::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    qDebug("Widget hide event");
}
