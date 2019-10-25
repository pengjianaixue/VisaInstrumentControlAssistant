#include "stdafx.h"
#include "visainstrumentcontrolassistant.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VisaInstrumentControlAssistant w;
	w.show();
	return a.exec();
}
