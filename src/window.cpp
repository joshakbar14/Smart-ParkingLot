#include "window.h"
#include <iostream>
#include "parkingLot.h"

using namespace std;

Window::Window()
{
	parkingLot park(2, this)
	this->spotlabeltext = 0;
	this->uidlabeltext = "";
	
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

void Window::timerEvent( QTimerEvent * )
{
	// Pass in to the GUI
	// spotlabel->setText(std::to_string(spotlabeltext));
	// spotavailable->setText(std::to_string(spotavailabletext));
	// spotoccupied->setText(std::to_string(spotoccupiedtext));
	// uidlabel->setText(uidlabeltext);
}

void Window::updateWindow(int spottext, string uidtext){
	
	spotlabel->setText()
	spotlabeltext = spottext;
	uidlabeltext = uidtext;
	cout << "This is in the window " << spottext << " and " << uidtext << endl; 

}

void Window::startParkingLot(){
	park->start();
}

Window::~Window(){
	park->stop();
	delete park;
}
