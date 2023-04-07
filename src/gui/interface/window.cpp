#include "window.h"

#include <cmath>  // for sine stuff


Window::Window()
{

	// set up the initial plot data
	for( int index=0; index<plotDataSize; ++index )
	{
		xData[index] = index;
		yData[index] = 0;
	}

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

	// see https://doc.qt.io/qt-5/signalsandslots-syntaxes.html

	// set up the layout - button above thermometer
	vLayout = new QVBoxLayout();
	vLayout->addWidget(label);
	vLayout->addWidget(header);
	vLayout->addWidget(welcomemessage);

	// plot to the left of button and thermometer
	hLayout = new QHBoxLayout();
	hLayout->addLayout(vLayout);

	setLayout(hLayout);
}

void Window::rfidscan()
{
	// the Qslots

	// get callbacks from parkinglot spots
	// and return: 
	// user uid
	// spot available, spot occupied
	// and designated parking space

	// if spot available = 0
	// return lable "I am sorry the parking is full, would you please try again later?"
}

void Window::reset() {
	// set up the initial plot data
	for( int index=0; index<plotDataSize; ++index )
	{
		xData[index] = index;
		yData[index] = 0;
	}
}


void Window::timerEvent( QTimerEvent * )
{
	double inVal = gain * sin( M_PI * count/50.0 );
	++count;

	// add the new input to the plot
	std::move( yData, yData + plotDataSize - 1, yData+1 );
	yData[0] = inVal;
	// curve->setSamples(xData, yData, plotDataSize);
	// plot->replot();

	// // set the thermometer value
	// thermo->setValue( fabs(inVal) );
}
