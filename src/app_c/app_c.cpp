#include <QApplication>

#include "app_c_window.hpp"

int main(int argc, char* argv[]) 
{
	QApplication app(argc, argv);

	AppCWindow window;
	window.show();

	return app.exec();
}