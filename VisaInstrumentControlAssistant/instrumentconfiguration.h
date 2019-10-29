#pragma once

#include <QDialog>
#include <memory>
#include "ui_instrumentconfiguration.h"
#include "QDelegateTemplate.h"
#include "CommunicationAddressConfigure.h"

class instrumentconfiguration : public QDialog
{
	Q_OBJECT
	
public:
	instrumentconfiguration(QWidget *parent = Q_NULLPTR);
	~instrumentconfiguration();
	using QLineEditDelegate   = QDelegateTemplate<QLineEdit>;
	using QComboBoxDelegate   = QDelegateTemplate<QComboBox>;
	using QPushButtonDelegate = QDelegateTemplate<QPushButton>;
public slots:
	void openConfigureForm();
public:
	static void comboxDelegateEditorSet(QComboBox *comboxdelegate, const int &row, const int &column);
	static QVariant delegateComboxDataOp(QComboBox *comboxdelegate, QVariant modeldata, QComboBoxDelegate::DATAOPTYPE dateoptype);
private:
	void initUi();
	bool conncetSlots();
	QToolButton *getQToolButtonCellWidget();

private:
	Ui::instrumentconfiguration ui;
	//std::shared_ptr<QPushButtonDelegate>		m_qPushButtonDelegateForDeviceConfig;
	QLineEditDelegate				m_qLineEditDelegateForDeviceName;
	QLineEditDelegate				m_qLineEditDelegateForDeviceConnectInfor;
	QComboBoxDelegate				m_qComboBoxDelegateForDeviceType;
	QComboBoxDelegate				m_qComboBoxDelegateForDeviceProtocol;
	QPushButtonDelegate				m_qPushButtonDelegateForDeviceConfig;
	CommunicationAddressConfigure	*m_communicationAddressConfigureform = {nullptr};
};
