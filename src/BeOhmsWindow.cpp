///////////////////////////////////////////////////
// BeOhmsWindow.cpp
// Copyright 1999  Kyle Crane
//
///////////////////////////////////////////////////


#include "BeOhmsWindow.h"
#include <Application.h>
#include <LayoutBuilder.h>



BeOhmsWindow::BeOhmsWindow()
: BWindow(BRect(),"BeOhms", B_TITLED_WINDOW, B_NOT_ZOOMABLE|B_NOT_RESIZABLE)
{
	// Size and center the window on screen
	ResizeTo(320,240);
	CenterOnScreen();
	
	back = new BView("back", B_WILL_DRAW);
	
	m_pSolveGroup = new BBox("solve_group");
	m_pSolveGroup->SetLabel("Solve For");
	
	m_pOptVoltage = 
		new BRadioButton("option_voltage", "Voltage", new BMessage(OPT_VOLTAGE));
	m_pOptResistance = 
		new BRadioButton("option_resistance", "Resistance", new BMessage(OPT_RESISTANCE));
	m_pOptCurrent = 
		new BRadioButton("option_current", "Current", new BMessage(OPT_CURRENT));
	m_pOptCurrent->SetValue(1);
	
	
	m_pTxtVoltage = new BTextControl("text_voltage", "", "", NULL);
	m_pTxtResistance = new BTextControl("text_resistance", "", "", NULL);
	
	m_pTxtCurrent = new BTextControl("text_current", "", "", NULL);
	m_pTxtCurrent->Hide();
	
	
	m_pLblOutput = new BStringView("label_output", "Current ---->");
	m_pTxtOutput = new BTextControl("text_output", "", "", NULL);
	m_pTxtOutput->SetEnabled(false);
	
	m_pBtnCompute = 
		new BButton("button_compute", "Compute", new BMessage(BTN_COMPUTE_PRESSED));  	
	m_pBtnClear =
		new BButton("button_clear", "Clear", new BMessage(BTN_CLEAR_PRESSED));
	m_pBtnExit = 
		new BButton("button_exit", "Exit", new BMessage(BTN_EXIT_PRESSED));
			
			
	BStringView* pLblCopyright = new BStringView("copy_right", "Copyright 1999  Kyle Crane");
		
	
	s_fBoxLayout = BLayoutBuilder::Group<>(B_HORIZONTAL)
		.SetInsets(10)
    	.AddGrid(B_USE_DEFAULT_SPACING, 0.0f)
       	  	.AddGlue(0,0)
    	  	.AddGlue(1,0)
			.Add(m_pOptVoltage, 0, 1)
			.Add(m_pOptResistance, 0, 2)
			.Add(m_pOptCurrent, 0, 3)
			.Add(m_pTxtVoltage, 1, 1)
			.Add(m_pTxtResistance, 1, 2)
			.Add(m_pTxtCurrent, 1, 3)
			.AddGlue(0,4)
			.AddGlue(1,4)	
		.End();
	
	m_pSolveGroup->AddChild(s_fBoxLayout->View());
	
	
	o_BoxLayout = BLayoutBuilder::Group<>(B_HORIZONTAL)
		.SetInsets(10)
    		.Add(m_pLblOutput)
    		.Add(m_pTxtOutput);
	
	
	BLayoutBuilder::Group<>(back, B_VERTICAL, 0.0f)
		.SetInsets(10)
		.Add(m_pSolveGroup)
		.Add(o_BoxLayout)
		.AddGrid()
			.Add(m_pBtnCompute , 0, 0)
			.Add(m_pBtnClear, 1, 0)
			.AddGlue(2, 0)
			.Add(m_pBtnExit, 3, 0)
		.End()		
	.End();
	
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0.0f)
		.SetInsets(0)
		.Add(back)
		.Add(pLblCopyright)
    .End();

}

bool BeOhmsWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(true);
}

void BeOhmsWindow::MessageReceived(BMessage* msg)
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
		PostMessage(B_QUIT_REQUESTED);
		
	}

	else
		// No messages for me
		BWindow::MessageReceived(msg);
}

void BeOhmsWindow::Compute(void)
{
	if (m_pOptVoltage->Value() != 0)
		ComputeForVoltage();
	else if (m_pOptCurrent->Value() != 0)
		ComputeForCurrent();
	else
		ComputeForResistance();
}

void BeOhmsWindow::ComputeForVoltage(void)
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

void BeOhmsWindow::ComputeForCurrent(void)
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

void BeOhmsWindow::ComputeForResistance(void)
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

bool BeOhmsWindow::Validate(BTextControl* pTextCtrl)
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

void BeOhmsWindow::ClearForm(void)
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

