///////////////////////////////////////////////////
// BeOhmsWindow.h
//
// Copyright 1999  Kyle Crane
//
///////////////////////////////////////////////////

#ifndef BEOHMSWINDOW_H
#define BEOHMSWINDOW_H


#include <Alert.h>
#include <Box.h>
#include <Button.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include <RadioButton.h>
#include <StringView.h>
#include <TextControl.h>
#include <View.h>
#include <Window.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
	
	BButton* 		fBtnCompute;
	BButton* 		fBtnClear;
	BBox*			fSolveGroup;
	BRadioButton*		fOptVoltage;
	BRadioButton*		fOptResistance;
	BRadioButton*		fOptCurrent;
	BTextControl*		fTxtVoltage;
	BTextControl*		fTxtResistance;
	BTextControl*		fTxtCurrent;
	BStringView*		fLblOutput;
	BTextControl*		fTxtOutput;
	BView*			fBack;
	BGroupLayout*		fBoxLayout;
	BMenuBar*		fMenuBar;
	BMenu*			fAppMenu;
};


#endif // BEOHMS_H
