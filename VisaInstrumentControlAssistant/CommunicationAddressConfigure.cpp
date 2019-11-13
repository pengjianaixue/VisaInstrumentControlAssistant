#include "stdafx.h"
#include "CommunicationAddressConfigure.h"

CommunicationAddressConfigure::CommunicationAddressConfigure(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	init();
}

CommunicationAddressConfigure::~CommunicationAddressConfigure()
{
	
}

bool CommunicationAddressConfigure::setCurrentTab(const QString &tabname)
{
	this->ui.tabWidget_protocol_configure->clear();
	if (m_protocolNameMapToWidget.find(tabname)!= m_protocolNameMapToWidget.cend())
	{
		this->ui.tabWidget_protocol_configure->addTab(m_protocolNameMapToWidget[tabname], tabname);
		return true;
	}
	QMessageBox::critical(this, "Protocol type error", "Protocol type haven't found");
	return false;
	
}

void CommunicationAddressConfigure::applyLanWidget()
{

	/*QWidget *applywidget =  qobject_cast<QWidget*>(QObject::sender());
	auto it =  m_protocolWidgetMapToName.find(applywidget);
	if (it != m_protocolWidgetMapToName.end())
	{
		QString widgetname = m_protocolWidgetMapToName[this->ui.tabWidget_protocol_configure->currentWidget()];
	}*/
	
}

void CommunicationAddressConfigure::applyUsbWidget()
{
}

void CommunicationAddressConfigure::applyComportWidget()
{

}

void CommunicationAddressConfigure::applyGPIBWidget()
{

}

void CommunicationAddressConfigure::applySSHOrTelnetWidget()
{

}

void CommunicationAddressConfigure::showEvent(QShowEvent *event)
{
	
}

void CommunicationAddressConfigure::init()
{
	this->ui.tabWidget_protocol_configure->setTabBarAutoHide(true);
	
	for (size_t i = 0; i < this->ui.tabWidget_protocol_configure->count(); i++)
	{
		this->ui.tabWidget_protocol_configure->setCurrentIndex(i);
		m_protocolNameMapToWidget.insert({ this->ui.tabWidget_protocol_configure->currentWidget()->accessibleName(),
			this->ui.tabWidget_protocol_configure->currentWidget() });
		m_protocolWidgetMapToName.insert({ this->ui.tabWidget_protocol_configure->currentWidget() ,this->ui.tabWidget_protocol_configure->currentWidget()->accessibleName() });
			
	}
	this->ui.tabWidget_protocol_configure->clear();
	//LAN configuration init
	this->ui.ComboBox_instrumentsockettype->addItems(QStringList() << "INST" << "SCOKET");
	// Comport configuration init
	comportFormInit();

	
}

bool CommunicationAddressConfigure::connectSolts()
{
	return
		//apply 
		connect(this->ui.pushButton_apply_lan, &QPushButton::clicked, this, CommunicationAddressConfigure::applyLanWidget)
		&& connect(this->ui.pushButton_apply_gpib, &QPushButton::clicked, this, CommunicationAddressConfigure::applyGPIBWidget)
		&& connect(this->ui.pushButton_cancel_comport, &QPushButton::clicked, this, CommunicationAddressConfigure::applyComportWidget)
		&& connect(this->ui.pushButton_apply_ssh, &QPushButton::clicked, this, CommunicationAddressConfigure::applySSHOrTelnetWidget)
		&& connect(this->ui.pushButton_apply_usb, &QPushButton::clicked, this, CommunicationAddressConfigure::applyUsbWidget)
		// cancel
		;
}

void CommunicationAddressConfigure::comportFormInit()
{
	QStringList vaildSerialPortName;
	Q_FOREACH(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	{
		vaildSerialPortName << info.portName();
		//qDebug() << "serialPortName:" << info.portName(); 
	}
	this->ui.comboBox_comport->addItems(vaildSerialPortName);
	this->ui.comboBox_baudrate->addItems(QStringList() << "9600" << "19200" << "38400" << "57600" << "115200");
	this->ui.comboBox_databits->addItems(QStringList() << "5" << "6" << "7" << "8");
	this->ui.comboBox_parity->addItems(QStringList() << "None" << "Even" << "Odd" << "Mark" << "Space");
	this->ui.comboBox_stopbit->addItems(QStringList() << "1" << "1.5" << "2");
	this->ui.comboBox_flowtype->addItems(QStringList() << "None" << "RTS/CTS" << "XON/XOFF");
}
