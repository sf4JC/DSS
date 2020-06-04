#include "AlignmentParameters.h"
#include "ui/ui_AlignmentParameters.h"

#include <ZExcept.h>
#include <Ztrace.h>

#include "Workspace.h"


AlignmentParameters::AlignmentParameters(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::AlignmentParameters),
	workspace(new CWorkspace())
{
    ui->setupUi(this);
	m_Alignment = workspace->value("Stacking/AlignmentTransformation", uint(1)).toUInt();
}

AlignmentParameters::~AlignmentParameters()
{
    delete ui;
}

void AlignmentParameters::onSetActive()
{
	updateControls();
}

void AlignmentParameters::updateControls()
{
    switch (m_Alignment)
    {
        case 0:
            /* Passthrough */
        case 1:
            ui->text->setText(QCoreApplication::translate("AlignmentParameters", "Automatic\n\nThe alignment method is automatically selected depending on the number of available stars."));
			ui->alignAuto->setChecked(true);
            break;
        case 2:
            ui->text->setText(QCoreApplication::translate("AlignmentParameters", "Bilinear Alignment\n\nThe Bilinear Alignment is used in all cases."));
			ui->alignBilinear->setChecked(true);
			break;
        case 3:
            ui->text->setText(QCoreApplication::translate("AlignmentParameters", "Bisquared Alignment\n\nThe Bisquared Alignment is used when at least 25 stars are available, else the Bilinear Alignment method is used."));
			ui->alignBisquared->setChecked(true);
			break;
        case 4:
            ui->text->setText(QCoreApplication::translate("AlignmentParameters", "Bicubic Alignment\n\nThe Bicubic method is used when at least 40 stars are available, then the Bisquared method is used if 25 to 39 stars are available, then the Bilinear method is used when less than 25 stars are available."));
			ui->alignBicubic->setChecked(true);
			break;
        case 5:
            ui->text->setText("");
			ui->alignNone->setChecked(true);
            break;
    }
}

void AlignmentParameters::setAlignment(uint wAlignment)
{
	if (m_Alignment != wAlignment)
	{
		m_Alignment = wAlignment;
		workspace->setValue("Stacking/AlignmentTransformation", uint(m_Alignment));
		updateControls();
	}
};


void AlignmentParameters::on_alignAuto_clicked()
{
    setAlignment(1);
}

void AlignmentParameters::on_alignBilinear_clicked()
{
    setAlignment(2);
}

void AlignmentParameters::on_alignBisquared_clicked()
{
    setAlignment(3);
}

void AlignmentParameters::on_alignBicubic_clicked()
{
    setAlignment(4);
}

void AlignmentParameters::on_alignNone_clicked()
{
    setAlignment(5);
}