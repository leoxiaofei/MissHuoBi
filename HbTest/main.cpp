#include "misshuobi.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MissHuoBi w;
	w.show();
	return a.exec();
}
