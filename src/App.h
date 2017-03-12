///////////////////////////////////////////////////
// App.h
//
// Copyright 1999  Kyle Crane
//
///////////////////////////////////////////////////

#ifndef APP_H
#define APP_H

#include <Application.h>
#include "BeOhmsWindow.h"


// Starter application class
class App : public BApplication {
public:
		App(void);
		
private:
	
		BeOhmsWindow*   mainWindow;
};



#endif 
