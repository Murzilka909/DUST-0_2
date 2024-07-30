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

double limV=5000;//������ ����������
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

//--------------------��� � ���� � ����� �� ��������--------------------------
void CounterToFnum (int n)
{
	s= NumToString(n); //n -> "(n)"
	fName=fBaseName+" "+s+".txt";
}

//--------------------��������� �������� �������� �����----------------------
void GetFBaseName()
{
	fBaseName=fName;//���������(?) ������� - ���� �������� � ������
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
		Form1->Series1->Clear();
		Form1->Series2->Clear();

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

//----------------------�������� ����----------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

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

	if(HandCheckBox->Checked==0)
	{
		fileCount++;  //����� ����
		CounterToFnum(fileCount);
		FNameLabel->Caption=fName.c_str();
		HandReadFile();
	}
	else
	{
		HandFNameButton->Enabled=1;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NoButtonClick(TObject *Sender)
{
    YesButton->Enabled=0;
	NoButton->Enabled=0;

	if(HandCheckBox->Checked==0)
	{
		fileCount++;  //����� ����
		CounterToFnum(fileCount);
		FNameLabel->Caption=fName.c_str();
		HandReadFile();
	}
	else
	{
		HandFNameButton->Enabled=1;
	}
}
//---------------------------------------------------------------------------

