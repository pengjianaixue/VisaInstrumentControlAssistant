#pragma once

#include <QCheckBox>
#include <QItemDelegate>
#include <type_traits>


template <typename	ET>
class QDelegateTemplate : public QItemDelegate
{
	//Q_OBJECT

public:
	QDelegateTemplate(QWidget *parent = nullptr,const QString& InputMask="" ,const QStringList  &PreInputContents= QStringList(),bool IsEnableClearButton=true);
	~QDelegateTemplate();
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
	QValidator		*m_InputValidator;
	QString			m_InputMask;
	QStringList		m_PreInputContents;
	bool			m_ClearButtonIsEnable;
};
template QDelegateTemplate<QLineEdit>;
template QDelegateTemplate<QComboBox>;
template QDelegateTemplate<QPushButton>;
