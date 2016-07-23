///////////////////////////////////////////////////
// BeOhms.h
//
// Copyright 1999  Kyle Crane
//
///////////////////////////////////////////////////

#ifndef BEOHMS_H
#define BEOHMS_H

#ifndef _APPLICATION_H
#include <Application.h>
#endif



// Starter application class
class BeOhmsApplication : public BApplication
{
public:
			BeOhmsApplication();
	virtual ~BeOhmsApplication();
	
private:
	BeOhmsWindow*		m_pMainWindow;
};



#endif // BEOHMS_H