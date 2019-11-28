#pragma once


#include <QDialog>
#include <map>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "ui_CommunicationProtocolConfigure.h"

class CommunicationProtocolConfigure : public QDialog
{
	Q_OBJECT

public:

	enum ProtocolType
	{
		TCP_IP,
		UDP,
		GPIB,
		COM,
		USB,
		SSH,
		Telnet,
		
	};
	struct LANInfor
	{
		enum SocketType
		{
			TCP_IP,
			UDP
		};
		QString ipAddress;
		QString visaType;
		QString remotePort;
		QString LoaclPort;
		SocketType socketType;
		~LANInfor() = default;

	};
	struct ComPortInfor
	{
		QString comport;
		QString baudRate;
		QString dataBits;
		QString Parity;
		QString stopBits;
		QString flowType;
		~ComPortInfor() = default;
	};
	struct SSHandTelnetInfor
	{
		enum Protocol
		{
			SSH,
			Telnet
		};
		QString  ipAddress;
		QString  port;
		QString  userName;
		QString  password;
		Protocol protocol;
		QString  prompt;
		~SSHandTelnetInfor() = default;
	};
	struct GPIB
	{
		QString  gpibAddress;
		~GPIB() = default;
	};
	struct USB
	{
		QString  USBDevice;
		~USB() = default;
	};

	struct DeviceProtocolInfor
	{
		struct ProtocolInfor
		{
			struct GPIB					gpibInfor;
			struct LANInfor				lanInfor;
			struct ComPortInfor			comportInfor;
			struct USB					usbInfor;
			struct SSHandTelnetInfor	sshOrTelnetInfor;  
		};
		ProtocolInfor protocoinfor;
		ProtocolType protocoltype;
	};
	enum OperationType
	{
		Apply,
		Cancel
	};
	explicit CommunicationProtocolConfigure(QWidget *parent = Q_NULLPTR);
	~CommunicationProtocolConfigure();
	CommunicationProtocolConfigure::DeviceProtocolInfor getCommunicationProtocolInfor() const;
public slots:
	bool setCurrentProtocol(const QString &tabName, const QString &protocolName);
private slots:
	void applyWithLanWidget();
	void applyWithUsbWidget();
	void applyWithComportWidget();
	void applyWithGPIBWidget();
	void applyWithSSHOrTelnetWidget();
	void cancelWithLanWidget();
	void cancelWithUsbWidget();
	void cancelWithComportWidget();
	void cancelWithGPIBWidget();
	void cancelWithSSHOrTelnetWidget();
	void comPortBaudRateCustom(int index);
signals:
	/*
	opeationType 
	{ 
		0 - cancel
		1 - apply
	}
	*/
	void operationCompletion(int opeationType);
	
protected:
	void showEvent(QShowEvent *event) override;
private:
	void init();
	bool connectSolts();
	void comportFormInit();
	void uiConfiguration(const QString &protocol);


private:
	Ui::CommunicationProtocolConfigure ui;
	//QWidget* m_protocolwidget[5] = { nullptr };
	std::map<QString,QWidget*>			m_protocolNameMapToWidget;
	std::map<QWidget*,QString>			m_protocolWidgetMapToName;
	DeviceProtocolInfor					m_deviceProtocolInfor;
};
