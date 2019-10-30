#include "stdafx.h"
#include "visainstrumentcontrolassistant.h"

VisaInstrumentControlAssistant::VisaInstrumentControlAssistant(QWidget *parent)
	: QMainWindow(parent), m_uiInstrumentDialog(new instrumentconfiguration(this))
{
	ui.setupUi(this);
	uiInit();
}

void VisaInstrumentControlAssistant::uiInit()
{
	this->ui.mainToolBar->setStyle(QStyleFactory::create("Fusion"));
	this->ui.splitter->setStretchFactor(0, 7);
	this->ui.splitter->setStretchFactor(1, 3);
	connectSlots();
	
}

bool VisaInstrumentControlAssistant::connectSlots()
{
	
	return	connect(this->ui.actionAddress_Information, &QAction::triggered, this->m_uiInstrumentDialog, [&] {this->m_uiInstrumentDialog->show(); })
			&& connect(this->ui.pushButton_send, &QPushButton::clicked, this,&VisaInstrumentControlAssistant::sendCommandToDevice)
			&& connect(this->ui.pushButton_read, &QPushButton::clicked, this, &VisaInstrumentControlAssistant::readFromDevice)
			&& connect(&this->m_visaControl, &VisaControl::hasRecveiveReponseFromInstrument, this->ui.textBrowser_commanddisplay, &QTextBrowser::append)
			&& connect(&this->m_visaControl, &VisaControl::hasSendCommandToInstrument, this->ui.textBrowser_commanddisplay, &QTextBrowser::append)
		;
}

bool VisaInstrumentControlAssistant::readFromDevice()
{
	QString response =  m_visaControl.readResponseFromInstrument();
	return true;
}

bool VisaInstrumentControlAssistant::sendCommandToDevice()
{
	if (!m_visaControl.IsConnect())
	{
		if (!m_visaControl.openInstrument("TCPIP0::10.166.128.143::inst0::INSTR"))
		{
			QMessageBox::warning(this, "Connect error", "Connect fail");
		}
	}
	if (ui.lineEdit_command->text().isEmpty())
	{
		QMessageBox::warning(this, "Send Waring", "Can't send empty command,please input command");
	}
	return m_visaControl.sendCmdToInstrument(ui.lineEdit_command->text()+"\n");
}
