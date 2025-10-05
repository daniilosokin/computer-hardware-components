#include <QApplication>

#include "app_a_window.hpp"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	AppAWindow window;
	window.show();

	return app.exec();
}