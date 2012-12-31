#include "qttutorial.h"
#include <qlistview.h>
#include <qstringlistmodel.h>
#include <qstandarditemmodel.h>
#include <qcombobox.h>
#include <qtreeview.h>
#include <qtableview.h>
#include <qcolor.h>
#include "PaletteTableModel.h"


QtTutorial::QtTutorial(QWidget *parent)
	: QMainWindow(parent)
{
	QTableView *tableView = new QTableView();
	tableView->show();

	QTableView *tableView2 = new QTableView();
	tableView2->show();

	// RGBA
	QColor red = QColor(255, 0, 0, 255);
	QColor green = QColor(0, 255, 0, 255);
	QColor blue = QColor(0, 0, 255, 255);
	QColor grey = QColor(155, 155, 155, 255);

	QList<QColor> colors;
	colors.append(red);
	colors.append(green);
	colors.append(blue);
	colors.append(grey);

	QList<QList<QColor>> items;
	for(int i = 0; i < 5; i++)
	{
		items.append(colors);
	}

	PaletteTableModel *model = new PaletteTableModel(items);
	tableView->setModel(model);
	tableView2->setModel(model);

	//model->removeColumns(1, 1);
	//model->removeRows(0,1);

	//model->insertRows(0, 5);
	//model->insertColumns(0, 2);
}

QtTutorial::~QtTutorial()
{
}
