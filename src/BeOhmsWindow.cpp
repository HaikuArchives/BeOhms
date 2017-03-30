///////////////////////////////////////////////////
// BeOhmsWindow.cpp
// Copyright 1999  Kyle Crane
//
///////////////////////////////////////////////////


#include <Application.h>
#include <LayoutBuilder.h>

#include "BeOhmsWindow.h"


BeOhmsWindow::BeOhmsWindow()
	:
	BWindow(BRect(),"BeOhms", B_TITLED_WINDOW, 
		B_NOT_ZOOMABLE|B_NOT_RESIZABLE)
{
	// Size and center the window on screen
	ResizeTo(360, 260);
	CenterOnScreen();
	
	fBack = new BView("back", B_WILL_DRAW);
	
	fMenuBar = new BMenuBar("MenuBar");
	
	fAppMenu = new BMenu("App");
	
	BMenuItem * item = new BMenuItem("About", new BMessage(B_ABOUT_REQUESTED));
	item->SetTarget(be_app);
	fAppMenu->AddItem(item);
	fAppMenu->AddSeparatorItem();
	fAppMenu->AddItem(new BMenuItem("Quit", new BMessage(kMenuAppQuit), 'Q', B_COMMAND_KEY));
	
	fMenuBar->AddItem(fAppMenu);
	
	fSolveGroup = new BBox("solve_group");
	fSolveGroup->SetLabel("Solve For");
	
	fOptVoltage = 
		new BRadioButton("option_voltage", "Voltage", new BMessage(kOptVoltage));
	fOptResistance = 
		new BRadioButton("option_resistance", "Resistance", new BMessage(kOptResistance));
	fOptCurrent = 
		new BRadioButton("option_current", "Current", new BMessage(kOptCurrent));
	fOptCurrent->SetValue(1);
	
	
	fTxtVoltage = new BTextControl("text_voltage", "", "", NULL);
	fTxtResistance = new BTextControl("text_resistance", "", "", NULL);
	
	fTxtCurrent = new BTextControl("text_current", "", "", NULL);
	fTxtCurrent->Hide();
	
	
	fLblOutput = new BStringView("label_output", "Current ---->");
	fTxtOutput = new BTextControl("text_output", "", "", NULL);
	fTxtOutput->SetEnabled(false);
	
	fBtnCompute = 
		new BButton("button_compute", "Compute", new BMessage(kComputePressed));
	fBtnClear =
		new BButton("button_clear", "Clear", new BMessage(kClearPressed));
				
	
	fBoxLayout = BLayoutBuilder::Group<>(B_HORIZONTAL)
		.SetInsets(10)
		.AddGrid(B_USE_DEFAULT_SPACING, 0.0f)
		.AddGlue(0,0)
		.AddGlue(1,0)
			.Add(fOptVoltage, 0, 1)
			.Add(fOptResistance, 0, 2)
			.Add(fOptCurrent, 0, 3)
			.Add(fTxtVoltage, 1, 1)
			.Add(fTxtResistance, 1, 2)
			.Add(fTxtCurrent, 1, 3)
			.AddGlue(0, 4)
			.AddGlue(1, 4)
		.End();
	
	fSolveGroup->AddChild(fBoxLayout->View());
	
	
	BLayoutBuilder::Group<>(fBack, B_VERTICAL, 0.0f)
		.SetInsets(10,10,10,0)
		.Add(fSolveGroup)
		.AddGroup(B_HORIZONTAL)
			.SetInsets(10)
			.Add(fLblOutput)
    		.Add(fTxtOutput)
		.End()
		.AddGrid()
			.AddGlue(0, 0)
			.Add(fBtnCompute, 1, 0)
			.Add(fBtnClear, 2, 0)
		.End()
		.AddStrut(10)
		.End();
	
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0.0f)
		.SetInsets(0)
		.Add(fMenuBar)
		.AddGlue()
		.Add(fBack)
		.AddGlue()
		.End();
}


bool
BeOhmsWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}


void
BeOhmsWindow::MessageReceived(BMessage* msg)
{		
	switch(msg->what) {
		
		case kMenuAppQuit:
			be_app->PostMessage(B_QUIT_REQUESTED);
			break;
	
		// Respond to messages sent from the controls
		case kOptVoltage:
		{
			if (!fTxtVoltage->IsHidden())
				fTxtVoltage->Hide();
			if (fTxtResistance->IsHidden())
				fTxtResistance->Show();
			if (fTxtCurrent->IsHidden())
				fTxtCurrent->Show();
			fLblOutput->SetText("Voltage ---->");
			fTxtOutput->SetText("");
			break;
		}
	
		case kOptCurrent:
		{
			if (fTxtVoltage->IsHidden())
				fTxtVoltage->Show();
			if (fTxtResistance->IsHidden())
				fTxtResistance->Show();
			if (!fTxtCurrent->IsHidden())
				fTxtCurrent->Hide();
			fLblOutput->SetText("Current ---->");
			fTxtOutput->SetText("");	
			break;
		}
	
		case kOptResistance:
		{
			if (fTxtVoltage->IsHidden())
				fTxtVoltage->Show();
			if (!fTxtResistance->IsHidden())
				fTxtResistance->Hide();
			if (fTxtCurrent->IsHidden())
				fTxtCurrent->Show();
			fLblOutput->SetText("Resistance ---->");
			fTxtOutput->SetText("");
			break;
		}
	
		case kComputePressed:
			Compute();
			break;

		case kClearPressed:
			ClearForm();
			break;
	
		default:
			BWindow::MessageReceived(msg);
			break;
	}
}


