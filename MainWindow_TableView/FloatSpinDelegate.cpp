#include "FloatSpinDelegate.h"

#include <QDoubleSpinBox>

FloatSpinDelegate::FloatSpinDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

QWidget *FloatSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    QDoubleSpinBox* editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(20000);
    editor->setDecimals(2);
    return editor;
}

void FloatSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto data = index.data(Qt::EditRole).toFloat();
    auto spinBox = static_cast<QDoubleSpinBox*>(editor);
    spinBox->setValue(data);
}

void FloatSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    float data = static_cast<QDoubleSpinBox*>(editor)->value();
    QString str = QString::asprintf("%.2f", data);
    model->setData(index, str);
}

void FloatSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
