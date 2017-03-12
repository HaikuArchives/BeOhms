///////////////////////////////////////////////////
// App.cpp
//
// Copyright 1999  Kyle Crane
//
///////////////////////////////////////////////////

const char* bSignature = "application/x-vnd.OHM-BeOhms";


#include "App.h"


App::App(void): BApplication(bSignature) { 
	
	mainWindow = new BeOhmsWindow();
	mainWindow->Show();
}

int main() {
	
	App *app = new App();
	be_app->Run();
	delete be_app;
	return 0;
}
