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

void CommunicationAddressConfigure::applyWithLanWidget()
{

	m_deviceProtocolInfor.protocoltype = ProtocolType::TCP_IP;
	m_deviceProtocolInfor.protocoinfor.lanInfor.ipAddress = this->ui.lineEdit_IPAddress->text();
	this->close();
}

void CommunicationAddressConfigure::applyWithUsbWidget()
{
	this->close();
}

void CommunicationAddressConfigure::applyWithComportWidget()
{
	this->close();
}

void CommunicationAddressConfigure::applyWithGPIBWidget()
{
	this->close();
}

void CommunicationAddressConfigure::applyWithSSHOrTelnetWidget()
{
	this->close();
}

void CommunicationAddressConfigure::cancelWithLanWidget()
{
	this->close();
}

void CommunicationAddressConfigure::cancelWithUsbWidget()
{
	this->close();
}

void CommunicationAddressConfigure::cancelWithComportWidget()
{
	this->close();
}

void CommunicationAddressConfigure::cancelWithGPIBWidget()
{
	this->close();
}

void CommunicationAddressConfigure::cancelWithSSHOrTelnetWidget()
{
	this->close();
}

void CommunicationAddressConfigure::comPortBaudRateCustom(int index)
{
	if (index == 8)
	{
		this->ui.comboBox_baudrate->setEditable(true);
		this->ui.comboBox_baudrate->setEditText("");
	}
	else
	{
		this->ui.comboBox_baudrate->setEditable(false);
	}
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
	this->ui.ComboBox_instrumentsockettype->addItems(QStringList() << "TCP_IP" << "UDP");
	this->ui.ComboBox_instrumentvisaprotocol->addItems(QStringList() << "INST" << "SCOKET");
	// Comport configuration init
	comportFormInit();
	if (!connectSolts())
	{
		QMessageBox::critical(this, "Internal Error", "Connect Slots Error");
		exit(-1);
	}

}

bool CommunicationAddressConfigure::connectSolts()
{
	return
		//apply 
		connect(this->ui.pushButton_apply_lan, &QPushButton::clicked, this, &CommunicationAddressConfigure::applyWithLanWidget)
		&& connect(this->ui.pushButton_apply_gpib, &QPushButton::clicked, this, &CommunicationAddressConfigure::applyWithGPIBWidget)
		&& connect(this->ui.pushButton_apply_comport, &QPushButton::clicked, this, &CommunicationAddressConfigure::applyWithComportWidget)
		&& connect(this->ui.pushButton_apply_ssh, &QPushButton::clicked, this, &CommunicationAddressConfigure::applyWithSSHOrTelnetWidget)
		&& connect(this->ui.pushButton_apply_usb, &QPushButton::clicked, this, &CommunicationAddressConfigure::applyWithUsbWidget)
		// cancel
		&& connect(this->ui.pushButton_cancel_lan, &QPushButton::clicked, this, &CommunicationAddressConfigure::cancelWithGPIBWidget)
		&& connect(this->ui.pushButton_cancel_gpib, &QPushButton::clicked, this, &CommunicationAddressConfigure::cancelWithGPIBWidget)
		&& connect(this->ui.pushButton_cancel_comport, &QPushButton::clicked, this, &CommunicationAddressConfigure::cancelWithComportWidget)
		&& connect(this->ui.pushButton_cancel_ssh, &QPushButton::clicked, this, &CommunicationAddressConfigure::cancelWithSSHOrTelnetWidget)
		&& connect(this->ui.pushButton_cancel_usb, &QPushButton::clicked, this, &CommunicationAddressConfigure::cancelWithUsbWidget)

		&& connect(this->ui.comboBox_baudrate, SIGNAL(currentIndexChanged(int)), this, SLOT(comPortBaudRateCustom(int)))
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
	this->ui.comboBox_baudrate->addItems(QStringList() << "4800"<<"9600" <<"14400" << "19200" << "38400" << "57600" << "115200"<<"128000"<<"Custom");
	this->ui.comboBox_databits->addItems(QStringList() << "5" << "6" << "7" << "8");
	this->ui.comboBox_parity->addItems(QStringList() << "None" << "Even" << "Odd" << "Mark" << "Space");
	this->ui.comboBox_stopbit->addItems(QStringList() << "1" << "1.5" << "2");
	this->ui.comboBox_flowtype->addItems(QStringList() << "None" << "RTS/CTS" << "XON/XOFF");
}
