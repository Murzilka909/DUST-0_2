//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>

#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TButton *Exit_Button;
	TTabSheet *AutoTab;
	TTabSheet *HandTab;
	TTabSheet *SpeedTab;
	TTabSheet *ChargeTab;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TLabel *FNameLabel;
	TListBox *AutoListBox;
	TListBox *HandListBox;
	TButton *HandFNameButton;
	TCheckBox *HandCheckBox;
	TButton *YesButton;
	TLabel *FDataLabel;
	TButton *NoButton;
	TChart *SpeedChart;
	TChart *ChargeChart;
	TButton *HandSpectraButton;
	TButton *AutoSpectraButton;
	TLabel *SpeedFLabel;
	TLabel *ChargeFLabel;
	TButton *SpeedSaveButton;
	TButton *ChargeSaveButton;
	TOpenTextFileDialog *AutoTextFileDialog;
	TOpenTextFileDialog *HandTextFileDialog;
	TButton *AutoFNameButton;
	TChart *HandChart;
	TLineSeries *Series1;
	TLineSeries *Series2;
	TTabSheet *SettingsTab;
	TPanel *Panel5;
	TLineSeries *Series3;
	TLineSeries *Series4;
	TButton *SetValButton;
	TListBox *ChargeListBox;
	TListBox *SpeedListBox;
	TButton *HandClearButton;
	TButton *AutoClearButton;
	TGroupBox *GroupBox1;
	TStaticText *StaticText15;
	TEdit *MaxChargeEdit;
	TStaticText *StaticText14;
	TStaticText *StaticText12;
	TEdit *MaxSpeedEdit;
	TStaticText *StaticText13;
	TStaticText *StaticText11;
	TEdit *DistrStepQEdit;
	TStaticText *StaticText9;
	TEdit *DistrStepVEdit;
	TStaticText *StaticText10;
	TStaticText *StaticText8;
	TStaticText *StaticText7;
	TStaticText *StaticText5;
	TEdit *GainBEdit;
	TStaticText *StaticText6;
	TEdit *GainAEdit;
	TStaticText *StaticText3;
	TStaticText *StaticText4;
	TStaticText *StaticText1;
	TEdit *LimVEdit;
	TStaticText *StaticText2;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox4;
	TStaticText *StaticText16;
	TEdit *MinFNumEdit;
	TStaticText *StaticText17;
	TEdit *MaxFNumEdit;
	TCheckBox *FBaseCheckBox;
	TStaticText *StaticText18;
	TEdit *DeltaSpeedABEdit;
	TStaticText *StaticText19;
	TStaticText *StaticText20;
	TEdit *DeltaSpeedCommEdit;
	TStaticText *StaticText21;
	TEdit *DeltaChargeABEdit;
	TStaticText *StaticText22;
	TStaticText *StaticText23;
	TStaticText *StaticText27;
	TStaticText *StaticText29;
	TStaticText *StaticText28;
	TStaticText *StaticText24;
	TStaticText *StaticText25;
	TEdit *DeltaI12Edit;
	TEdit *DeltaI23Edit;
	TEdit *DeltaA12Edit;
	TStaticText *StaticText26;
	TStaticText *StaticText30;
	TStaticText *StaticText31;
	TEdit *BaseNumEdit;
	TStaticText *StaticText32;
	TStaticText *StaticText33;
	TEdit *DeltaA23Edit;
	TLabel *AutoLabel;
	TButton *StartButton;
	void __fastcall Exit_ButtonClick(TObject *Sender);
	void __fastcall HandFNameButtonClick(TObject *Sender);
	void __fastcall YesButtonClick(TObject *Sender);
	void __fastcall NoButtonClick(TObject *Sender);
	void __fastcall SetValButtonClick(TObject *Sender);
	void __fastcall HandSpectraButtonClick(TObject *Sender);
	void __fastcall HandClearButtonClick(TObject *Sender);
	void __fastcall AutoFNameButtonClick(TObject *Sender);
	void __fastcall StartButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
