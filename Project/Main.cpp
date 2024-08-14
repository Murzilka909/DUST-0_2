//---------------------------------------------------------------------------
#include <vcl.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <stdlib.h>
#include <iomanip>

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Classes.h"

//---------------------------------------------------------------------------

#define MAX_FNUM 10000

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//----------------------���������� ����������--------------------------------
FILE* file_Data;          //������������� - ������
FILE* file_Res;           //������ - ������

std::string fName; //��� � ���� � �����
std::string fBaseName; //��� � ���� � �����

int strNum, colNum; //���-�� ����� � �������� � ����� ������
int fileSize;      //������ ����� � ������
int fNumMin, fNumMax;//�������� ������� ������

double limV;//������ ����������
double gainA; //�������� �� �������
double gainB;

double SinglePerDoubleC; //����������� ��� ���������� � ������ ������ ������

double stepDistrV;//������� ������������ ��� ���������� ��������
double stepDistrQ;

double deltaV, deltaV_AB, deltaQ_AB;//������ ��� ���� �������

double deltaI12, deltaI23; //���������� ���������� �������� � ����������
double deltaA12, deltaA23;
int baseLenght;  //����� �������, �� �������� �������� ������� �����

bool mvFlag=0;//���� �����������, ���� 1 - ��

int fileCount; //������� ������
int i,j,k,m;//��������

char c;//������
char cBuf[8];//�����
std::string s;//�����
double Buf[3];

DataPoint* DataP=new DataPoint(2); //����� ����� ������������
SpectrPoint* SpectrP=new SpectrPoint(2);//����� ����� �������

//---------------------�������������� ����� ������---------------------------
std::string UnicodeToString (UnicodeString us)
{
	AnsiString as=us;
	s = as.c_str();
	return s;
}
std::string IntToString (int a)
{
	std::stringstream ss;
	ss << a;
	s = ss.str();
	return s;
}
std::string DoubleToString(double a)
{
	std::stringstream ss;
	ss.setf(std::ios::scientific, std::ios::floatfield);
	ss << std::setprecision(8) << a;
	s = ss.str();
	return s;
}
std::string NumToString(int n)
{
	int SIZE=2;  //������ ������
	int N=n;
	while (N>0)
	{
		N=N/10;
		SIZE++;
	}

	cBuf[0]='(';
	s=IntToString(n);

	N=1; //������ ��� �������
	while(N<(SIZE-1))
	{
		cBuf[N]= s[N-1];
		N++;
	}
	cBuf[SIZE-1]=')';
	s=cBuf;
	s.erase(SIZE);
	return s;
}

//---------------------����� ����� �� Edit�---------------------------
int NumFromEdit (TEdit* EDIT, int MIN, int MAX)
{
	int a=atof(UnicodeToString(EDIT->Text).c_str());
	if ((a<=MAX)&(a>=MIN))
	{
		return a;
	}
	else
	{
		ShowMessage ("Invalid INT value");
		return NULL;
	}
}

//---------------------������� ����� �� Edit�---------------------------
double PhDoubleFromEdit (TEdit* EDIT,   double MAX)
{
	double a=atof(UnicodeToString(EDIT->Text).c_str());

	bool b;
	if (MAX==0){b=1;}
	else {b=(a<MAX);}

	if (b&(a>0))
	{
		return a;
	}
	else
	{
		ShowMessage ("Invalid phisyc value");
		return NULL;
	}
}

//--------------------��� � ���� � ����� �� ��������--------------------------
void CounterToFnum (int n)
{
	s= NumToString(n); //n -> "(n)"
	fName=fBaseName+" "+s+".txt";
}

//--------------------���������� �������-------------------------------------
void Sort(double* DAT, int Length)
{
    double BUF;
    i=0;
	while(i<Length-1)
	{
		j=0;
		while(j<Length-i-1)
		{
			if(DAT[j] > DAT[j + 1])
			{
				BUF=DAT[j];
                DAT[j]=DAT[j + 1];
                DAT[j + 1]=BUF;
			}
            j++;
		}
        i++;
	}
}

