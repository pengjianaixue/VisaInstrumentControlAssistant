#include "stdafx.h"
#include "instrumentconfiguration.h"
std::map<QString, int>	instrumentconfiguration::static_deciveTypeMapToIndex;
instrumentconfiguration::instrumentconfiguration(QWidget *parent)
	: QDialog(parent), m_communicationAddressConfigureform(new CommunicationAddressConfigure(this))
	
{
	ui.setupUi(this);
	init();
	if (!conncetSlots())
	{
		QMessageBox::critical(this, "Internal Error", "Connect Slots Error");
		exit(-1);
	}
}

instrumentconfiguration::~instrumentconfiguration()
{

}

void instrumentconfiguration::openConfigureForm()
{
	if (this->ui.tableWidget->item(this->ui.tableWidget->currentRow(),2) 
		&& !this->ui.tableWidget->item(this->ui.tableWidget->currentRow(), 2)->text().isEmpty()
		)
	{
		QString protocoltypename = this->ui.tableWidget->item(this->ui.tableWidget->currentRow(), 2)->text();
		if (protocoltypename == "SSH" || protocoltypename == "Telnet")
		{
			protocoltypename = "SSH/Telnet";
		}
		else if(protocoltypename == "UDP" || protocoltypename == "TCP_IP")
		{
			protocoltypename = "LAN";
		}
		else
		{
			protocoltypename = this->ui.tableWidget->item(this->ui.tableWidget->currentRow(), 2)->text();
		}
		if(m_communicationAddressConfigureform->setCurrentTab(protocoltypename))
			m_communicationAddressConfigureform->show();
	}
	else
	{
		QMessageBox::critical(this, tr("configure error"), tr("please choose the protocol type"));
	}
	
}

void instrumentconfiguration::comboxDelegateEditorSet(QWidget *parent, QComboBox *comboxdelegate, const int &row, const int &column)
{

	if (column == 1)
	{
		comboxdelegate->addItems(QStringList() << "SG_Device" << "SA_Device" << "RFBox_Device" <<"RU_Device"<< "Common_Device");
	}
	else if (column ==2)
	{
		if (!static_cast<QTableWidget*>(parent->parent())->item(row, 1))
		{
			QMessageBox::critical(nullptr, "Instrument type eroor", "Please choose the Instrument Type");
			return ;
		}
		QString devicetype = static_cast<QTableWidget*>(parent->parent())->item(row,1)->text();
		if (devicetype.isEmpty())
		{
			QMessageBox::critical(nullptr, "Instrument type eroor", "Please choose the Instrument Type");
			return;
		}
		else
		{
			comboxdelegate->addItems(getDeviceProtocolChoose(devicetype));
		}
	}
	if (column == 3)
	{
		//comboxdelegate->setEditable(true);
		if (static_cast<QTableWidget*>(parent->parent())->item(row, 1) && static_cast<QTableWidget*>(parent->parent())->item(row, 2))
		{
			QString devicetype   = static_cast<QTableWidget*>(parent->parent())->item(row, 1)->text();
			QString ProtocolType = static_cast<QTableWidget*>(parent->parent())->item(row, 2)->text();
			if (static_deciveTypeMapToIndex[devicetype] <= 2)
			{
				std::list<VisaControl::InstrumentInfor> instrumentInforlist;
				VisaControl visaControl;
				visaControl.findInstrument((VisaControl::InstrumentType)static_deciveTypeMapToIndex[devicetype], getProtocolTypefromProtocolName(ProtocolType),instrumentInforlist);
				comboxdelegate->clear();
				for (const auto &item: instrumentInforlist)
				{
					QString DisplayStr = item.manufacturer + "::" + item.model;
					comboxdelegate->addItem(DisplayStr);
				}
			}
		}
	}
	comboxdelegate->setStyle(QStyleFactory::create("windowsvista"));
	comboxdelegate->setStyleSheet("background - color:rgba(193, 205, 205)");
}
/// JUST FOR TEST
// This function register to the QDelegateTemplate class to setModel data or SetEditorData;
QVariant instrumentconfiguration::delegateComboxDataOp(QComboBox * comboxdelegate, QVariant modeldata, QComboBoxDelegate::DATAOPTYPE dateoptype)
{
	if (dateoptype == QComboBoxDelegate::DATAOPTYPE::SETEDITORDATA)
	{
		comboxdelegate->setCurrentText(modeldata.toString() + "callback" );
		return QVariant();
	}
	else
	{
		QVariant editordata = comboxdelegate->currentText() + "callback";
		return editordata;
	}
}

