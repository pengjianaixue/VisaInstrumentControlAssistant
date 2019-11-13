#pragma once


#include <QDialog>
#include <map>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "ui_CommunicationAddressConfigure.h"

class CommunicationAddressConfigure : public QDialog
{
	Q_OBJECT

public:
	CommunicationAddressConfigure(QWidget *parent = Q_NULLPTR);
	~CommunicationAddressConfigure();
public slots:
	bool setCurrentTab(const QString& tabname);
	void applyLanWidget();
	void applyUsbWidget();
	void applyComportWidget();
	void applyGPIBWidget();
	void applySSHOrTelnetWidget();
protected:
	void showEvent(QShowEvent *event) override;
private:
	void init();
	bool connectSolts();
	void comportFormInit();

private:
	Ui::CommunicationAddressConfigure ui;
	//QWidget* m_protocolwidget[5] = { nullptr };
	std::map<QString,QWidget*>			m_protocolNameMapToWidget;
	std::map<QWidget*,QString>			m_protocolWidgetMapToName;
};
