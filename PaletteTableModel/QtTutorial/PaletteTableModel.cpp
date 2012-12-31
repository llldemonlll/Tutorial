#include "PaletteTableModel.h"
#include <qpixmap.h>
#include <qicon.h>
#include <qstring.h>
#include <qcolor.h>
#include <qdebug.h>

PaletteTableModel::PaletteTableModel(QObject* parent)
	: QAbstractTableModel(parent)
{
}

PaletteTableModel::PaletteTableModel(QList<QList<QColor>> items, QObject* parent)
	: QAbstractTableModel(parent)
{
	colors = items;
}

PaletteTableModel::~PaletteTableModel()
{
}

int PaletteTableModel::rowCount(const QModelIndex&) const
{
	return colors.size();
}

int PaletteTableModel::columnCount(const QModelIndex&) const
{
	return colors[0].size();
}

Qt::ItemFlags PaletteTableModel::flags(const QModelIndex &index) const
{
	if(!index.isValid())
		return Qt::ItemIsEnabled;

	return QAbstractTableModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}

QVariant PaletteTableModel::data(const QModelIndex &index, int role) const
{
	if(!index.isValid())
		return QVariant();

	if(role == Qt::EditRole)
	{
		int row = index.row();
		int column = index.column();

		return colors[row][column].name();
	}
	
	if(role == Qt::ToolTipRole)
	{
		int row = index.row();
		int column = index.column();

		return "Hex code: " + colors[row][column].name();
	}

	if(role == Qt::DecorationRole)
	{
		int row = index.row();
		int column = index.column();

		QColor color = colors[row][column];

		QPixmap pixmap(26, 26);
		pixmap.fill(color);

		QIcon icon(pixmap);

		return icon;
	}

	if(role == Qt::DisplayRole)
	{
		int row = index.row();
		int column = index.column();
		
		return colors[row][column];
	}

	return QVariant();
}

QVariant PaletteTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role != Qt::DisplayRole)
		return QVariant();

	if(orientation == Qt::Horizontal)
	{
		return QString("Column %1").arg(section); 
	}
	else // vertical
	{
		return QString("Row %1").arg(section);
	}
}

bool PaletteTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(!index.isValid() || role != Qt::EditRole)
		return false;
	
	int row = index.row();
	int column = index.column();

	colors[row][column] = QColor(value.value<QColor>());
	emit(dataChanged(index, index));

	return true;
}


bool PaletteTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
	beginInsertRows(QModelIndex(), position, position + rows - 1);

	QList<QColor> temp;
	for(int i = 0; i < this->columnCount(); i++)
	{
		temp.append(QColor(0, 0, 0, 255));
	}

	for(int row = 0; row < rows; row++)
	{
		colors.insert(position, temp);
	}

	endInsertRows();
	return true;
}

bool PaletteTableModel::insertColumns(int position, int columns, const QModelIndex &index)
{
	int rows = rowCount();
	beginInsertColumns(QModelIndex(), position, position + columns - 1);
	
	for(int row = 0; row < rows; ++row)
	{
		for(int column = position; column < columns; ++column)
		{
			colors[row].insert(position, QColor("#000000"));
		}
	}

	endInsertColumns();
	return true;
}

bool PaletteTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
	beginRemoveRows(index, position, position + rows - 1);

	for(int row = 0; row < rows; ++row)
	{
		colors.removeAt(position);
	}

	endRemoveRows();
	return true;
}

bool PaletteTableModel::removeColumns(int position, int columns, const QModelIndex &index)
{
	int rows = rowCount();
	beginRemoveRows(index, position, position + columns - 1);

	for(int row = 0; row < rows; ++row)
	{
		for(int column = 0; column < columns; ++column)
		{
			colors[row].removeAt(position);
		}
	}

	endRemoveRows();
	return true;
}