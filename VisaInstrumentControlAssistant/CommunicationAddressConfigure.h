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

	enum ProtocolType
	{
		TCP_IP,
		UDP,
		GPIB,
		COM,
		SSH,
		Telnet
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
		QString  Prompt;
		~SSHandTelnetInfor() = default;
	};
	struct GPIB
	{
		QString  GPIBAddress;
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
	explicit CommunicationAddressConfigure(QWidget *parent = Q_NULLPTR);
	~CommunicationAddressConfigure();
public slots:
	bool setCurrentTab(const QString& tabname);
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
	DeviceProtocolInfor					m_deviceProtocolInfor;
};
