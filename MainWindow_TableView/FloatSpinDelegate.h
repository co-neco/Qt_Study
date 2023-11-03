#ifndef FLOATSPINDELEGATE_H
#define FLOATSPINDELEGATE_H

#include <QStyledItemDelegate>
#include <QWidget>

class FloatSpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    FloatSpinDelegate(QObject *parent);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget* editor, const QModelIndex &index) const;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

#endif // FLOATSPINDELEGATE_H
