#include "mshbconfig.h"
#include "mscfgfile.h"

MsHbConfig::MsHbConfig(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	MsCfgFile file;
	file.LoadFile("MsCfg.hb");

	ui.edtWebSocketUrl->setText(file.strWebSocketUrl);
	ui.edtRestUrl->setText(file.strRestUrl);
	ui.edtAccessKey->setText(file.strAccessKey);
	ui.edtSecretKey->setText(file.strSecretKey);
}

MsHbConfig::~MsHbConfig()
{

}

void MsHbConfig::accept()
{
	MsCfgFile file;

	file.strWebSocketUrl = ui.edtWebSocketUrl->text();
	file.strRestUrl = ui.edtRestUrl->text();
	file.strAccessKey = ui.edtAccessKey->text();
	file.strSecretKey = ui.edtSecretKey->text();

	file.SaveFile("MsCfg.hb");

	QDialog::accept();
}
