#include "ComboBoxDelegate.h"

#include <QComboBox>

ComboBoxDelegate::ComboBoxDelegate(QObject *parent, const QStringList& itemList) 
    : QStyledItemDelegate{parent}, _itemList(itemList)
{

}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    auto editor = new QComboBox(parent);
    editor->addItems(_itemList);
    editor->setFrame(false);
    editor->setEditable(false);
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto data = index.data(Qt::EditRole).toString();
    auto comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentText(data);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto data = static_cast<QComboBox*>(editor)->currentText();
    model->setData(index, data);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