//--------------------��������� �������� �������� �����----------------------
void GetFBaseName()
{
	fBaseName=fName;// ������� - ���� �������� � ������
	std::string to_delete=").txt";  // ����� ��������� �������
	size_t start =fBaseName.find(to_delete);            // ������� ������� ���������
	if (start != std::string::npos) // ���� ����� ��������� ����, ���������� �����
	{
		fileCount=0;
		to_delete=" "+NumToString(fileCount)+".txt";
		start =fBaseName.find(to_delete);
		while ((start == std::string::npos)&(i<MAX_FNUM)) //
		{
			fileCount++;
			to_delete=" "+NumToString(fileCount)+".txt";
			start =fBaseName.find(to_delete);
			if (start != std::string::npos) // ������� � ������� ��� ��������� to_delete
			{
				fBaseName.erase(start, to_delete.length());
				//start = fBaseName.find(to_delete, start + to_delete.length());
			}
		}
	}
	else
	{
		to_delete=" .txt";
		if (start != std::string::npos) // ������� � ������� ��� ��������� to_delete
			{
				fBaseName.erase(start, to_delete.length());
				//start = fBaseName.find(to_delete, start + to_delete.length());
			}
		fileCount=1;
	}
}

//--------------------�������� ������������ ������� �����--------------------
bool CheckFileSize()
{
	fseek( file_Data , 0 , SEEK_END );//� ����� ����� ������
	bool B=((fileSize-ftell(file_Data))>1000)||((fileSize-ftell(file_Data))<-1000);
	fileSize = ftell(file_Data);
	return(B);
}

//--------------------��������� ������� �������------------------------------
void GetFileSize()
{
	fseek( file_Data , 0 , SEEK_END );//� ����� ����� ������
	fileSize = ftell(file_Data);//������ ����� � ������
	fseek( file_Data , 0 , SEEK_SET );//�������
	strNum=0;
	colNum=0;
	while (ftell(file_Data)<fileSize)//������� �������� �����
	{
		fread(&c,1,1,file_Data);
		if (c=='\n')
		{strNum++;}
		if (c=='\t')
		{colNum++;}
	}
	strNum=strNum-3;
	colNum=((colNum-2)/strNum)+1;       //�������� ��������
	delete DataP;
	delete SpectrP;
	DataP=new DataPoint(colNum);
	SpectrP=new SpectrPoint(colNum);
}

//--------------------���������� � ������,��������� ������-------------------
void PrepareForRead()
{
	fseek( file_Data , 0 , SEEK_SET );//������ � ������
	i=0;
	j=0;
	mvFlag=1;
	while (i<3)  //������ ������ ���������
	{
		fread(&c,1,1,file_Data);
		if (i==1)
		{
			j=0;
			while (j<7)
			{
				cBuf[j]=cBuf[j+1];
				j++;
			}                              //�������� ������� � �� ������ ������
			cBuf[7]=c;                     //���� ���� �� ���� � 0
			s=cBuf;
			if (s=="с)\t(В)"){mvFlag=0;}
		}
		if (c=='\n') {i++;}
	}
	SpectrP->to_zero();//���������� � ���� ��� ������ ���������� ����������
}

//--------------------������ ������ �� ����� � ������-------------------------
void ReadStrFile(double* DAT)
{
	fseek( file_Data , -1 , SEEK_CUR );//��� ����� ��� ������
	i=0;
	while (c!='\n') {fread(&c,1,1,file_Data);}
	fread(&c,1,1,file_Data);
	while(i<colNum)//���� ������
	{
		j=0;
		c=0;
		while((j<7)&(c!='\t')&(c!='\n'))//�����
		{
			fread(&c,1,1,file_Data);
			cBuf[j]=c;
			j++;
		}
		if (j<7)     //���� ������
		{
			if (cBuf[1]=='-'){DAT[i]=-limV/1000;}
			else {DAT[i]=limV/1000;}
		}
		else        //���� �� ������
		{
			s=cBuf;
			DAT[i]=atof(s.c_str());
			while ((c!='\t')&(c!='\n')) {fread(&c,1,1,file_Data);}
		}
		if ((mvFlag==0)&(i!=0))
		{DAT[i]=DAT[i]*1000;}  //�������� ����������� ��� ��
		i++;
	}

}

