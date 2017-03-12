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
#include <Window.h>
#include <View.h>




// Main window for the applications
class BeOhmsWindow : public BWindow
{
public:
	BeOhmsWindow();
	
	bool 	QuitRequested(void);
	void 	MessageReceived(BMessage * msg);
	
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
	BView * 		back;
	BGroupLayout*	s_fBoxLayout;
	BGroupLayout*	o_BoxLayout;
};



#endif // BEOHMS_H
