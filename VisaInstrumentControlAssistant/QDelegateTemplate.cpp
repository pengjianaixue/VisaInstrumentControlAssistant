#include "stdafx.h"
#include "QDelegateTemplate.h"


template <typename	ET>
QDelegateTemplate<ET>::QDelegateTemplate(QWidget *parent)
	: QItemDelegate(parent)
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
	//qDebug() << typeid(ET*).name();
	m_editorSetFunction(parent,editor, index.row(), index.column());
	return (QWidget*)editor;
}
template <typename	ET>
void QDelegateTemplate<ET>::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();
	ET *Editor = static_cast<ET*>(editor);
	//qDebug() << typeid(Editor).name();
	if (m_editorDataOpFunction)
	{
		m_editorDataOpFunction(Editor, value, DATAOPTYPE::SETEDITORDATA);
	}
	/*else
	{
		if (typeid(Editor) == typeid(QComboBox*))
		{
			((QComboBox*)Editor)->setCurrentText(value);
		}
		else if (typeid(Editor) == typeid(QLineEdit*))
		{
			((QLineEdit*)Editor)->setText(value);
		}
		else if (typeid(Editor) == typeid(QTextEdit*))
		{
			((QTextEdit*)Editor)->setText(value);
		}
	}*/
	
	
}


//specialization 
template<>
void QDelegateTemplate<QComboBox>::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();
	QComboBox *Editor = static_cast<QComboBox*>(editor);
	if (m_editorDataOpFunction)
	{
		m_editorDataOpFunction(Editor, value, DATAOPTYPE::SETEDITORDATA, index);
	}
	Editor->setCurrentText(value);
}

//specialization 
template<>
void QDelegateTemplate<QLineEdit>::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();
	QLineEdit *Editor = static_cast<QLineEdit*>(editor);
	if (m_editorDataOpFunction)
	{
		m_editorDataOpFunction(Editor, value, DATAOPTYPE::SETEDITORDATA, index);
	}
	Editor->setText(value);
}

//specialization 
template<>
void QDelegateTemplate<QTextEdit>::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();
	QTextEdit *Editor = static_cast<QTextEdit*>(editor);
	if (m_editorDataOpFunction)
	{
		m_editorDataOpFunction(Editor, value, DATAOPTYPE::SETEDITORDATA, index);
	}
	Editor->setText(value);
}

//specialization 
template<>
void QDelegateTemplate<QPushButton>::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();
	QPushButton *Editor = static_cast<QPushButton*>(editor);
	if (m_editorDataOpFunction)
	{
		m_editorDataOpFunction(Editor, value, DATAOPTYPE::SETEDITORDATA, index);
	}
	Editor->setText(value);
}


template <typename	ET>
void QDelegateTemplate<ET>::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	ET *internaleEditor = static_cast<ET*>(editor);
	QVariant value;
	if (m_editorDataOpFunction)
	{
		value = m_editorDataOpFunction(internaleEditor, QVariant(), DATAOPTYPE::SETMODELDATA);
	}
	/*else
	{
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
	}*/
	model->setData(index, value, Qt::EditRole);
}
//specialization 
template <>
void QDelegateTemplate<QComboBox>::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QComboBox *internaleEditor = static_cast<QComboBox*>(editor);
	QVariant value = internaleEditor->currentText();
	if (m_editorDataOpFunction)
	{
		value = m_editorDataOpFunction(internaleEditor, QVariant(), DATAOPTYPE::SETMODELDATA, index);
	}
	model->setData(index, value, Qt::EditRole);
}
//specialization 
template <>
void QDelegateTemplate<QLineEdit>::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QLineEdit *internaleEditor = static_cast<QLineEdit*>(editor);
	QVariant value = internaleEditor->text();
	if (m_editorDataOpFunction)
	{
		value = m_editorDataOpFunction(internaleEditor, QVariant(), DATAOPTYPE::SETMODELDATA, index);
	}
	model->setData(index, value, Qt::EditRole);

}

//specialization 
template <>
void QDelegateTemplate<QTextEdit>::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QTextEdit *internaleEditor = static_cast<QTextEdit*>(editor);
	QVariant value = internaleEditor->toPlainText();
	if (m_editorDataOpFunction)
	{
		value = m_editorDataOpFunction(internaleEditor, QVariant(), DATAOPTYPE::SETMODELDATA, index);
	}
	model->setData(index, value, Qt::EditRole);

}

//specialization 
template <>
void QDelegateTemplate<QPushButton>::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QPushButton *internaleEditor = static_cast<QPushButton*>(editor);
	QVariant value = internaleEditor->text();
	if (m_editorDataOpFunction)
	{
		value = m_editorDataOpFunction(internaleEditor, QVariant(), DATAOPTYPE::SETMODELDATA, index);
	}
	model->setData(index, value, Qt::EditRole);
}

template <typename	ET>
void QDelegateTemplate<ET>::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	editor->setGeometry(option.rect);
}

template<typename ET>
void QDelegateTemplate<ET>::registerEditorSetFunction(EDITORSETFUNCTION &&editorSetFunction)
{
	if (editorSetFunction !=nullptr)
	{
		m_editorSetFunction = editorSetFunction;
	}
}

template<typename ET>
void QDelegateTemplate<ET>::registerEditorDataOperationFunction(EDITORDATAOPFUNCTION &&editorDataOpFunction)
{
	if (editorDataOpFunction != nullptr)
	{
		m_editorDataOpFunction = editorDataOpFunction;
	}
}

template class QDelegateTemplate<QLineEdit>;
template class QDelegateTemplate<QComboBox>;
template class QDelegateTemplate<QPushButton>;
template class QDelegateTemplate<QTextEdit>;