//--------------------������ ������---------------------------------------
void HandReadFile()
{
		k=0;
		while(k<colNum-1)
		{
			Form1->HandChart->Series[k]->Clear();
			k++;
		}

		file_Data = fopen(fName.c_str(), "r");
		if (file_Data != NULL)  //���� ��������
		{

			if (CheckFileSize()){GetFileSize();} //���� �������������� - ������� ������
			PrepareForRead();//���������� � ������

			m=0;
			while(m<strNum)
			{
				ReadStrFile(Buf);//������ ������
				DataP->setP(Buf);//�������� � �����
				SpectrP->extrSpectr(*DataP);//������ ��������
				k=0;
				while(k<colNum-1)
				{
					Form1->HandChart->Series[k]->AddXY(Buf[0],Buf[k+1]);
					k++;
				}
				m++;
			}

			fclose (file_Data);

			s="File size: "+IntToString(fileSize)+";\n"
			+"Columns number: "+IntToString(colNum)+";\n"
			+"Strings number: "+IntToString(strNum)+";\n";
			Form1->FDataLabel->Caption=s.c_str();

			Form1->YesButton->Enabled=1;
			Form1->NoButton->Enabled=1;
		}
		else    //���� �� ��������
		{
			ShowMessage("File is not opened");
			Form1->FNameLabel->Caption="The file is not selected";
		}
}

//--------------------������ ������---------------------------------------
void AutoReadFile()
{
		file_Data = fopen(fName.c_str(), "r");
		if (file_Data != NULL)  //���� ��������
		{

			if (CheckFileSize()){GetFileSize();} //���� �������������� - ������� ������
			PrepareForRead();//���������� � ������

			SpectrP->zeroBase();
			m=0;
			while(m<baseLenght) //���������� ������� �����
			{
				ReadStrFile(Buf);//������ ������
				DataP->setP(Buf);//�������� � �����
				SpectrP->setBase(*DataP, baseLenght);
				m++;
			}
			while(m<strNum)
			{
				ReadStrFile(Buf);//������ ������
				DataP->setP(Buf);//�������� � �����
				SpectrP->extrSpectr(*DataP);//������ ��������
				SpectrP-> extrAandI(*DataP);//��������� �����. ����������
				m++;
			}
			SpectrP[0].calcSpectr();

			fclose (file_Data);
		}
		else    //���� �� ��������
		{
			ShowMessage("File is not opened");
			Form1->FNameLabel->Caption="The file is not selected";
		}
}

