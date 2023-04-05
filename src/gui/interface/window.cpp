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

	button = new QPushButton("Reset");
	// see https://doc.qt.io/qt-5/signalsandslots-syntaxes.html
	connect(button,&QPushButton::clicked,this,&Window::reset);

	// set up the layout - button above thermometer
	vLayout = new QVBoxLayout();
	vLayout->addWidget(button);

	// plot to the left of button and thermometer
	hLayout = new QHBoxLayout();
	hLayout->addLayout(vLayout);

	setLayout(hLayout);
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
}
