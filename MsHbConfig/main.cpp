#include "mshbconfig.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MsHbConfig w;
	w.show();
	return a.exec();
}
