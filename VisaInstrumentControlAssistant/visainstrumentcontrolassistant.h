#pragma once

#include "ui_visainstrumentcontrolassistant.h"
#include <QtWidgets/QMainWindow>
#include "visacontrol.h"
#include "instrumentconfiguration.h"

class VisaInstrumentControlAssistant : public QMainWindow
{
	Q_OBJECT

public:
	VisaInstrumentControlAssistant(QWidget *parent = Q_NULLPTR);
private:
	void uiInit();
	bool connectSlots();
private slots:
	bool sendCommandToDevice();
	bool readFromDevice();
private:
	Ui::VisaInstrumentControlAssistantClass ui;
	instrumentconfiguration					*m_uiInstrumentDialog;
	VisaControl								m_visaControl;


};
