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
#include <MenuBar.h>
#include <MenuItem.h>



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
	
	BButton* 		m_pBtnCompute;
	BButton* 		m_pBtnClear;
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
	BMenuBar*	fMenuBar;
	BMenu*		fAppMenu;
};



#endif // BEOHMS_H
