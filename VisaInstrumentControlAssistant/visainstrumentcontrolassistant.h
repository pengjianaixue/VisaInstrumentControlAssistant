#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_visainstrumentcontrolassistant.h"

class VisaInstrumentControlAssistant : public QMainWindow
{
	Q_OBJECT

public:
	VisaInstrumentControlAssistant(QWidget *parent = Q_NULLPTR);

private:
	Ui::VisaInstrumentControlAssistantClass ui;
};