//----------------------���������� ��������----------------------------------
void GetSpectrChart(TListBox* LIST)
{

	s = "V, m/s;";
	Form1->SpeedListBox->Clear();
	Form1->SpeedListBox->Items->Add(s.c_str());
	s = "Q, C*10^(-13);";
	Form1->ChargeListBox->Clear();
	Form1->ChargeListBox->Items->Add(s.c_str());

	Form1->SpeedChart->Series[0]->Clear();
	Form1->ChargeChart->Series[0]->Clear();

    double DAT[3];
	int P_NUM = LIST->Count;//������� ����� ����� ��������
	double* DATA_V=new double[P_NUM];
	double* DATA_Q=new double[P_NUM];
	i=0;
	while (i<P_NUM) //��� ������ ��������
	{
		SpectrP->setStr(UnicodeToString(LIST->Items->operator [](i)));
		SpectrP->getV(DAT);
		DATA_V[i]=DAT[colNum-1];
		if(colNum==2){DATA_V[i]=DATA_V[i]*SinglePerDoubleC;}

		SpectrP->getQ(DAT);
		if (colNum==3){DATA_Q[i]=(gainA*DAT[0]+gainB*DAT[1])/2;}
        else{DATA_Q[i]=gainA*DAT[0];}

		s=DoubleToString(DATA_V[i]);
		Form1->SpeedListBox->Items->Add(s.c_str());
		s=DoubleToString(DATA_Q[i]);
		Form1->ChargeListBox->Items->Add(s.c_str());

        i++;
	}

	Sort(DATA_V, P_NUM);      //��������� �������
    Sort(DATA_Q, P_NUM);

	j=1;                 //������ ���������� �� ��������
	k=1;                 //�� ������

    int NUM_V=0;  //����� ������ � ���������
    int NUM_Q=0;

	i=0;                 //����� ������ � �������

	Form1->SpeedChart->Series[0]->Clear();
	Form1->ChargeChart->Series[0]->Clear();

	Form1->SpeedChart->Series[0]->AddXY(0,0);
	Form1->ChargeChart->Series[0]->AddXY(0,0);
	while (i<P_NUM)
	{
		if ((DATA_V[i]<=j*stepDistrV)&(DATA_V[i]>(j-1)*stepDistrV))//���� � ���������
		{
			NUM_V++; //���� 1 � ������ �������
		}
		else        //�����
		{
			if(DATA_V[i]==j*stepDistrV){NUM_V++;}
			Form1->SpeedChart->Series[0]->AddXY((j-1)*stepDistrV,NUM_V);
			Form1->SpeedChart->Series[0]->AddXY((j)*stepDistrV,NUM_V);
			while ((DATA_V[i]>(j)*stepDistrV))
			{
				j++;
				Form1->SpeedChart->Series[0]->AddXY((j-1)*stepDistrV,0);
			}
			NUM_V=1;
		}
		if ((DATA_Q[i]<=k*stepDistrQ)&(DATA_Q[i]>(k-1)*stepDistrQ))//���� � ���������
		{
			NUM_Q++; //���� 1 � ������ �������
		}
		else        //�����
		{
			if(DATA_Q[i]==k*stepDistrQ){NUM_Q++;}
			Form1->ChargeChart->Series[0]->AddXY((k-1)*stepDistrQ,NUM_Q);
			Form1->ChargeChart->Series[0]->AddXY((k)*stepDistrQ,NUM_Q);
			while ((DATA_Q[i]>(k)*stepDistrQ))
			{
				k++;
				Form1->ChargeChart->Series[0]->AddXY((k-1)*stepDistrQ,0);
			}
			NUM_Q=1;
		}
        i++;
    }
    Form1->SpeedChart->Series[0]->AddXY((j-1)*stepDistrV,NUM_V);
    Form1->SpeedChart->Series[0]->AddXY((j)*stepDistrV,NUM_V);
    Form1->SpeedChart->Series[0]->AddXY((j)*stepDistrV,0);
	Form1->ChargeChart->Series[0]->AddXY((k-1)*stepDistrQ,NUM_Q);
	Form1->ChargeChart->Series[0]->AddXY((k)*stepDistrQ,NUM_Q);
	Form1->ChargeChart->Series[0]->AddXY((k)*stepDistrQ,0);

    delete [] DATA_V;
	delete [] DATA_Q;
}

//----------------------�������� ����----------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	limV = PhDoubleFromEdit(LimVEdit,0);  //���������� �������� ���������� � ������
	gainA = PhDoubleFromEdit(GainAEdit,0);
	gainB = PhDoubleFromEdit(GainBEdit,0);
	stepDistrV = PhDoubleFromEdit(DistrStepVEdit,0);
	stepDistrQ = PhDoubleFromEdit(DistrStepQEdit,0);
	Form1->SpeedChart->BottomAxis->Maximum = PhDoubleFromEdit(MaxSpeedEdit,0);
	Form1->ChargeChart->BottomAxis->Maximum = PhDoubleFromEdit(MaxChargeEdit,0);

	SinglePerDoubleC=PhDoubleFromEdit(CoefEdit,0);

	deltaV=PhDoubleFromEdit(DeltaSpeedCommEdit,1);
	deltaV_AB=PhDoubleFromEdit(DeltaSpeedABEdit,1);
	deltaQ_AB=PhDoubleFromEdit(DeltaChargeABEdit,5);

	deltaI12=PhDoubleFromEdit(DeltaI12Edit,1);
	deltaI23=PhDoubleFromEdit(DeltaI23Edit,1);
	deltaA12=PhDoubleFromEdit(DeltaA12Edit,1);
	deltaA23=PhDoubleFromEdit(DeltaA23Edit,1);
	baseLenght=NumFromEdit(BaseNumEdit,1,1000);

	fNumMin=NumFromEdit(MinFNumEdit,1,10000);
	fNumMax=NumFromEdit(MaxFNumEdit,fNumMin,10000);
}

