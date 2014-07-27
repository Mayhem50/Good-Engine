#ifndef BRDF_H
#define BRDF_H

#include <QtWidgets/QMainWindow>
#include "ui_brdf.h"

class BRDF : public QMainWindow
{
	Q_OBJECT

public:
	BRDF(QWidget *parent = 0);
	~BRDF();

private:
	Ui::BRDFClass ui;
};

#endif // BRDF_H
