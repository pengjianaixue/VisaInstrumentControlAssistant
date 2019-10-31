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
	~VisaInstrumentControlAssistant();
protected:
	bool eventFilter(QObject *target,QEvent *event) override;
private:
	void uiInit();
	bool connectSlots();
	bool isQueryCommand(const QString &commandstr);
private slots:
	void sendCommandToDevice();
	void readFromDevice();
	void sendCommandAndReadResponseFromDevice();
	void autoSend();
	void addToHistroyList(const QString &commandstr);
signals:
	bool s_sendCommandToDevice(const QString &commandstr);
	QString s_readFromDevice();
	QString s_sendCommandAndReadResponseFromDevice(const QString &commandstr);
private:
	Ui::VisaInstrumentControlAssistantClass ui;
	instrumentconfiguration					*m_uiInstrumentDialog;
	VisaControl								m_visaControl;
	QThread									m_visaProcessThread;


};
