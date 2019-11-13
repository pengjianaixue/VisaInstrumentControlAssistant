#pragma once

#include <QDialog>
#include <memory>
#include <map>
#include "ui_instrumentconfiguration.h"
#include "QDelegateTemplate.h"
#include "CommunicationAddressConfigure.h"
#include "visacontrol.h"
using namespace std::placeholders;
extern template class QDelegateTemplate<QLineEdit>;
extern template class QDelegateTemplate<QComboBox>;
extern template class QDelegateTemplate<QPushButton>;
extern template class QDelegateTemplate<QTextEdit>;

class instrumentconfiguration : public QDialog
{
	Q_OBJECT
	
public:
	explicit instrumentconfiguration(QWidget *parent = Q_NULLPTR);
	~instrumentconfiguration();
	using QLineEditDelegate   = QDelegateTemplate<QLineEdit>;
	using QComboBoxDelegate   = QDelegateTemplate<QComboBox>;
	using QPushButtonDelegate = QDelegateTemplate<QPushButton>;
public slots:
	void openConfigureForm();
	void setConncetStrInfor(const QString &instrumentmodel);
	void checkAndInsertNextSetRow( QTableWidgetItem *item);
	void rowOperationMenu(const QPoint &pos);
	void deleteRow();
	void addRow();
protected:
	bool eventFilter(QObject *target, QEvent *event) override;
signals:
	//void si_InsertNexRow(QTableWidgetItem *item);
private:
	void init();
	bool conncetSlots();
	QToolButton* getQToolButtonCellWidget(int row );
	QWidget* getQCheckBoxCellWidget(int row);
	VisaControl::ProtocolType  getProtocolTypefromProtocolName(const QString &protocolname);
	QStringList	getDeviceProtocolChoose(const QString &deviceIndex);
	void comboxDelegateEditorSet(QWidget *parent, QComboBox *comboxdelegate, const int &row, const int &column);
	QVariant delegateComboxDataOp(QComboBox *comboxdelegate, QVariant modeldata, 
		QComboBoxDelegate::DATAOPTYPE dateoptype,const QModelIndex &index);
	void initRow(int row);
	//QCheckBox   *getQCheckBoxCellWidget();

private:
	Ui::instrumentconfiguration ui;
	//std::shared_ptr<QPushButtonDelegate>		m_qPushButtonDelegateForDeviceConfig;
	QLineEditDelegate						m_qLineEditDelegateForDeviceName;
	QComboBoxDelegate						m_qComboBoxDelegateForDeviceConnectInfor;
	QComboBoxDelegate						m_qComboBoxDelegateForDeviceType;
	QComboBoxDelegate						m_qComboBoxDelegateForDeviceProtocol;
	QPushButtonDelegate						m_qPushButtonDelegateForDeviceConfig;
	CommunicationAddressConfigure			*m_communicationAddressConfigureform = {nullptr};
	std::map<QString, int>					m_deciveTypeMapToIndex;
	std::list<VisaControl::InstrumentInfor> m_instrumentInforlist;
	QString									m_connectStr;
	//VisaControl								m_visaControl;
};
