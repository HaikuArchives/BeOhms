///////////////////////////////////////////////////
// App.cpp
//
// Copyright 1999  Kyle Crane
//
///////////////////////////////////////////////////

const char* bSignature = "application/x-vnd.OHM-BeOhms";


#include "App.h"


App::App(void)
	: BApplication(bSignature)
{ 
	
	fMainWindow = new BeOhmsWindow();
	fMainWindow->Show();
}


void
App::AboutRequested()
{
	BAlert* alert = new BAlert("about",
		"BeOhms\n"
		"\tby Kyle Crane\n"
		"\tCopyright 1999\n\n"
		"An Ohm's law calculator.",
		"Thank you");

	BTextView * view = alert->TextView();
	BFont font;
	view->SetStylable(true);
	view->GetFont(&font);
	font.SetSize(font.Size() + 4);
	font.SetFace(B_BOLD_FACE);
	view->SetFontAndColor(0, 6, &font);
	alert->Go();
}


int
main() 
{
	
	App *app = new App();
	be_app->Run();
	delete be_app;
	return 0;
}
