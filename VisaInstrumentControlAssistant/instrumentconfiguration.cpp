#include "stdafx.h"
#include "instrumentconfiguration.h"

instrumentconfiguration::instrumentconfiguration(QWidget *parent)
	: QDialog(parent)/*, 
	m_qLineEditDelegateForDeviceName(std::make_shared<QLineEditDelegate>(this)),
	m_qComboBoxDelegateForDeviceType(std::make_shared<QComboBoxDelegate>(this)),
	m_qPushButtonDelegateForDeviceConfig(std::make_shared<QPushButtonDelegate>(this)),
	m_qComboBoxDelegateForDeviceProtocol(std::make_shared<QComboBoxDelegate>(this)),
	m_qLineEditDelegateForDeviceConnectInfor(std::make_shared<QLineEditDelegate>(this))*/
{
	ui.setupUi(this);
	initUi();
}

instrumentconfiguration::~instrumentconfiguration()
{

}

void instrumentconfiguration::initUi()
{
	/*this->ui.tableWidget->setItemDelegateForColumn(0, m_qComboBoxDelegateForDeviceType.get());
	this->ui.tableWidget->setItemDelegateForColumn(1, m_qComboBoxDelegateForDeviceProtocol.get());
	this->ui.tableWidget->setItemDelegateForColumn(2, m_qLineEditDelegateForDeviceConnectInfor.get());
	this->ui.tableWidget->setItemDelegateForColumn(3, m_qPushButtonDelegateForDeviceConfig.get());
	this->ui.tableWidget->setItemDelegateForColumn(4, m_qLineEditDelegateForDeviceName.get());*/
	this->ui.tableWidget->setItemDelegateForColumn(0, &m_qComboBoxDelegateForDeviceType);
	this->ui.tableWidget->setItemDelegateForColumn(1, &m_qComboBoxDelegateForDeviceProtocol);
	this->ui.tableWidget->setItemDelegateForColumn(2, &m_qLineEditDelegateForDeviceConnectInfor);
	//this->ui.tableWidget->setItemDelegateForColumn(3, &m_qPushButtonDelegateForDeviceConfig);
	this->ui.tableWidget->setItemDelegateForColumn(4, &m_qLineEditDelegateForDeviceName);
	this->ui.tableWidget->setCellWidget(0, 3, new QPushButton("configuration", this));
	this->ui.tableWidget->setColumnCount(5);
	this->ui.tableWidget->setRowCount(1);
	//this->ui.tableWidget->setStyle(QStyleFactory::create("Fusion"));

	
}
