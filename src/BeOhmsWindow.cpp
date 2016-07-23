///////////////////////////////////////////////////
// BeOhmsWindow.cpp
//
// Copyright 1999  Kyle Crane
//
///////////////////////////////////////////////////

#ifndef _APPLICATION_H
#include <Application.h>
#endif

#ifndef BEOHMSWINDOW_H
#include "BeOhmsWindow.h"
#endif


/////////////////////////////////////////////////////
// BeOhmsWindow -- Member Functions
//
BeOhmsWindow::BeOhmsWindow(BRect bounds)
: BWindow(bounds, "BeOhms", B_TITLED_WINDOW, B_NOT_RESIZABLE | B_NOT_ZOOMABLE )
{
	// Size and setup the window
	ResizeTo(285,190);
	BRect myBounds(Bounds());
	m_pMainView = new BeOhmsView(myBounds);
	AddChild(m_pMainView);
}

bool BeOhmsWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(true);
}



//////////////////////////////////////////////////////
// BeOhmsView -- Member Functions
//
BeOhmsView::BeOhmsView(BRect bounds)
: BView(bounds, "main_view", B_FOLLOW_ALL_SIDES, B_WILL_DRAW)
{
	// Get some handy measurements
	m_fRight = bounds.Width();
	m_fBottom = bounds.Height();
	m_fVCenter = m_fBottom / 2;
	m_fHCenter = m_fRight / 2;
}

void BeOhmsView::MessageReceived(BMessage* msg)
{
	int nValue = msg->what;
	
	// Respond to messages sent from the controls
	if(nValue == OPT_VOLTAGE)
	{
		if (!m_pTxtVoltage->IsHidden())
			m_pTxtVoltage->Hide();
		if (m_pTxtResistance->IsHidden())
			m_pTxtResistance->Show();
		if (m_pTxtCurrent->IsHidden())
			m_pTxtCurrent->Show();
		m_pLblOutput->SetText("Voltage ---->");
		m_pTxtOutput->SetText("");
	}
	else if (nValue == OPT_CURRENT)
	{
		if (m_pTxtVoltage->IsHidden())
			m_pTxtVoltage->Show();
		if (m_pTxtResistance->IsHidden())
			m_pTxtResistance->Show();
		if (!m_pTxtCurrent->IsHidden())
			m_pTxtCurrent->Hide();
		m_pLblOutput->SetText("Current ---->");
		m_pTxtOutput->SetText("");	
	}
	else if (nValue == OPT_RESISTANCE)
	{
		if (m_pTxtVoltage->IsHidden())
			m_pTxtVoltage->Show();
		if (!m_pTxtResistance->IsHidden())
			m_pTxtResistance->Hide();
		if (m_pTxtCurrent->IsHidden())
			m_pTxtCurrent->Show();
		m_pLblOutput->SetText("Resistance ---->");
		m_pTxtOutput->SetText("");
	}
	else if (nValue == BTN_COMPUTE_PRESSED)
	{
		Compute();
	}
	else if (nValue == BTN_CLEAR_PRESSED)
	{
		ClearForm();
	}
	else if (nValue == BTN_EXIT_PRESSED)
	{
		Window()->PostMessage(B_QUIT_REQUESTED);
		
	}
	else
		// No messages for me
		BView::MessageReceived(msg);
}

void BeOhmsView::AttachedToWindow(void)
{
	// Do some initialization
	SetViewColor(210,210,210);
	CreateControls();
}

void BeOhmsView::CreateControls(void)
{
	float fButtonWidth = 70.00;

	// Create the controls for this view
	BRect groupRect(10,10,275,100);
	m_pSolveGroup = new BBox(groupRect, "solve_group");
	m_pSolveGroup->SetLabel("Solve For");
	AddChild(m_pSolveGroup);
	
	BRect optVoltageRect(10,15,100,30);
	m_pOptVoltage = 
		new BRadioButton(optVoltageRect, "option_voltage", "Voltage", new BMessage(OPT_VOLTAGE));
	m_pSolveGroup->AddChild(m_pOptVoltage);
	
	BRect optResistanceRect(10,40,100,55);
	m_pOptResistance = 
		new BRadioButton(optResistanceRect, "option_resistance", "Resistance", new BMessage(OPT_RESISTANCE));
	m_pSolveGroup->AddChild(m_pOptResistance);
	
	BRect optCurrentRect(10,65,100,80);
	m_pOptCurrent = 
		new BRadioButton(optCurrentRect, "option_current", "Current", new BMessage(OPT_CURRENT));
	m_pSolveGroup->AddChild(m_pOptCurrent);
	m_pOptCurrent->SetValue(1);
	
	BRect txtVoltageRect(120,15,250,30);
	m_pTxtVoltage = new BTextControl(txtVoltageRect, "text_voltage", "", "", NULL);
	m_pTxtVoltage->SetDivider(0);
	m_pSolveGroup->AddChild(m_pTxtVoltage);
	
	BRect txtResistanceRect(120,40,250,55);
	m_pTxtResistance = new BTextControl(txtResistanceRect, "text_resistance", "", "", NULL);
	m_pTxtResistance->SetDivider(0);
	m_pSolveGroup->AddChild(m_pTxtResistance);
	
	BRect txtCurrentRect(120,65,250,80);
	m_pTxtCurrent = new BTextControl(txtCurrentRect, "text_current", "", "", NULL);
	m_pTxtCurrent->SetDivider(0);
	m_pSolveGroup->AddChild(m_pTxtCurrent);
	m_pTxtCurrent->Hide();
	
	BRect lblOutputRect(20,105,125,120);
	m_pLblOutput = new BStringView(lblOutputRect, "label_output", "Current ---->");
	AddChild(m_pLblOutput);
	
	BRect txtOutputRect(130,105,260,120);
	m_pTxtOutput = new BTextControl(txtOutputRect, "text_output", "", "", NULL);
	m_pTxtOutput->SetDivider(0);
	m_pTxtOutput->SetEnabled(false);
	AddChild(m_pTxtOutput);
	
	BRect btnComputeRect(10,140,70,170);
	m_pBtnCompute = 
		new BButton(btnComputeRect, "button_compute", "Compute", new BMessage(BTN_COMPUTE_PRESSED));  	
	AddChild(m_pBtnCompute);
	
	BRect btnClearRect(80,140,140,170);
	m_pBtnClear =
		new BButton(btnClearRect, "button_clear", "Clear", new BMessage(BTN_CLEAR_PRESSED));
	AddChild(m_pBtnClear);
	
	BRect btnExitRect((m_fRight - 10 - fButtonWidth), 140, (m_fRight - 10), 170);
	m_pBtnExit = 
		new BButton(btnExitRect, "button_exit", "Exit", new BMessage(BTN_EXIT_PRESSED));
	AddChild(m_pBtnExit);
	
	BRect lblCopyrightRect(10,180,150,190);
	BStringView* pLblCopyright = new BStringView(lblCopyrightRect, "copy_right", "Copyright 1999  Kyle Crane");
	AddChild(pLblCopyright);
	
	m_pOptVoltage->SetTarget(this);
	m_pOptResistance->SetTarget(this);
	m_pOptCurrent->SetTarget(this);		 	
	m_pBtnCompute->SetTarget(this);
	m_pBtnClear->SetTarget(this);
	m_pBtnExit->SetTarget(this);
}

