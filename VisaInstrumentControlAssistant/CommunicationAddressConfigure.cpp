#include "stdafx.h"
#include "CommunicationAddressConfigure.h"

CommunicationProtocolConfigure::CommunicationProtocolConfigure(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	init();
}

CommunicationProtocolConfigure::~CommunicationProtocolConfigure()
{
	
}

CommunicationProtocolConfigure::DeviceProtocolInfor CommunicationProtocolConfigure::getCommunicationProtocolInfor() const
{
	return m_deviceProtocolInfor;
}

bool CommunicationProtocolConfigure::setCurrentProtocol(const QString &tabName, const QString &protocolName)
{
	this->ui.tabWidget_protocol_configure->clear();
	if (m_protocolNameMapToWidget.find(tabName)!= m_protocolNameMapToWidget.cend())
	{
		this->ui.tabWidget_protocol_configure->addTab(m_protocolNameMapToWidget[tabName], tabName);
		if (tabName == "LAN" || tabName == "SSH/Telnet")
		{
			uiConfiguration(protocolName);
		}
		return true;
	}
	QMessageBox::critical(this, "Protocol type error", "Protocol type haven't found");
	return false;
	
}

void CommunicationProtocolConfigure::applyWithLanWidget()
{
	
	m_deviceProtocolInfor.protocoinfor.lanInfor.ipAddress = this->ui.lineEdit_IPAddress->text();
	m_deviceProtocolInfor.protocoinfor.lanInfor.visaType = this->ui.ComboBox_instrumentvisaprotocol->currentText();
	m_deviceProtocolInfor.protocoinfor.lanInfor.socketType = this->ui.ComboBox_instrumentsockettype->currentText() == "TCP_IP" ? LANInfor::SocketType::TCP_IP : LANInfor::SocketType::UDP;
	m_deviceProtocolInfor.protocoltype = this->ui.ComboBox_instrumentsockettype->currentText() == "TCP_IP" ? ProtocolType::TCP_IP : ProtocolType::UDP;
	m_deviceProtocolInfor.protocoinfor.lanInfor.LoaclPort = this->ui.spinBox_localport->text();
	m_deviceProtocolInfor.protocoinfor.lanInfor.remotePort = this->ui.spinBox_remoteport->text();
	emit operationCompletion(1);
	this->close();
}

void CommunicationProtocolConfigure::applyWithUsbWidget()
{
	m_deviceProtocolInfor.protocoltype = ProtocolType::USB;
	m_deviceProtocolInfor.protocoinfor.usbInfor.USBDevice = this->ui.comboBox_usb->currentText();
	emit operationCompletion(1);
	this->close();
}

void CommunicationProtocolConfigure::applyWithComportWidget()
{
	m_deviceProtocolInfor.protocoltype = ProtocolType::COM;
	m_deviceProtocolInfor.protocoinfor.comportInfor.comport  = this->ui.comboBox_comport->currentText();
	m_deviceProtocolInfor.protocoinfor.comportInfor.baudRate = this->ui.comboBox_baudrate->currentText();
	m_deviceProtocolInfor.protocoinfor.comportInfor.dataBits = this->ui.comboBox_databits->currentText();
	m_deviceProtocolInfor.protocoinfor.comportInfor.Parity	 = this->ui.comboBox_parity->currentText();
	m_deviceProtocolInfor.protocoinfor.comportInfor.stopBits = this->ui.comboBox_stopbit->currentText();
	m_deviceProtocolInfor.protocoinfor.comportInfor.flowType = this->ui.comboBox_flowtype->currentText();
	emit operationCompletion(1);
	this->close();
}

void CommunicationProtocolConfigure::applyWithGPIBWidget()
{
	m_deviceProtocolInfor.protocoltype = ProtocolType::GPIB;
	m_deviceProtocolInfor.protocoinfor.gpibInfor.gpibAddress = this->ui.spinBox_gpibaddress->text();
	emit operationCompletion(1);
	this->close();
}

