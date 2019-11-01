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

bool VisaControl::findInstrument(InstrumentType instrumenttype, ProtocolType protocoltype, std::list<InstrumentInfor> &instrumentfindlist)
{
	ViFindList vifindlist = 0;
	ViUInt32   virecnt = 0;
	ViSession viseeionfind;
	ViSession viseeioninstrument;
	ViChar    desc[1024] = {0};
	ViChar	  instrumentinfor[256] = { 0 };
	//QList<std::pair<QString, QString>> instrumentfindlist;
	InstrumentInfor instrumentinforstruct;
	QString manufacturer;
	QString model;
	QString connectStr;
	ViStatus openstatus = viOpenDefaultRM(&viseeionfind);
	if (openstatus != VI_SUCCESS)
	{
		return false;
	}
	ViStatus findret = viFindRsrc(viseeionfind, const_cast<ViString>(getInstrumentFindExpr(instrumenttype, protocoltype).toStdString().c_str()), 
		&vifindlist, &virecnt, desc);
	if (findret != VI_SUCCESS)
	{
		return false;
	}
	for (size_t i = 0; i < virecnt; i++)
	{
		ViStatus IOstatus = viOpen(viseeionfind, desc, VI_NULL, VI_NULL, &viseeioninstrument);
		if (IOstatus != VI_SUCCESS)
		{
			viFindNext(vifindlist, desc);
			continue;
		}
		ViUInt32 cnt = 256;
		ViPUInt32 recnt = 0;
		IOstatus = viPrintf(viseeioninstrument, "*IDN?\n");
		IOstatus = viRead(viseeioninstrument, (ViPBuf)instrumentinfor, cnt, recnt);
		//IOstatus = viQueryf(viseeioninstrument,"*IDN?\n","%s", instrumentinfor);
		if (IOstatus == VI_SUCCESS)
		{
			QString querystr = instrumentinfor;
			if (querystr.split(",").length() > 2)
			{
				instrumentinforstruct.manufacturer = querystr.split(",").at(0);
				instrumentinforstruct.model = querystr.split(",").at(1);
				instrumentinforstruct.connectStr = desc;
				instrumentfindlist.push_back(instrumentinforstruct);
			}
		}
		viClose(viseeioninstrument);
		viFindNext(vifindlist, desc);
	}

}
bool VisaControl::openInstrumentRM()
{
	ViStatus openstatus = viOpenDefaultRM(&m_viSessionRM);
	return openstatus == VI_SUCCESS;
}

QString VisaControl::getInstrumentFindExpr(InstrumentType instrumenttype, ProtocolType protocoltype)
{
	QString findexpr;
	switch (instrumenttype)
	{
		case VisaControl::SG:
			break;
		case VisaControl::SA:
			break;
		case VisaControl::NA:
			break;
		case VisaControl::PRM:
			break;
		default:
			break;
	}
	switch (protocoltype)
	{
		case VisaControl::TCP_IP:
			findexpr = "TCPIP0?*::INSTR";
			break;
		case VisaControl::GPIB:
			findexpr = "GPIB[0-9]*::?*INSTR";
			break;
		case VisaControl::COM:
			findexpr = "ASRL[0-9]*::?*INSTR";
			break;
		default:
			break;
	}
	return findexpr;
}

bool VisaControl::sendCommandToInstrument(const QString &commandstr)
{
	ViStatus sendstatus  = viPrintf(m_viSession, const_cast<ViRsrc>(commandstr.toStdString().c_str()));
	QString commandstremit = std::move(commandstr);
	emit hasSendCommandToInstrument("Send Command: "+ commandstremit.replace("\n","") + "-->" + "SendStatus: " + (sendstatus == VI_SUCCESS ? "Success": ("error code--"+QString::number(sendstatus))));
	emit hasSendCommandToInstrumentRet(commandstremit.replace("\n", ""), sendstatus);
	return sendstatus == VI_SUCCESS;
}