//---------------------�������� ����-----------------------------------------
void __fastcall TForm1::Exit_ButtonClick(TObject *Sender)
{
	delete DataP;
    delete SpectrP;
	fclose (file_Data);
	Close();
}

//---------------------������ ����� � ������ ������--------------------------
void __fastcall TForm1::HandFNameButtonClick(TObject *Sender)
{
	if ( HandTextFileDialog->Execute() )
	//������ ��������
	{
		HandFNameButton->Enabled=0;
		FNameLabel->Caption=HandTextFileDialog->FileName;
		fName=UnicodeToString(FNameLabel->Caption);
		GetFBaseName();
		HandReadFile();
	}
	else //������ �� ��������
	{
		ShowMessage("File is not selected");
		FNameLabel->Caption="The file is not selected";
	}
}

//--------------------������� �������� � ������ �����------------------------

void __fastcall TForm1::YesButtonClick(TObject *Sender)
{
	YesButton->Enabled=0;
	NoButton->Enabled=0;

	SpectrP[0].calcSpectr();//������ �������, ����� �� �����
	s=SpectrP[0].getStr();
	HandListBox->Items->Add(s.c_str());

	HandSpectraButton->Enabled=1; //����� ������� ������

	if(HandCheckBox->Checked==0) //���� �������� ��������� �����
	{
		fileCount++;  //����� ����
		CounterToFnum(fileCount);
		FNameLabel->Caption=fName.c_str();
		HandReadFile();
	}
	else                                   //���� �������
	{
		HandFNameButton->Enabled=1;
	}
}

//-------------------������� ��������� � ������ ������-----------------------
void __fastcall TForm1::NoButtonClick(TObject *Sender)
{
	YesButton->Enabled=0;
	NoButton->Enabled=0;

	if(HandCheckBox->Checked==0)    //���� �������� ��������� �����
	{
		fileCount++;  //����� ����
		CounterToFnum(fileCount);
		FNameLabel->Caption=fName.c_str();
		HandReadFile();
	}
	else                            //���� �������
	{
		HandFNameButton->Enabled=1;
	}
}

//------------------��������� �������� � ������� �������---------------------
void __fastcall TForm1::SetValButtonClick(TObject *Sender)
{
	limV = PhDoubleFromEdit(LimVEdit,0);  //���������� �������� ���������� � ������
	gainA = PhDoubleFromEdit(GainAEdit,0);
	gainB = PhDoubleFromEdit(GainBEdit,0);
	stepDistrV = PhDoubleFromEdit(DistrStepVEdit,0);
	stepDistrQ = PhDoubleFromEdit(DistrStepQEdit,0);
	Form1->SpeedChart->BottomAxis->Maximum = PhDoubleFromEdit(MaxSpeedEdit,0);
	Form1->ChargeChart->BottomAxis->Maximum = PhDoubleFromEdit(MaxChargeEdit,0);

	SinglePerDoubleC=PhDoubleFromEdit(CoefEdit,0);

	deltaV=PhDoubleFromEdit(DeltaSpeedCommEdit,1);
	deltaV_AB=PhDoubleFromEdit(DeltaSpeedABEdit,1);
	deltaQ_AB=PhDoubleFromEdit(DeltaChargeABEdit,5);

	deltaI12=PhDoubleFromEdit(DeltaI12Edit,1);
	deltaI23=PhDoubleFromEdit(DeltaI23Edit,1);
	deltaA12=PhDoubleFromEdit(DeltaA12Edit,1);
	deltaA23=PhDoubleFromEdit(DeltaA23Edit,1);
	baseLenght=NumFromEdit(BaseNumEdit,1,1000);

	fNumMin=NumFromEdit(MinFNumEdit,1,10000);
	fNumMax=NumFromEdit(MaxFNumEdit,fNumMin,10000);
}

