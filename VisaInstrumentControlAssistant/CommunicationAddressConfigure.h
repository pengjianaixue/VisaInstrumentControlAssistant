#pragma once

#include <QDialog>
#include "ui_CommunicationAddressConfigure.h"

class CommunicationAddressConfigure : public QDialog
{
	Q_OBJECT

public:
	CommunicationAddressConfigure(QWidget *parent = Q_NULLPTR);
	~CommunicationAddressConfigure();
protected:
	void showEvent(QShowEvent *event) override;

private:
	Ui::CommunicationAddressConfigure ui;
};
