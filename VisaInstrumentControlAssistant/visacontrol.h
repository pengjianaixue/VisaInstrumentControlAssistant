#pragma once

#include <QObject>
#include <functional>
#include ".\VisaLib\include\visa.h"
class VisaControl : public QObject
{
	Q_OBJECT
public:
	enum EventType
	{
		Event_IO_Completion,
		Event_Exception

	};
	using VIEVENTHANDLERFN = ViHndlr;
	explicit VisaControl(QObject *parent = nullptr);
	~VisaControl();
	bool IsConnect() const;
	bool registerVisaEventCallBackFn(VIEVENTHANDLERFN eventhandlerfunction, EventType eventtype);
public slots:
	bool sendCommandToInstrument(const QString &commandstr);
	QString readResponseFromInstrument();
	QString sendCommandAndReadResponse(const QString &commandstr);
	bool openInstrument(const QString &instrumentConncetStr);
	bool setVisaTimeOutVaule(unsigned int ms);
signals:
	void hasRecveiveReponseFromInstrument(const QString &);
	void hasSendCommandToInstrumentRet(const QString &,int viStatus);
	void hasSendCommandToInstrument(const QString &);
private:
	bool openInstrumentRM();
private:
	ViSession		m_viSession   = { 0 };
	ViSession		m_viSessionRM = { 0 };
	bool			m_viOpenFlag  = { false };

};
