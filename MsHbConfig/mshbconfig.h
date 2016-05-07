#ifndef MSHBCONFIG_H
#define MSHBCONFIG_H

#include <QtWidgets/QDialog>
#include "ui_mshbconfig.h"

class MsHbConfig : public QDialog
{
	Q_OBJECT

public:
	MsHbConfig(QWidget *parent = 0);
	~MsHbConfig();

	virtual void accept() override;

private:
	Ui::MsHbConfigClass ui;
};

#endif // MSHBCONFIG_H