void CommunicationProtocolConfigure::applyWithSSHOrTelnetWidget()
{
	
	m_deviceProtocolInfor.protocoinfor.sshOrTelnetInfor.ipAddress = this->ui.lineEdit_address->text();
	m_deviceProtocolInfor.protocoinfor.sshOrTelnetInfor.protocol  = this->ui.ComboBox_protocol->currentText() == "SSH" ? SSHandTelnetInfor::Protocol::SSH : SSHandTelnetInfor::Protocol::Telnet;
	m_deviceProtocolInfor.protocoltype = this->ui.ComboBox_protocol->currentText() == "SSH" ? ProtocolType::SSH : ProtocolType::Telnet;
	m_deviceProtocolInfor.protocoinfor.sshOrTelnetInfor.port = this->ui.spinBox_sshport->text();
	m_deviceProtocolInfor.protocoinfor.sshOrTelnetInfor.userName = this->ui.lineEdit_useraccount->text();
	m_deviceProtocolInfor.protocoinfor.sshOrTelnetInfor.password = this->ui.lineEdit_password->text();
	m_deviceProtocolInfor.protocoinfor.sshOrTelnetInfor.prompt = this->ui.lineEdit_prompt->text();
	emit operationCompletion(1);
	this->close();
}

void CommunicationProtocolConfigure::cancelWithLanWidget()
{
	
	emit operationCompletion(0);
	this->close();
}

void CommunicationProtocolConfigure::cancelWithUsbWidget()
{
	emit operationCompletion(0);
	this->close();
}

void CommunicationProtocolConfigure::cancelWithComportWidget()
{
	emit operationCompletion(0);
	this->close();
}

void CommunicationProtocolConfigure::cancelWithGPIBWidget()
{
	emit operationCompletion(0);
	this->close();
}

void CommunicationProtocolConfigure::cancelWithSSHOrTelnetWidget()
{
	emit operationCompletion(0);
	this->close();
}

void CommunicationProtocolConfigure::comPortBaudRateCustom(int index)
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

void CommunicationProtocolConfigure::uiConfiguration(const QString &protocol)
{
	
	if (protocol == "TCP_IP")
	{
		this->ui.ComboBox_instrumentsockettype->clear();
		this->ui.ComboBox_instrumentsockettype->addItem("TCP_IP");
	}
	else if (protocol == "UDP")
	{
		this->ui.ComboBox_instrumentsockettype->clear();
		this->ui.ComboBox_instrumentsockettype->addItem("UDP");
		this->ui.ComboBox_instrumentvisaprotocol->hide();
		this->ui.instrumentVisaTypeLabel->hide();
	}
	else if (protocol == "SSH")
	{
		this->ui.ComboBox_protocol->clear();
		this->ui.ComboBox_protocol->addItem("SSH");
		this->ui.spinBox_sshport->setValue(22);
	}
	else if (protocol == "Telnet")
	{
		this->ui.ComboBox_protocol->clear();
		this->ui.ComboBox_protocol->addItem("Telnet");
		this->ui.spinBox_sshport->setValue(23);
	}
}

void CommunicationProtocolConfigure::showEvent(QShowEvent *event)
{
	
}

void CommunicationProtocolConfigure::init()
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

bool CommunicationProtocolConfigure::connectSolts()
{
	return
		//apply 
		connect(this->ui.pushButton_apply_lan, &QPushButton::clicked, this, &CommunicationProtocolConfigure::applyWithLanWidget)
		&& connect(this->ui.pushButton_apply_gpib, &QPushButton::clicked, this, &CommunicationProtocolConfigure::applyWithGPIBWidget)
		&& connect(this->ui.pushButton_apply_comport, &QPushButton::clicked, this, &CommunicationProtocolConfigure::applyWithComportWidget)
		&& connect(this->ui.pushButton_apply_ssh, &QPushButton::clicked, this, &CommunicationProtocolConfigure::applyWithSSHOrTelnetWidget)
		&& connect(this->ui.pushButton_apply_usb, &QPushButton::clicked, this, &CommunicationProtocolConfigure::applyWithUsbWidget)
		// cancel
		&& connect(this->ui.pushButton_cancel_lan, &QPushButton::clicked, this, &CommunicationProtocolConfigure::cancelWithGPIBWidget)
		&& connect(this->ui.pushButton_cancel_gpib, &QPushButton::clicked, this, &CommunicationProtocolConfigure::cancelWithGPIBWidget)
		&& connect(this->ui.pushButton_cancel_comport, &QPushButton::clicked, this, &CommunicationProtocolConfigure::cancelWithComportWidget)
		&& connect(this->ui.pushButton_cancel_ssh, &QPushButton::clicked, this, &CommunicationProtocolConfigure::cancelWithSSHOrTelnetWidget)
		&& connect(this->ui.pushButton_cancel_usb, &QPushButton::clicked, this, &CommunicationProtocolConfigure::cancelWithUsbWidget)
		&& connect(this->ui.comboBox_baudrate, SIGNAL(currentIndexChanged(int)), this, SLOT(comPortBaudRateCustom(int)))
		;
}

void CommunicationProtocolConfigure::comportFormInit()
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
