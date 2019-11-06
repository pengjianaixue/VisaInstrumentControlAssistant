#pragma once

#include <QCheckBox>
#include <QItemDelegate>
#include <type_traits>
#include <functional>

template <typename	ET>
class QDelegateTemplate : public QItemDelegate
{

public:
	enum DATAOPTYPE
	{
		SETEDITORDATA,
		SETMODELDATA
	};
	// sample void(QWidget *parent,QComboBox *delegatecombox,int row,int column)
	using EDITORSETFUNCTION		= std::function<void(QWidget *,ET *,const int& ,const int&)> ; 
	// sample void(QComboBox *delegatecombox, QVariant modeldata,DATAOPTYPE )
	using EDITORDATAOPFUNCTION  = std::function<QVariant(ET *, QVariant,  DATAOPTYPE, const QModelIndex&)>;
	//Q_OBJECT

//   override API 
public:
	explicit QDelegateTemplate(QWidget *parent = nullptr);
	~QDelegateTemplate();
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const override;
	void updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &index) const override;

// customization API
public:
	void registerEditorSetFunction(EDITORSETFUNCTION &&editorSetFunction);
	void registerEditorDataOperationFunction(EDITORDATAOPFUNCTION &&editorDataOpFunction);
private:
	ET						*m_editor				= {nullptr};
	EDITORSETFUNCTION		m_editorSetFunction		= {nullptr};
	EDITORDATAOPFUNCTION	m_editorDataOpFunction  = {nullptr};

};
