#include <QApplication>
#include <QPushButton>

#include "c3c.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	ReadC3CMemory(0, 0, 0);
	QPushButton hello("Hello world!");
	hello.resize(100, 30);

	hello.show();
	return app.exec();
}
