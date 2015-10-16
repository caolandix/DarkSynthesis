#include <QComboBox>
#include <QWidget>
#include <QModelIndex>
#include <QApplication>
#include <QString>
#include <iostream>

#include "comboboxdelegate.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent) : QItemDelegate(parent) {
    m_Items.push_back("Test0");
    m_Items.push_back("Test1");
    m_Items.push_back("Test2");
    m_Items.push_back("Test3");
    m_Items.push_back("Test4");
    m_Items.push_back("Test5");
    m_Items.push_back("Test6");
    m_Items.push_back("Test7");
    m_Items.push_back("Test8");
}

QWidget *ComboBoxDelegate::createEditor(QWidget *pParent, const QStyleOptionViewItem &Option, const QModelIndex &idx) const {
    QComboBox *pComboBox = new QComboBox(pParent);
    for (unsigned int i = 0; i < m_Items.size(); ++i)
        pComboBox -> addItem(m_Items[i].c_str());
    return pComboBox;
}

void ComboBoxDelegate::setEditorData(QWidget *pEditor, const QModelIndex &modelIndex) const {
    QComboBox *pComboBox = static_cast<QComboBox *>(pEditor);
    int val = modelIndex.model() -> data(modelIndex, Qt::EditRole).toUInt();
    pComboBox -> setCurrentIndex(val);
}

void ComboBoxDelegate::setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &modelIndex) const {
    QComboBox *pComboBox = static_cast<QComboBox*>(pEditor);
    pModel -> setData(modelIndex, pComboBox -> currentIndex(), Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *pEditor, const QStyleOptionViewItem &styleOption, const QModelIndex &modelIndex) const {
    pEditor -> setGeometry(styleOption.rect);
}

void ComboBoxDelegate::paint(QPainter *pPainter, const QStyleOptionViewItem &styleOption, const QModelIndex &modelIndex) const {
    QStyleOptionViewItemV4 myOption = styleOption;
    QString text = m_Items[modelIndex.row()].c_str();

    myOption.text = text;
    QApplication::style() -> drawControl(QStyle::CE_ItemViewItem, &myOption, pPainter);
}
