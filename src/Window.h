#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <string>
#include "parkingLot.h"
#include <QString>
#include <QThread>

using namespace std;

// class definition 'Window'
class Window : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT
	
	
public:
	Window(); // default constructor - called when a Window is declared without arguments
	void timerEvent( QTimerEvent * );
	void startParkingLot();
	QString spotlabeltext;
	// int spotavailabletext;
	// int spotoccupiedtext;
	QString uidlabeltext;

// internal variables for the window class
private:
	QLabel  *label;
	QLabel	*header;
	QLabel	*welcomemessage;
	QLabel	*spotlabel;
	QLabel	*uidlabel;
	QLabel	*spotavailable;
	QLabel 	*spotoccupied;

	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  *vLayout;  // vertical layout
	QHBoxLayout  *hLayout;  // horizontal layout

	void welcomescreen();
	
public slots:
	void updateWindow(int spotlabeltext, string uidlabeltext);

};

#endif // WINDOW_H
