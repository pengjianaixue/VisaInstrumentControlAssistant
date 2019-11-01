#pragma once

#include <QDialog>
#include <memory>
#include <map>
#include "ui_instrumentconfiguration.h"
#include "QDelegateTemplate.h"
#include "CommunicationAddressConfigure.h"
#include "visacontrol.h"

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
public:
	static void comboxDelegateEditorSet(QWidget *parent,QComboBox *comboxdelegate, const int &row, const int &column);
	static QVariant delegateComboxDataOp(QComboBox *comboxdelegate, QVariant modeldata, QComboBoxDelegate::DATAOPTYPE dateoptype);
	
private:
	void init();
	bool conncetSlots();
	QToolButton *getQToolButtonCellWidget();
	QWidget     *getQCheckBoxCellWidget();
	static VisaControl::ProtocolType  getProtocolTypefromProtocolName(const QString &protocolname);
	static QStringList	getDeviceProtocolChoose(const QString &deviceIndex);
	
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
	static std::map<QString, int>			static_deciveTypeMapToIndex;
	//VisaControl								m_visaControl;
};
