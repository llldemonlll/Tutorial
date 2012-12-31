#include "PaletteListModel.h"
#include <qpixmap.h>
#include <qicon.h>
#include <qstring.h>

PaletteListModel::PaletteListModel(QObject* parent)
	: QAbstractListModel(parent)
{
}

PaletteListModel::PaletteListModel(QList<QColor> items, QObject* parent)
	: QAbstractListModel(parent)
{
	colors = items;
}

PaletteListModel::~PaletteListModel()
{
}

int PaletteListModel::rowCount(const QModelIndex& ) const
{
	return colors.size();
}

QVariant PaletteListModel::data(const QModelIndex &index, int role) const
{
	if(!index.isValid())
		return QVariant();

	if(role == Qt::DisplayRole)
	{
		return colors.at(index.row());
	}

	if(role == Qt::DecorationRole)
	{
		int row = index.row();
		QColor color = colors.value(row);

		QPixmap pixmap(26, 26);
		pixmap.fill(color);

		QIcon icon(pixmap);

		return icon;
	}

	if(role == Qt::EditRole)
	{
		return colors.at(index.row()).name();
	}

	if(role == Qt::ToolTipRole)
	{
		return "Hex code: " + colors.at(index.row()).name();
	}

	return QVariant();
}

QVariant PaletteListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role != Qt::DisplayRole)
		return QVariant();

	if(orientation == Qt::Horizontal)
	{
		switch(section)
		{
		case 0:
			return ("Color");

		default:
			return QVariant();
		}
	}
	else
	{
		return QString("Color %1").arg(section);
	}
}

bool PaletteListModel::insertRows(int position, int rows, const QModelIndex &index)
{
	beginInsertRows(QModelIndex(), position, position + rows - 1);

	for(int row = 0; row < rows; row++)
	{
		colors.insert(position, QColor(0, 0, 0, 255));
	}

	endInsertRows();
	return true;
}

bool PaletteListModel::removeRows(int position, int rows, const QModelIndex &index)
{
	beginRemoveRows(QModelIndex(), position, position + rows - 1);

	for(int row = 0; row < rows; ++row)
	{
		colors.removeAt(position);
	}

	endRemoveRows();
	return true;
}
	
bool PaletteListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(index.isValid() && role == Qt::EditRole)
	{
		int row = index.row();

		QColor color = QColor(value.value<QColor>());

		colors.replace(row, color);
		emit(dataChanged(index, index));

		return true;
	}

	return false;
}

Qt::ItemFlags PaletteListModel::flags(const QModelIndex &index) const
{
	if(!index.isValid())
		return Qt::ItemIsEnabled;

	return QAbstractListModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}