void
BeOhmsWindow::Compute(void)
{
	if (fOptVoltage->Value() != 0)
		ComputeForVoltage();
	else if (fOptCurrent->Value() != 0)
		ComputeForCurrent();
	else
		ComputeForResistance();
}


void
BeOhmsWindow::ComputeForVoltage(void)
{
	if (Validate(fTxtCurrent) && Validate(fTxtResistance))
	{
		char* pszResult = new char[50];
		float fCurrent, fResistance, fVoltage;
		fCurrent = fResistance = fVoltage = 0;
	
		fCurrent = atof(fTxtCurrent->Text());
		fResistance = atof(fTxtResistance->Text());
		fVoltage = fCurrent * fResistance;
		sprintf(pszResult, "%g", fVoltage);
	
		fTxtVoltage->SetText(pszResult);
		fTxtOutput->SetText(pszResult);
		delete pszResult;
	}
	else
	{
		fTxtOutput->SetText("--- ERROR ---");		
		fTxtVoltage->SetText("");
	}
}


void
BeOhmsWindow::ComputeForCurrent(void)
{
	if (Validate(fTxtVoltage) && Validate(fTxtResistance))
	{
		char* pszResult = new char[50];
		float fCurrent, fResistance, fVoltage;
		fCurrent = fResistance = fVoltage = 0;
	
		fResistance = atof(fTxtResistance->Text());
		fVoltage = atof(fTxtVoltage->Text());
		fCurrent = fVoltage/fResistance;
		sprintf(pszResult, "%g", fCurrent);
	
		fTxtCurrent->SetText(pszResult);
		fTxtOutput->SetText(pszResult);
		delete pszResult;
	}
	else
	{
		fTxtOutput->SetText("--- ERROR ---");
		fTxtCurrent->SetText("");
	}
}


void
BeOhmsWindow::ComputeForResistance(void)
{

	if(Validate(fTxtVoltage) && Validate(fTxtCurrent))
	{
		char* pszResult = new char[50];
		float fCurrent, fResistance, fVoltage;
		fCurrent = fResistance = fVoltage = 0;
	
		fVoltage = atof(fTxtVoltage->Text());
		fCurrent = atof(fTxtCurrent->Text());
		fResistance = fVoltage/fCurrent;
		sprintf(pszResult, "%g", fResistance);
	
		fTxtResistance->SetText(pszResult);
		fTxtOutput->SetText(pszResult);
		delete pszResult;
	}
	else
	{
		fTxtResistance->SetText("");
		fTxtOutput->SetText("--- ERROR ---");
	}
}


bool
BeOhmsWindow::Validate(BTextControl* pTextCtrl)
{
	// First make sure each character is one that is valid
	// as a number 1(-)<-Must be first, 1(.), 1234567890
	char* 	pszText;
	int  	cCurrent;
	bool	bDecimalFound = false;
	bool 	bOk = true;
	int nSize = 0;
	
	pszText = (char *)pTextCtrl->Text();
	nSize = strlen(pszText);
		
	for (int nIndex = 0; nIndex < nSize; nIndex++)
	{
		cCurrent = pszText[nIndex];
		
		if (nIndex == 0)
		{
			// if this is the first character then a minus sign is ok
			if( (cCurrent > 47 && cCurrent < 58) || (cCurrent == 45) || ((cCurrent == 46) && !bDecimalFound))
			{
				if(cCurrent == 46)
					bDecimalFound = true;
			}
			else
			{
				bOk = false;
				break;
			}
		}
		else
		{
			// Otherwise only numeric characters and the decimal point
			// is ok.
			if((cCurrent > 47 && cCurrent < 58) || ((cCurrent == 46) && !bDecimalFound))
			{
				if(cCurrent == 46)
					bDecimalFound = true;
			}
			else
			{
				bOk = false;
				break;
			}
		}
	}
	
	if (!bOk)
	{
		BAlert* alert = new BAlert("Invalid Numeric Entry", "You entered an invalid number\nPlease Retry!", "Ok");
		alert->Go();
		pTextCtrl->MakeFocus(true);
	}
	
	// Now make sure that the number is greater than zero.
	if (atof(pszText) == 0 && bOk)
	{
		BAlert* alert = new BAlert("Zero Entry", "Number must not be zero\nPlease Retry!", "Ok");
		alert->Go();
		pTextCtrl->MakeFocus(true);
		bOk = false;
	}
	
	return bOk;
}


void
BeOhmsWindow::ClearForm(void)
{
	// Send a phony message to reset the for to
	// its default state
	BMessage* msg = new BMessage(kOptCurrent);
	fOptCurrent->SetValue(1);
	MessageReceived(msg);
	
	// Now clear all text boxes
	fTxtVoltage->SetText("");
	fTxtResistance->SetText("");
	fTxtCurrent->SetText("");				
	fTxtOutput->SetText("");
}

