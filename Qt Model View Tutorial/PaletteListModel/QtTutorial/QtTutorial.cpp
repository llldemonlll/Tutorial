#include "qttutorial.h"
#include <qlistview.h>
#include <qstringlistmodel.h>
#include <qstandarditemmodel.h>
#include <qcombobox.h>
#include <qtreeview.h>
#include <qtableview.h>
#include <qcolor.h>
#include "PaletteListModel.h"


QtTutorial::QtTutorial(QWidget *parent)
	: QMainWindow(parent)
{

	// ALL OF OUR VIEWS
	QListView *listView = new QListView();
	listView->show();

	QTreeView *treeView = new QTreeView();
	treeView->show();

	QComboBox *comboBox = new QComboBox();
	comboBox->show();

	QTableView *tableView = new QTableView();
	tableView->show();

	// RGBA
	QColor red = QColor(255, 0, 0, 255);
	QColor green = QColor(0, 255, 0, 255);
	QColor blue = QColor(0, 0, 255, 255);

	QList<QColor> items;
	items.append(red);
	items.append(green);
	items.append(blue);

	int rowCount = 4;
	int columnCount = 6;

	PaletteListModel *model = new PaletteListModel(items);
	
	// Insert at Position 3 -> 5 empty rows
	model->insertRows(3, 5);

	// Remove from position 4 -> 1 row
	// model->removeRows(4,1);

	listView->setModel(model);
	comboBox->setModel(model);
	tableView->setModel(model);
    treeView->setModel(model);
}

QtTutorial::~QtTutorial()
{
}
