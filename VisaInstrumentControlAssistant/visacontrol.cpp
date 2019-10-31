#include "stdafx.h"
#include "visacontrol.h"

VisaControl::VisaControl(QObject *parent)
	: QObject(parent)
{
	
}

VisaControl::~VisaControl()
{
	if (m_viOpenFlag)
	{
		viClose(m_viSessionRM);
		viClose(m_viSession);
	}
}

bool VisaControl::IsConnect() const
{

	return m_viOpenFlag;
}

bool VisaControl::registerVisaEventCallBackFn(VIEVENTHANDLERFN eventhandlerfunction, EventType eventtype)
{
	if (!eventhandlerfunction)
	{
		return false;
	}
	int vi_eventype = 0;
	if (eventtype == EventType::Event_IO_Completion)
	{
		vi_eventype = VI_EVENT_IO_COMPLETION;
	}
	else
	{
		vi_eventype = VI_EVENT_EXCEPTION;
	}
	if (VI_SUCCESS == viInstallHandler(m_viSession, vi_eventype, eventhandlerfunction, nullptr))
	{
		viEnableEvent(m_viSession, vi_eventype, VI_HNDLR,VI_NULL);
		return true;
	}
	return false;
}

QString VisaControl::readResponseFromInstrument()
{
	
	char readbuf[1024] = { 0 };
	ViUInt32  retlen = 0;
	ViStatus readstatus  =  viRead(m_viSession, (ViPBuf)readbuf, 1024, &retlen);
	if (!readstatus)
	{
		emit hasRecveiveReponseFromInstrument(QString(std::string(readbuf).c_str()));
		return QString(std::string(readbuf).c_str());
	}
	else if (readstatus == VI_ERROR_TMO)
	{
		return QString("read time out");
	}
	return QString("read fail");
	
}

QString VisaControl::sendCommandAndReadResponse(const QString &commandstr)
{
	if (m_viOpenFlag)
	{
		if (sendCommandToInstrument(commandstr))
		{
			return readResponseFromInstrument();
		}
		else
		{
			return QString();
		}
	}
	return QString();
}

bool VisaControl::openInstrument(const QString &instrumentConncetStr)
{
	if (m_viOpenFlag)
	{
		viClose(m_viSessionRM);
		viClose(m_viSession);
	}
	if (!openInstrumentRM())
		return false;
	ViStatus openstatus = -1;
	openstatus = viOpen(m_viSessionRM,  const_cast<ViRsrc>(instrumentConncetStr.toStdString().c_str()), VI_NULL, VI_NULL, &m_viSession);
	if (m_viSession && openstatus == VI_SUCCESS)
	{
		m_viOpenFlag = true;
		viPrintf(m_viSession, "*IDN?\n");
		readResponseFromInstrument();
		viSetAttribute(m_viSession, VI_ATTR_TMO_VALUE, 60000);
	}
	return openstatus == VI_SUCCESS;
}

bool VisaControl::setVisaTimeOutVaule(unsigned int ms)
{
	if (!m_viOpenFlag)
	{
		return false;
	}
	return viSetAttribute(m_viSession, VI_ATTR_TMO_VALUE, ms) == 0;
}




bool VisaControl::openInstrumentRM()
{
	ViStatus openstatus = viOpenDefaultRM(&m_viSessionRM);
	return openstatus == VI_SUCCESS;
}

bool VisaControl::sendCommandToInstrument(const QString &commandstr)
{
	ViStatus sendstatus  = viPrintf(m_viSession, const_cast<ViRsrc>(commandstr.toStdString().c_str()));
	QString commandstremit = std::move(commandstr);
	emit hasSendCommandToInstrument("Send Command: "+ commandstremit.replace("\n","") + "-->" + "SendStatus: " + (sendstatus == VI_SUCCESS ? "Success": ("error code--"+QString::number(sendstatus))));
	emit hasSendCommandToInstrumentRet(commandstremit.replace("\n", ""), sendstatus);
	return sendstatus == VI_SUCCESS;
}
