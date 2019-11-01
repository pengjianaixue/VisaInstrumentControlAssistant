#pragma once

#include <QDialog>
#include <map>
#include "ui_CommunicationAddressConfigure.h"

class CommunicationAddressConfigure : public QDialog
{
	Q_OBJECT

public:
	CommunicationAddressConfigure(QWidget *parent = Q_NULLPTR);
	~CommunicationAddressConfigure();
public slots:
	bool setCurrentTab(const QString& tabname);
protected:
	void showEvent(QShowEvent *event) override;
private:
	void init();

private:
	Ui::CommunicationAddressConfigure ui;
	//QWidget* m_protocolwidget[5] = { nullptr };
	std::map<QString,QWidget*>			m_protocolwidgetmap;
};
