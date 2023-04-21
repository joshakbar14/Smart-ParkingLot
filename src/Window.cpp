#include "Window.h"
#include <iostream>
#include "parkingLot.h"
#include <QString>
#include <QDebug>

using namespace std;

Window::Window()
{
	
	QFont font("Arial", 25);

	label = new QLabel("Test");
	QPixmap pixmap("Capture.png");

	// GUI Stuff
	label->setPixmap(pixmap);
	label->setAlignment(Qt::AlignCenter);

	header = new QLabel("Welcome to SpaceIT!");
	header->setFont(font);
	header->setAlignment(Qt::AlignCenter);

	welcomemessage = new QLabel("Scan your card");
	welcomemessage->setFont(font);
	welcomemessage->setAlignment(Qt::AlignCenter);

	spotlabel = new QLabel("Designated Spot");
	spotlabel->setFont(font);
	spotlabel->setAlignment(Qt::AlignCenter);

	uidlabel = new QLabel("UID");
    uidlabel->setFont(font);
	uidlabel->setAlignment(Qt::AlignCenter);

	spotavailable = new QLabel("Available Spot");
    spotavailable->setFont(font);
	spotavailable->setAlignment(Qt::AlignCenter);

	spotoccupied = new QLabel("Occupied Spot");
	spotoccupied->setFont(font);
	spotoccupied->setAlignment(Qt::AlignCenter);
	
	// set up the layout
	vLayout = new QVBoxLayout();
	vLayout->addWidget(label);
	vLayout->addWidget(header);
	vLayout->addWidget(welcomemessage);
	vLayout->addWidget(spotlabel);
	vLayout->addWidget(uidlabel);
	vLayout->addWidget(spotavailable);
	vLayout->addWidget(spotoccupied);

	// plot to the left
	hLayout = new QHBoxLayout();
	hLayout->addLayout(vLayout);

	setLayout(hLayout);
	
}

void Window::updateWindow(int spottext, string uidtext){
	spotlabeltext = QString::number(spottext);
	uidlabeltext = QString::fromStdString(uidtext);
	cout << "This is in the window " << spottext << " and " << uidtext << endl;
	qDebug() << spotlabeltext << " " << uidlabeltext;
	QApplication::processEvents();
}

void Window::startParkingLot(){
	parkingLot park(2, (Window*)this);
	QApplication::processEvents();
	startTimer(40);

}



void Window::timerEvent( QTimerEvent * )
{
	spotlabel->setText(spotlabeltext);
	uidlabel->setText(uidlabeltext);
	update();
}

