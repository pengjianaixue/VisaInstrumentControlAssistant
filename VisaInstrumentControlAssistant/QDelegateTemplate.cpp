#include "stdafx.h"
#include "QDelegateTemplate.h"


template <typename	ET>
QDelegateTemplate<ET>::QDelegateTemplate(QWidget *parent, const QString  &InputMask,const QStringList  &PreInputContents, bool IsEnableClearButton)
	: QItemDelegate(parent), m_InputMask(InputMask), m_PreInputContents(PreInputContents),
	  m_ClearButtonIsEnable(IsEnableClearButton)
{
	
}
template <typename	ET>
QDelegateTemplate<ET>::~QDelegateTemplate()
{
	
}
template <typename	ET>
QWidget * QDelegateTemplate<ET>::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	ET *editor = new ET(parent);
	qDebug() << typeid(ET*).name();
	//editor->setPlaceholderText(m_InputMask);
	//editor->setValidator(m_InputValidator);
	//editor->setAlignment(Qt::AlignCenter);
	editor->setStyleSheet("background-color:rgba(193, 205, 205)");
	//editor->setFontPointSize(10);
	//editor->setAcceptRichText(true);
	/*if (m_PreInputContents.length()!=0)
	{
		QCompleter *MyInfor = new QCompleter(m_PreInputContents);
		editor->setCompleter(MyInfor);
	}*/
	/*if (m_ClearButtonIsEnable)
	{
		
		editor->setClearButtonEnabled(true);
	}*/
	
	return (QWidget *)editor;
}
template <typename	ET>
void QDelegateTemplate<ET>::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();
	ET *Editor = static_cast<ET*>(editor);
	/*textEditor->setClearButtonEnabled(true);*/
	qDebug() << typeid(Editor).name();
	if (typeid(Editor) == typeid(QComboBox*))
	{
		((QComboBox*)Editor)->setCurrentText(value);
	}
	else if (typeid(Editor) == typeid(QLineEdit*) )
	{
		((QLineEdit*)Editor)->setText(value);
	}
	else if (typeid(Editor) == typeid(QTextEdit*))
	{
		((QTextEdit*)Editor)->setText(value);
	}
	
}
template <typename	ET>
void QDelegateTemplate<ET>::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	ET *internaleEditor = static_cast<ET*>(editor);
	QVariant value;
	if (typeid(internaleEditor) == typeid(QTextEdit*))
	{
		 value = ((QTextEdit*)(internaleEditor))->toPlainText();
	}
	else if (typeid(internaleEditor) == typeid(QLineEdit*))
	{
		 value = ((QLineEdit*)(internaleEditor))->text();
	}
	else if (typeid(internaleEditor) == typeid(QComboBox*))
	{
		 value = ((QComboBox*)(internaleEditor))->currentText();
	}
	else
	{
		//static_assert(false,"the QDelegateTemplate not support this Qt Class");
	}
	model->setData(index, value, Qt::EditRole);
}
template <typename	ET>
void QDelegateTemplate<ET>::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	editor->setGeometry(option.rect);
}
