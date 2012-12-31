#include "qttutorial.h"
#include <qapplication.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QtTutorial window;
	window.show();

	return app.exec();
}
