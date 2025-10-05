#include <QApplication>

#include "app_b_window.hpp"

int main(int argc, char* argv[]) 
{
	QApplication app(argc, argv);

	AppBWindow window;
	window.show();

	return app.exec();
}