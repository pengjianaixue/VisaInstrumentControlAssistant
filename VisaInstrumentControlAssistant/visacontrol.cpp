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

QString VisaControl::readResponseFromInstrument()
{

	char readbuf[1024] = { 0 };
	ViUInt32  retlen = 0;
	ViStatus readstatus  =  viRead(m_viSession, (ViPBuf)readbuf, 1024, &retlen);
	if (!readstatus)
	{
		emit recveiveReponseFromInstrument(QString(std::string(readbuf).c_str()));
		return QString(std::string(readbuf).c_str());
	}
	else if (readstatus == VI_ERROR_TMO)
	{
		return QString("read time out");
	}
	
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

bool VisaControl::sendCmdToInstrument(const QString &commandstr)
{
	ViStatus sendstatus  = viPrintf(m_viSession, const_cast<ViRsrc>(commandstr.toStdString().c_str()));
	return sendstatus == VI_SUCCESS;
}