//------------------���������� �������� �� ������ ������� ������-------------
void __fastcall TForm1::HandSpectraButtonClick(TObject *Sender)
{
	GetSpectrChart(HandListBox);
}

//-------------------������� ����� �� ������� ������� ������-----------------
void __fastcall TForm1::HandClearButtonClick(TObject *Sender)
{
	HandChart->Series[0]->Clear();
	HandChart->Series[1]->Clear();
	HandListBox->Clear();
	YesButton->Enabled=0;
	NoButton->Enabled=0;
	HandFNameButton->Enabled=1;
	HandSpectraButton->Enabled=0;
}

//-----------------���������� � ������ � �������������� ������---------------
void __fastcall TForm1::AutoFNameButtonClick(TObject *Sender)
{

	if ( AutoTextFileDialog->Execute() )
	//������ ��������
	{
		AutoFNameButton->Enabled=0;
		fName=UnicodeToString(AutoTextFileDialog->FileName);
		GetFBaseName();
		FNameLabel->Caption=fBaseName.c_str();
		s= "Range of file numbers: "+IntToString(fNumMin)+"..."+IntToString(fNumMax)+"\n"
				+"Click 'START' to continue calculation";
		AutoLabel->Caption=s.c_str();
        StartButton->Enabled=1;
	}
	else //������ �� ��������
	{
		ShowMessage("File is not selected");
		FNameLabel->Caption="The file is not selected";
	}
}

//-----------------��������������� ���������� ������ � ��� ������------------
void __fastcall TForm1::StartButtonClick(TObject *Sender)
{
	int fileCountP=0;

	fileCount=fNumMin;
	if (FBaseCheckBox->Checked==1)
	{
		fName=fBaseName+".txt";
		AutoReadFile();
		if (SpectrP->Check(deltaA12,
				deltaA23,
				deltaI12,
				deltaI23,
				deltaV,
				deltaV_AB,
				deltaQ_AB,
				gainA,
				gainB,
				SinglePerDoubleC))
		{
			SpectrP->calcSpectr();//������ �������, ����� �� �����
			s=SpectrP->getStr();
			AutoListBox->Items->Add(s.c_str());
			fileCountP++;
		}
	}
	while (fileCount<=fNumMax)
	{
			CounterToFnum(fileCount);
			AutoReadFile();
			if (SpectrP->Check(deltaA12,
				deltaA23,
				deltaI12,
				deltaI23,
				deltaV,
				deltaV_AB,
				deltaQ_AB,
				gainA,
				gainB,
				SinglePerDoubleC))
			{
					SpectrP->calcSpectr();//������ �������, ����� �� �����
					s=SpectrP->getStr();
					AutoListBox->Items->Add(s.c_str());
					fileCountP++;
			}
			fileCount++;
	}

	AutoResLabel->Caption="";
	s= "The study is based on a "+IntToString(colNum)+"-column methodology; ";
	AutoResLabel->Caption=s.c_str();
	s= "\n" + IntToString(fileCountP) + " files out of "+ IntToString(fNumMax-fNumMin+1) + " are taken into account in the spectrum.";
	AutoResLabel->Caption=AutoResLabel->Caption+s.c_str();

	AutoSpectraButton->Enabled=1;
	AutoClearButton->Enabled=1;

}

//-----------------���������� �������� �� ������ ���� ������-----------------
void __fastcall TForm1::AutoSpectraButtonClick(TObject *Sender)
{
		GetSpectrChart(AutoListBox);
}

//-----------------������� ����� �� ������� ��� ������-----------------------
void __fastcall TForm1::AutoClearButtonClick(TObject *Sender)
{
	AutoListBox->Clear();
	AutoFNameButton->Enabled=1;
	StartButton->Enabled=0;
	AutoSpectraButton->Enabled=0;
}
//---------------------------------------------------------------------------

