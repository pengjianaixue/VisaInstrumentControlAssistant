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
	if (m_protocolwidgetmap.find(tabname)!= m_protocolwidgetmap.cend())
	{
		
		this->ui.tabWidget_protocol_configure->addTab(m_protocolwidgetmap[tabname], tabname);
		return true;
	}
	QMessageBox::critical(this, "Protocol type error", "Protocol type haven't found");
	return false;
	
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
		m_protocolwidgetmap.insert({ this->ui.tabWidget_protocol_configure->currentWidget()->accessibleName(),
			this->ui.tabWidget_protocol_configure->currentWidget() });
		
	}
	this->ui.tabWidget_protocol_configure->clear();
	//this->ui.tabWidget_protocol_configure->addTab(m_protocolwidgetmap["LAN"], "LAN");
	
}
