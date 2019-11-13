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
		//m_protocolwidget[i] = this->ui.tabWidget_protocol_configure->currentWidget();
		m_protocolNameMapToWidget.insert({ this->ui.tabWidget_protocol_configure->currentWidget()->accessibleName(),
			this->ui.tabWidget_protocol_configure->currentWidget() });
		m_protocolWidgetMapToName.insert({ this->ui.tabWidget_protocol_configure->currentWidget() ,this->ui.tabWidget_protocol_configure->currentWidget()->accessibleName() });
		
	}
	this->ui.tabWidget_protocol_configure->clear();
	//LAN configuration init
	this->ui.ComboBox_instrumentsockettype->addItems(QStringList() << "INST" << "SCOKET");
	

	
}

bool CommunicationAddressConfigure::connectSolts()
{	

	return false;
}

void CommunicationAddressConfigure::comportFormInit()
{
	QStringList vaildSerialPortName; 
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) 
	{
		vaildSerialPortName << info.portName();
		qDebug() << "serialPortName:" << info.portName(); 
	}
	this->ui.comboBox_comport->addItems(vaildSerialPortName);


}
