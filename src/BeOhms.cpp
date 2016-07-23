///////////////////////////////////////////////////
// BeOhms.cpp
//
// Copyright 1999  Kyle Crane
//
///////////////////////////////////////////////////

#ifndef BEOHMSWINDOW_H
#include "BeOhmsWindow.h"
#endif

#ifndef BEOHMS_H
#include "BeOhms.h"
#endif

// Program entry point
main()
{
	BeOhmsApplication	theApp;
	
	theApp.Run();
	
	return(0);
}




//////////////////////////////////////////////////////
// Main Application
//

BeOhmsApplication::BeOhmsApplication(void)
: BApplication("application/x-vnd.OHM-BeOhms")
{
	// Create the new window and get it displayed
	BRect bounds(100, 80, 260, 120);
	m_pMainWindow = new BeOhmsWindow(bounds);
	m_pMainWindow->Show();
}

BeOhmsApplication::~BeOhmsApplication(void)
{

}