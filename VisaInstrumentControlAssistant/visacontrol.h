#pragma once

#include <QObject>
#include ".\VisaLib\include\visa.h"
class VisaControl : public QObject
{
	Q_OBJECT
public:
	VisaControl(QObject *parent);
	~VisaControl();
public slots:
	bool sendCmdToInstrument(const QString &commandstr);
	QString readResponseFromInstrument();
	bool openInstrument(const QString &instrumentConncetStr);
	bool setVisaTimeOutVaule(unsigned int ms);
signals:
	void recveiveReponseFromInstrument(const QString &);
private:
	bool openInstrumentRM();
private:
	ViSession		m_viSession   = { 0 };
	ViSession		m_viSessionRM = { 0 };
	bool			m_viOpenFlag  = { false };

};