void instrumentconfiguration::init()
{
	this->ui.tableWidget->setColumnCount(6);
	this->ui.tableWidget->setRowCount(1);
	QStringList headerLables;
	headerLables << "Enable" << "Instrument Type" << "Protocol"<<"Conncet Information String "<<"configure button"<<"Instrument Name";
	this->ui.tableWidget->setHorizontalHeaderLabels(headerLables);
	this->ui.tableWidget->setItemDelegateForColumn(1, &m_qComboBoxDelegateForDeviceType);
	this->ui.tableWidget->setItemDelegateForColumn(2, &m_qComboBoxDelegateForDeviceProtocol);
	this->ui.tableWidget->setItemDelegateForColumn(3, &m_qComboBoxDelegateForDeviceConnectInfor);
	m_qComboBoxDelegateForDeviceProtocol.registerEditorSetFunction(std::forward<QComboBoxDelegate::EDITORSETFUNCTION>(&comboxDelegateEditorSet));
	m_qComboBoxDelegateForDeviceType.registerEditorSetFunction(std::forward<QComboBoxDelegate::EDITORSETFUNCTION>(&comboxDelegateEditorSet));
	m_qComboBoxDelegateForDeviceConnectInfor.registerEditorSetFunction(std::forward<QComboBoxDelegate::EDITORSETFUNCTION>(&comboxDelegateEditorSet));

	//register to function the QDelegateTemplate class to setModel data or SetEditorData;
	/*m_qComboBoxDelegateForDeviceProtocol.registerEditorDataOperationFunction(delegateComboxDataOp);
	m_qComboBoxDelegateForDeviceType.registerEditorDataOperationFunction(delegateComboxDataOp);*/
	
	this->ui.tableWidget->setCellWidget(0, 4, getQToolButtonCellWidget());
	this->ui.tableWidget->setCellWidget(0, 0, getQCheckBoxCellWidget());
	this->ui.tableWidget->setColumnWidth(0, 50);
	this->ui.tableWidget->setColumnWidth(3, 300);
	this->ui.tableWidget->setColumnWidth(4, 120);
	this->ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	this->ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
	//this->ui.tableWidget->setStyle(QStyleFactory::create("Fusion"));
	static_deciveTypeMapToIndex.clear();
	static_deciveTypeMapToIndex.insert({ "SG_Device",0 });
	static_deciveTypeMapToIndex.insert({ "SA_Device",1 });
	static_deciveTypeMapToIndex.insert({ "RFBox_Device",2 });
	static_deciveTypeMapToIndex.insert({ "RU_Device",3 });
	static_deciveTypeMapToIndex.insert({ "Common_Device",4 });
	
}

bool instrumentconfiguration::conncetSlots()
{

	//return connect(this->ui.tableWidget,&QTableWidget::cellClicked,this, &instrumentconfiguration::openConfigureForm);
	return true;
}

QToolButton *instrumentconfiguration::getQToolButtonCellWidget()
{
	QToolButton *configurationToolButton = new QToolButton;
	configurationToolButton->setIcon(QIcon(":/Icon/Resource/Configuration.png"));
	configurationToolButton->setText("Configure");
	configurationToolButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);
	connect(configurationToolButton, &QToolButton::clicked, this, &instrumentconfiguration::openConfigureForm);
	return  configurationToolButton;
}

QWidget *instrumentconfiguration::getQCheckBoxCellWidget()
{
	QCheckBox *instrumentEnableCheckBox = new QCheckBox;
	QWidget *widget = new QWidget(this->ui.tableWidget);
	QHBoxLayout *layout = new QHBoxLayout;
	layout->setSpacing(0); 
	layout->setMargin(0); 
	layout->setAlignment(Qt::AlignJustify);
	layout->addWidget(instrumentEnableCheckBox);
	widget->setLayout(layout);
	/*instrumentEnableCheckBox->setMinimumSize(QSize(50,30));
	instrumentEnableCheckBox->setIcon(QIcon(":/Icon/Resource/Configuration.png"));
	instrumentEnableCheckBox->setText("Configure");*/
	//connect(configurationToolButton, &QToolButton::clicked, this, &instrumentconfiguration::openConfigureForm);
	return  widget;
}

VisaControl::ProtocolType instrumentconfiguration::getProtocolTypefromProtocolName(const QString &protocolname)
{
	if (protocolname == "TCP_IP")
	{
		return VisaControl::ProtocolType::TCP_IP;
	}
	else if (protocolname == "GPIB")
	{
		return VisaControl::ProtocolType::GPIB;
	}
	else if (protocolname == "COM")
	{
		return VisaControl::ProtocolType::COM;
	}
	return VisaControl::ProtocolType(-1);
}

QStringList instrumentconfiguration::getDeviceProtocolChoose(const QString &deviceIndex)
{

	switch (static_deciveTypeMapToIndex[deviceIndex])
	{
		case 0:
		case 1:
		case 2:
			return QStringList() << "TCP_IP" << "GPIB" << "COM";
			break;
		case 3:
			return QStringList() << "COM" << "SSH" << "Telnet";
			break;
		case 4:
			return QStringList() << "TCP_IP" << "UDP" << "GPIB" << "COM" << "SSH" << "Telnet";
			break;
		default:
			QMessageBox::critical(nullptr, "Device type", "Device type Error");
			return QStringList();
			break;
	}
	return QStringList();
	
}

