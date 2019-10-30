#include "stdafx.h"
#include "instrumentconfiguration.h"

instrumentconfiguration::instrumentconfiguration(QWidget *parent)
	: QDialog(parent), m_communicationAddressConfigureform(new CommunicationAddressConfigure(this))
	
{
	ui.setupUi(this);
	initUi();
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
	m_communicationAddressConfigureform->show();
}

void instrumentconfiguration::comboxDelegateEditorSet(QComboBox *comboxdelegate, const int &row, const int &column)
{
	if (column == 1)
	{
		comboxdelegate->addItems(QStringList() << "SG_Device" << "SA_Device" << "RFBox_Device" <<"RU_Device"<< "Common_Device");
	}
	else if (column ==2)
	{
		comboxdelegate->addItems(QStringList() << "TCP_IP" << "UDP" << "GPIB" << "COM"<<"SSH"<<"Telnet");
	}
	comboxdelegate->setStyle(QStyleFactory::create("windowsvista"));
	comboxdelegate->setStyleSheet("background - color:rgba(193, 205, 205)");
}
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

void instrumentconfiguration::initUi()
{
	this->ui.tableWidget->setColumnCount(6);
	this->ui.tableWidget->setRowCount(1);
	QStringList headerLables;
	headerLables << "" << "Instrument Type" << "Protocol"<<"Conncet Information String "<<"configure button"<<"Instrument Name";
	this->ui.tableWidget->setHorizontalHeaderLabels(headerLables);
	this->ui.tableWidget->setItemDelegateForColumn(1, &m_qComboBoxDelegateForDeviceType);
	this->ui.tableWidget->setItemDelegateForColumn(2, &m_qComboBoxDelegateForDeviceProtocol);
	m_qComboBoxDelegateForDeviceProtocol.registerEditorSetFunction(std::forward<QComboBoxDelegate::EDITORSETFUNCTION>(&comboxDelegateEditorSet));
	m_qComboBoxDelegateForDeviceType.registerEditorSetFunction(std::forward<QComboBoxDelegate::EDITORSETFUNCTION>(&comboxDelegateEditorSet));
	//register to function the QDelegateTemplate class to setModel data or SetEditorData;
	/*m_qComboBoxDelegateForDeviceProtocol.registerEditorDataOperationFunction(delegateComboxDataOp);
	m_qComboBoxDelegateForDeviceType.registerEditorDataOperationFunction(delegateComboxDataOp);*/
	
	this->ui.tableWidget->setCellWidget(0, 4, getQToolButtonCellWidget());
	this->ui.tableWidget->setCellWidget(0, 0, getQCheckBoxCellWidget());
	this->ui.tableWidget->setColumnWidth(0, 20);
	//this->ui.tableWidget->setColumnWidth(1, 100);
	this->ui.tableWidget->setColumnWidth(3, 300);
	this->ui.tableWidget->setColumnWidth(4, 120);
	this->ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	this->ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
	//this->ui.tableWidget->setStyle(QStyleFactory::create("Fusion"));

	
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

QCheckBox *instrumentconfiguration::getQCheckBoxCellWidget()
{
	QCheckBox *instrumentEnableCheckBox = new QCheckBox;
	/*QWidget *widget = new QWidget;
	QGridLayout *layout = new QGridLayout;
	layout->setSpacing(0); 
	layout->setMargin(0); 
	layout->addWidget(instrumentEnableCheckBox);
	widget->setLayout(layout);*/
	//instrumentEnableCheckBox->setMinimumSize(QSize(50,30));
	//instrumentEnableCheckBox->setIcon(QIcon(":/Icon/Resource/Configuration.png"));
	//instrumentEnableCheckBox->setText("Configure");
	instrumentEnableCheckBox->setContentsMargins(QMargins(0, 0, 0, 0));
	//connect(configurationToolButton, &QToolButton::clicked, this, &instrumentconfiguration::openConfigureForm);
	return  instrumentEnableCheckBox;
}

