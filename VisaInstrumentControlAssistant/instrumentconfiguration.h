#pragma once

#include <QDialog>
#include <memory>
#include "ui_instrumentconfiguration.h"
#include "QDelegateTemplate.h"


class instrumentconfiguration : public QDialog
{
	Q_OBJECT

public:
	instrumentconfiguration(QWidget *parent = Q_NULLPTR);
	~instrumentconfiguration();
	using QLineEditDelegate   = QDelegateTemplate<QLineEdit>;
	using QComboBoxDelegate   = QDelegateTemplate<QComboBox>;
	using QPushButtonDelegate = QDelegateTemplate<QPushButton>;
private:
	void initUi();

private:
	Ui::instrumentconfiguration ui;
	/*std::shared_ptr<QLineEditDelegate>        m_qLineEditDelegateForDeviceName;
	std::shared_ptr<QLineEditDelegate>          m_qLineEditDelegateForDeviceConnectInfor;
	std::shared_ptr<QComboBoxDelegate>			m_qComboBoxDelegateForDeviceType;
	std::shared_ptr<QComboBoxDelegate>			m_qComboBoxDelegateForDeviceProtocol;
	std::shared_ptr<QPushButtonDelegate>		m_qPushButtonDelegateForDeviceConfig;*/
	QLineEditDelegate			m_qLineEditDelegateForDeviceName;
	QLineEditDelegate			m_qLineEditDelegateForDeviceConnectInfor;
	QComboBoxDelegate			m_qComboBoxDelegateForDeviceType;
	QComboBoxDelegate			m_qComboBoxDelegateForDeviceProtocol;
	QPushButtonDelegate			m_qPushButtonDelegateForDeviceConfig;
	std::map<std::string ,std::string>			m_map;
};
