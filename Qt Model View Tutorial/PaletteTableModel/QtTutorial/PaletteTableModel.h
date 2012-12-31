#include <QAbstractTableModel>

class PaletteTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	PaletteTableModel(QObject *parent = 0);
	PaletteTableModel(QList<QList<QColor>> colors, QObject *parent = 0);
	~PaletteTableModel();
	
	Qt::ItemFlags flags(const QModelIndex &index) const;

	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int selection, Qt::Orientation orientation, int role) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
	bool insertColumns(int position, int columns, const QModelIndex &parent = QModelIndex());

	bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());
	bool removeColumns(int position, int columns, const QModelIndex &parent = QModelIndex());

private:
	QList<QList<QColor>> colors;
};
