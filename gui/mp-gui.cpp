#include "MPApp.h"
#include <QMessageBox>

int main(int argc, char **argv)
{
    MPApp app(argc, argv);

    if (!FindC3C()) {
	QMessageBox::critical(NULL, "Error",
	    "Unable to find C3C process.  Please check if C3C is running.");
	return 1;
    }

    app.refresh();
    return app.exec();
}