void BeOhmsView::Compute(void)
{
	if (m_pOptVoltage->Value() != 0)
		ComputeForVoltage();
	else if (m_pOptCurrent->Value() != 0)
		ComputeForCurrent();
	else
		ComputeForResistance();
}

void BeOhmsView::ComputeForVoltage(void)
{
	if (Validate(m_pTxtCurrent) && Validate(m_pTxtResistance))
	{
		char* pszResult = new char[50];
		float fCurrent, fResistance, fVoltage;
		fCurrent = fResistance = fVoltage = 0;
	
		fCurrent = atof(m_pTxtCurrent->Text());
		fResistance = atof(m_pTxtResistance->Text());
		fVoltage = fCurrent * fResistance;
		sprintf(pszResult, "%g", fVoltage);
	
		m_pTxtVoltage->SetText(pszResult);
		m_pTxtOutput->SetText(pszResult);
		delete pszResult;
	}
	else
	{
		m_pTxtOutput->SetText("--- ERROR ---");		
		m_pTxtVoltage->SetText("");
	}
}

void BeOhmsView::ComputeForCurrent(void)
{
	if (Validate(m_pTxtVoltage) && Validate(m_pTxtResistance))
	{
		char* pszResult = new char[50];
		float fCurrent, fResistance, fVoltage;
		fCurrent = fResistance = fVoltage = 0;
	
		fResistance = atof(m_pTxtResistance->Text());
		fVoltage = atof(m_pTxtVoltage->Text());
		fCurrent = fVoltage/fResistance;
		sprintf(pszResult, "%g", fCurrent);
	
		m_pTxtCurrent->SetText(pszResult);
		m_pTxtOutput->SetText(pszResult);
		delete pszResult;
	}
	else
	{
		m_pTxtOutput->SetText("--- ERROR ---");
		m_pTxtCurrent->SetText("");
	}
}

void BeOhmsView::ComputeForResistance(void)
{

	if(Validate(m_pTxtVoltage) && Validate(m_pTxtCurrent))
	{
		char* pszResult = new char[50];
		float fCurrent, fResistance, fVoltage;
		fCurrent = fResistance = fVoltage = 0;
	
		fVoltage = atof(m_pTxtVoltage->Text());
		fCurrent = atof(m_pTxtCurrent->Text());
		fResistance = fVoltage/fCurrent;
		sprintf(pszResult, "%g", fResistance);
	
		m_pTxtResistance->SetText(pszResult);
		m_pTxtOutput->SetText(pszResult);
		delete pszResult;
	}
	else
	{
		m_pTxtResistance->SetText("");
		m_pTxtOutput->SetText("--- ERROR ---");
	}
}

bool BeOhmsView::Validate(BTextControl* pTextCtrl)
{
	// First make sure each character is one that is valid
	// as a number 1(-)<-Must be first, 1(.), 1234567890
	char* 	pszText;
	int  	cCurrent;
	bool	bDecimalFound = false;
	bool 	bOk = true;
	int nSize = 0;
	
	pszText = pTextCtrl->Text();
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

void BeOhmsView::ClearForm(void)
{
	// Send a phony message to reset the for to
	// its default state
	BMessage* msg = new BMessage(OPT_CURRENT);
	m_pOptCurrent->SetValue(1);
	MessageReceived(msg);
	
	// Now clear all text boxes
	m_pTxtVoltage->SetText("");
	m_pTxtResistance->SetText("");
	m_pTxtCurrent->SetText("");				
	m_pTxtOutput->SetText("");
}