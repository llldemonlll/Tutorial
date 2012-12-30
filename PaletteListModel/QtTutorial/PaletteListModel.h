#include <QAbstractListModel>
#include <qstringlist.h>
#include <qcolor.h>
#include <qlist.h>

class PaletteListModel : public QAbstractListModel
{
	Q_OBJECT

public:
	PaletteListModel(QObject *parent = 0);
	PaletteListModel(QList<QColor> colors, QObject *parent = 0);
	~PaletteListModel();

	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int selection, Qt::Orientation orientation, int role) const;

	int rowCount(const QModelIndex &parent = QModelIndex()) const;

	bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
	bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

	Qt::ItemFlags flags(const QModelIndex &index) const;

private:
	QList<QColor> colors;
};
