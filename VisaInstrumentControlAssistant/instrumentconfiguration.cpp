#include "stdafx.h"
#include "instrumentconfiguration.h"

//static member dec
//std::map<QString, int>	instrumentconfiguration::static_deciveTypeMapToIndex;
//std::list<VisaControl::InstrumentInfor> instrumentconfiguration::static_instrumentInforlist;
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

void instrumentconfiguration::setConncetStrInfor(const QString &instrumentmodel)
{
	auto instrumentinforlist = instrumentmodel.split("->");
	if (instrumentinforlist.length() == 3)
	{
		int row = this->ui.tableWidget->currentRow();
		this->ui.tableWidget->setItem(this->ui.tableWidget->currentRow(), 5, new QTableWidgetItem(instrumentinforlist.at(0) + "::" + instrumentinforlist.at(1)));
		m_connectStr = instrumentinforlist.at(2);
		//this->ui.tableWidget->setItem(this->ui.tableWidget->currentRow(), 3, new QTableWidgetItem(instrumentinforlist.at(2)));		
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
			if (m_deciveTypeMapToIndex[devicetype] <= 2)
			{
				m_instrumentInforlist.clear();
				VisaControl visaControl;
				visaControl.findInstrument((VisaControl::InstrumentType)m_deciveTypeMapToIndex[devicetype], getProtocolTypefromProtocolName(ProtocolType), m_instrumentInforlist);
				comboxdelegate->clear();
				for (const auto &item: m_instrumentInforlist)
				{
					QString DisplayStr = item.manufacturer + "->" + item.model + "->" + item.connectStr;
					comboxdelegate->addItem(DisplayStr);
				}
				//connect(comboxdelegate, &QComboBox::currentTextChanged, this, &instrumentconfiguration::setConncetStrInfor);
				// use the function param to specil the function
				connect(comboxdelegate, SIGNAL(activated(const QString&)), this, SLOT(setConncetStrInfor(const QString &))); 
			}
		}
	}
	comboxdelegate->setStyle(QStyleFactory::create("windowsvista"));
	comboxdelegate->setStyleSheet("background - color:rgba(193, 205, 205)");
}

// This function register to the QDelegateTemplate class to setModel data or SetEditorData;
QVariant instrumentconfiguration::delegateComboxDataOp(QComboBox * comboxdelegate, QVariant modeldata, QComboBoxDelegate::DATAOPTYPE dateoptype, const QModelIndex &index)
{
	if (dateoptype == QComboBoxDelegate::DATAOPTYPE::SETMODELDATA )
	{
		if (index.column() != 3)
		{
			return comboxdelegate->currentText();
		}		
	}
	return QVariant(m_connectStr);
}

void instrumentconfiguration::init()
{
	this->ui.tableWidget->setColumnCount(6);
	this->ui.tableWidget->setRowCount(2);
	QStringList headerLables;
	headerLables << "Enable" << "Instrument Type" << "Protocol"<<"Conncet Information String "<<"configure button"<<"Instrument Name";
	this->ui.tableWidget->setHorizontalHeaderLabels(headerLables);
	this->ui.tableWidget->setItemDelegateForColumn(1, &m_qComboBoxDelegateForDeviceType);
	this->ui.tableWidget->setItemDelegateForColumn(2, &m_qComboBoxDelegateForDeviceProtocol);
	this->ui.tableWidget->setItemDelegateForColumn(3, &m_qComboBoxDelegateForDeviceConnectInfor);
	m_qComboBoxDelegateForDeviceProtocol.registerEditorSetFunction(std::bind(&instrumentconfiguration::comboxDelegateEditorSet,this,std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_qComboBoxDelegateForDeviceType.registerEditorSetFunction(std::bind(&instrumentconfiguration::comboxDelegateEditorSet, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_qComboBoxDelegateForDeviceConnectInfor.registerEditorSetFunction(std::bind(&instrumentconfiguration::comboxDelegateEditorSet, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	m_qComboBoxDelegateForDeviceConnectInfor.registerEditorDataOperationFunction(std::bind(&instrumentconfiguration::delegateComboxDataOp, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));	
	this->ui.tableWidget->setCellWidget(0, 4, getQToolButtonCellWidget());
	this->ui.tableWidget->setCellWidget(0, 0, getQCheckBoxCellWidget());
	this->ui.tableWidget->setColumnWidth(0, 50);
	this->ui.tableWidget->setColumnWidth(2, 70);
	this->ui.tableWidget->setColumnWidth(3, 400);
	this->ui.tableWidget->setColumnWidth(4, 100);
	this->ui.tableWidget->setColumnWidth(5, 150);
	this->ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	this->ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
	/*QTableWidgetItem *addrow = new QTableWidgetItem();
	addrow->setIcon(QIcon(":/Icon/Resource/add.png"));
	this->ui.tableWidget->setVerticalHeaderItem(1, addrow);*/
	//this->ui.tableWidget->setSpan(1, 0, 1, 5);
	//this->ui.tableWidget->setRowHidden(1, true);
	//this->ui.tableWidget->setFrameShape(QFrame::NoFrame);
	//this->ui.tableWidget->setStyle(QStyleFactory::create("Fusion"));
	m_deciveTypeMapToIndex.clear();
	m_deciveTypeMapToIndex.insert({ "SG_Device",0 });
	m_deciveTypeMapToIndex.insert({ "SA_Device",1 });
	m_deciveTypeMapToIndex.insert({ "RFBox_Device",2 });
	m_deciveTypeMapToIndex.insert({ "RU_Device",3 });
	m_deciveTypeMapToIndex.insert({ "Common_Device",4 });
	
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

	switch (m_deciveTypeMapToIndex[deviceIndex])
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

