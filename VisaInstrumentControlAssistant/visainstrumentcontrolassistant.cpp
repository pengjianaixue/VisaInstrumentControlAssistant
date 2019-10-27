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
	
	connect(this->ui.actionAddress_Information, &QAction::triggered, this->m_uiInstrumentDialog, [&] {this->m_uiInstrumentDialog->show(); });
	return false;
}
