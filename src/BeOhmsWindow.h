///////////////////////////////////////////////////
// BeOhmsWindow.h
//
// Copyright 1999  Kyle Crane
//
///////////////////////////////////////////////////

#ifndef BEOHMSWINDOW_H
#define BEOHMSWINDOW_H

#include <TextControl.h>
#include <Button.h>
#include <StringView.h>
#include <RadioButton.h>
#include <Box.h>
#include <Alert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef _WINDOW_H
#include <Window.h>
#endif



// Main view for the window
class BeOhmsView : public BView
{
public:
	BeOhmsView(BRect bounds);

	virtual void 	MessageReceived(BMessage* msg);
	virtual void 	AttachedToWindow(void);


private:
			void	CreateControls(void);
			void 	Compute(void);
			void	ComputeForVoltage(void);
			void	ComputeForCurrent(void);
			void	ComputeForResistance(void);
			bool	Validate(BTextControl* pText);
			void 	ClearForm(void);
			
			
private:
	static const int OPT_VOLTAGE 	 	 = 1001;
	static const int OPT_RESISTANCE	 	 = 1002;
	static const int OPT_CURRENT		 = 1003;
	static const int BTN_COMPUTE_PRESSED = 1004;
	static const int BTN_CLEAR_PRESSED	 = 1005;
	static const int BTN_EXIT_PRESSED	 = 1006;
	
	BButton* 		m_pBtnCompute;
	BButton* 		m_pBtnClear;
	BButton* 		m_pBtnExit;
	BBox*			m_pSolveGroup;
	BRadioButton*	m_pOptVoltage;
	BRadioButton*	m_pOptResistance;
	BRadioButton*	m_pOptCurrent;
	BTextControl*	m_pTxtVoltage;
	BTextControl*	m_pTxtResistance;
	BTextControl*	m_pTxtCurrent;
	BStringView*	m_pLblOutput;
	BTextControl*	m_pTxtOutput;
	
	float m_fBottom;
	float m_fRight;
	float m_fVCenter;
	float m_fHCenter;	
};



// Main window for the applications
class BeOhmsWindow : public BWindow
{
public:
	BeOhmsWindow(BRect bounds);
	
	virtual bool 	QuitRequested(void);
	
private:
	BeOhmsView*		m_pMainView;
};



#endif // BEOHMS_H
