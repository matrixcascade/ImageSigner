#include "imagesigner.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ImageSigner w;
	w.show();
	return a.exec();
}
