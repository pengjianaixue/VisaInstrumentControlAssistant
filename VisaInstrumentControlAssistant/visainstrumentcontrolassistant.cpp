#include "stdafx.h"
#include "visainstrumentcontrolassistant.h"

VisaInstrumentControlAssistant::VisaInstrumentControlAssistant(QWidget *parent)
	: QMainWindow(parent), m_uiInstrumentDialog(new instrumentconfiguration(this))
{
	ui.setupUi(this);
	uiInit();
	m_visaControl.moveToThread(&m_visaProcessThread);
	m_visaProcessThread.start();
}

VisaInstrumentControlAssistant::~VisaInstrumentControlAssistant()
{
	m_visaProcessThread.terminate();
}

void VisaInstrumentControlAssistant::uiInit()
{
	this->ui.mainToolBar->setStyle(QStyleFactory::create("Fusion"));
	this->ui.splitter->setStretchFactor(0, 7);
	this->ui.splitter->setStretchFactor(1, 3);
	if (!connectSlots())
	{
		QMessageBox::critical(this, "internal Error", "Connect slots fail");
		exit(-1);
	}
}

bool VisaInstrumentControlAssistant::connectSlots()
{
	
	return	connect(this->ui.actionAddress_Information, &QAction::triggered, this->m_uiInstrumentDialog, [&] {this->m_uiInstrumentDialog->show(); })
			&& connect(this->ui.pushButton_send, &QPushButton::clicked, this,&VisaInstrumentControlAssistant::sendCommandToDevice)
			&& connect(this->ui.pushButton_read, &QPushButton::clicked, this, &VisaInstrumentControlAssistant::readFromDevice)
			&& connect(this->ui.pushButton_sendandread, &QPushButton::clicked, this, &VisaInstrumentControlAssistant::sendCommandAndReadResponseFromDevice)
			&& connect(&this->m_visaControl, &VisaControl::hasRecveiveReponseFromInstrument, this->ui.textBrowser_commanddisplay, &QTextBrowser::append)
			&& connect(&this->m_visaControl, &VisaControl::hasSendCommandToInstrument, this->ui.textBrowser_commanddisplay, &QTextBrowser::append)
			&& connect(this->ui.pushButton_clean, &QPushButton::clicked, this->ui.textBrowser_commanddisplay, &QTextBrowser::clear)
			&& connect(this, &VisaInstrumentControlAssistant::s_sendCommandToDevice, this, &VisaInstrumentControlAssistant::sendCommandToDevice)
			&& connect(this, &VisaInstrumentControlAssistant::s_readFromDevice, this, &VisaInstrumentControlAssistant::readFromDevice)
			&& connect(this, &VisaInstrumentControlAssistant::s_sendCommandAndReadResponseFromDevice, this, &VisaInstrumentControlAssistant::sendCommandAndReadResponseFromDevice)
		;
}

bool VisaInstrumentControlAssistant::isQueryCommand(const QString &commandstr)
{
	return commandstr.endsWith("?");
}

void VisaInstrumentControlAssistant::readFromDevice()
{
	emit s_readFromDevice();
	//QString response =  m_visaControl.readResponseFromInstrument();
}

void VisaInstrumentControlAssistant::sendCommandAndReadResponseFromDevice()
{
	emit s_sendCommandAndReadResponseFromDevice(std::move(ui.lineEdit_command->text() + "\n"));
	//m_visaControl.sendCommandAndReadResponse(ui.lineEdit_command->text() + "\n");
}

void VisaInstrumentControlAssistant::autoSend()
{
	if (!ui.lineEdit_command->text().isEmpty() && isQueryCommand(ui.lineEdit_command->text()))
	{
		emit s_sendCommandAndReadResponseFromDevice(std::move(ui.lineEdit_command->text()+"\n"));
		//m_visaControl.sendCommandAndReadResponse(std::move(ui.lineEdit_command->text()));
	}
	else
	{
		emit s_sendCommandToDevice(std::move(ui.lineEdit_command->text()));
	}
	
}

void VisaInstrumentControlAssistant::sendCommandToDevice()
{
	if (!m_visaControl.IsConnect())
	{
		if (!m_visaControl.openInstrument("TCPIP0::10.166.128.151::inst0::INSTR"))
		{
			QMessageBox::warning(this, "Connect error", "Connect fail");
		}
	}
	if (ui.lineEdit_command->text().isEmpty())
	{
		QMessageBox::warning(this, "Send Waring", "Can't send empty command,please input command");
	}
	emit s_sendCommandToDevice(ui.lineEdit_command->text() + "\n");
	return;
}
