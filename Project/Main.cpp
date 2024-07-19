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
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//----------------------���������� ����������--------------------------------
FILE* file_Data;          //������������� - ������
FILE* file_Res;           //������ - ������

std::string fName; //��� � ���� � �����

int strNum, colNum; //���-�� ����� � �������� � ����� ������
int fileSize;      //������ ����� � ������

double limV=2000;//������ ����������
bool mvFlag=0;

int i,j,k;//��������
char c;//�����
char cBuf[8];//�����
std::string s;//�����

DataPoint* DataP; //����� ����� ������������
SpectrPoint* SpectrP;//����� ����� �������


//---------------------�������������� ����� ������---------------------------
std::string UnicodeToString (UnicodeString us)
{
	AnsiString as=us;
	std::string s = as.c_str();
	return s;
}
std::string IntToString (int a)
{
	std::stringstream ss;
	ss << a;
	std::string s = ss.str();
	return s;
}
std::string DoubleToString(double a)
{
	std::stringstream ss;
	ss.setf(std::ios::scientific, std::ios::floatfield);
	ss << std::setprecision(8) << a;
	std::string s = ss.str();
	return s;
}
std::string CounterToFnum (int a, int n)
{
	char* ch = new char[5];
	ch[0]='(';
	if (n==3) {ch[1]=(char)(((int)'0')+a);}
	if (n==4)
	{
		ch[2]=(char)(((int)'0')+a%10);
		ch[1]=(char)(((int)'0')+a/10);
	}
	if (n==5)
	{
		ch[3]=(char)(((int)'0')+a%10);
		ch[2]=(char)(((int)'0')+(a/10)%10);
		ch[1]=(char)(((int)'0')+(a/100));
	}
	ch[n-1]=')';
	/*int a1 = a%10;
	int a2 = (a%100)/10;
	int a3 = (a%1000)/100;
	int a4 = a/1000;
	char ch [5];
	ch[0] = '-';
	ch[1] = (char)(((int)'0')+a4);
	ch[2] = (char)(((int)'0')+a3);
	ch[3] = (char)(((int)'0')+a2);
	ch[4] = (char)(((int)'0')+a1);
	//std::string s(ch);*/ //���� ����� ��� ������ ������ � ���������� � �������
	//����-������4�����
	//������ ������������ ������ ���� (�����)
	return (ch);
}

//--------------------��������� ������� �����,��������� ������---------------
void GetFileSize()
{
	fseek( file_Data , 0 , SEEK_END );//� ����� ����� ������
	fileSize = ftell(file_Data);//������ ����� � ������
	fseek( file_Data , 0 , SEEK_SET );//�������
	int count=0;
	strNum=0;
	colNum=0;
	while (ftell(file_Data)<fileSize)//������� �������� �����
	{
		fread(&c,1,1,file_Data);
		if (c=='\n')
		{strNum++;}
		if (c=='\t')
		{colNum++;}
		count++;
	}
	strNum=strNum-3;
	colNum=((colNum-2)/strNum)+1;       //�������� ��������
}

//--------------------���������� � ������ -----------------------------------
void PrepareForRead()
{
	fseek( file_Data , 0 , SEEK_SET );//������ � ������
	int count=0;
	int count_1=0;
	mvFlag=1;
	while (count<3)  //������ ������ ���������
	{
		fread(&c,1,1,file_Data);
		if (count==1)
		{
			count_1=0;
			while (count_1<7)
			{
				cBuf[count_1]=cBuf[count_1+1];
                count_1++;
			}                              //�������� ������� � �� ������ ������
			cBuf[7]=c;                     //���� ���� �� ���� � 0
			s=cBuf;
			if (s=="с)\t(В)"){mvFlag=0;}
		}
		if (c=='\n') {count++;}
	}
}

//--------------------������ ������ �� ����� � ������-------------------------
void ReadStrFile(double* DAT)
{
	int count=0;
	int count_1;
	fseek( file_Data , -1 , SEEK_CUR );
	while (c!='\n') {fread(&c,1,1,file_Data);}
	fread(&c,1,1,file_Data);
	while(count<colNum)//������
	{
		count_1=0;
		c=0;
		while((count_1<8)&(c!='\t')&(c!='\n'))//�����
		{
			fread(&c,1,1,file_Data);
			cBuf[count_1]=c;
			count_1++;
		}
		if (count_1<8)     //���� ������
		{
			if (cBuf[1]=='-'){DAT[count]=-limV;}
			else {DAT[count]=limV;}
		}
		else        //���� �� ������
		{
			s=cBuf;
			DAT[count]=atof(s.c_str());
			while ((c!='\t')&(c!='\n')) {fread(&c,1,1,file_Data);}
		}
		if ((mvFlag==0)&(count!=0))
		{DAT[count]=DAT[count]*1000;}  //�������� ����������� ��� ��
		count++;
	}

}

//--------------------��������� ������---------------------------------------
void Calc()
{

}

//----------------------�������� ����----------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	TLineSeries *serie = new TLineSeries(HandChart);
	HandChart->AddSeries(serie);
	serie->Title = "A";
	serie->LinePen->Width = 2;

	serie = new TLineSeries(HandChart);
	HandChart->AddSeries(serie);
	serie->Title = "B";
	serie->LinePen->Width = 2;
}

//---------------------�������� ����-----------------------------------------
void __fastcall TForm1::Exit_ButtonClick(TObject *Sender)
{
	fclose (file_Data);
	Close();
}

//---------------------������ ����� � ������ ������--------------------------
void __fastcall TForm1::HandFNameButtonClick(TObject *Sender)
{
	fclose (file_Data);
	if ( HandTextFileDialog->Execute() )
	//������ ��������
	{
		FNameLabel->Caption=HandTextFileDialog->FileName;
		fName=UnicodeToString(FNameLabel->Caption);
		file_Data = fopen(fName.c_str(), "r");
		if (file_Data != NULL)  //���� ��������
		{
			GetFileSize();  //c������ �������
			HandChart->Series[0]->Clear();
			HandChart->Series[1]->Clear();
			PrepareForRead();//���������� � ������
			DataP=new DataPoint(colNum);
			SpectrP=new SpectrPoint(colNum);

			double* BUF= new double[colNum];
			i=0;
			while(i<strNum)
			{
				ReadStrFile(BUF);//������ ������
				DataP[0].setP(BUF);//�������� � �����
				SpectrP[0].extrSpectr(DataP[0]);//������ ��������
				j=0;
				while(j<colNum-1)
				{
					HandChart->Series[j]->AddXY(BUF[0],BUF[j+1]);
					j++;
				}
				i++;
			}
			fclose (file_Data);
			delete BUF;

			YesButton->Enabled=1;
			NoButton->Enabled=1;
		}
		else    //���� �� ��������
		{
			ShowMessage("File is not opened");
			FNameLabel->Caption="The file is not selected";
		}
	}
	else //������ �� ��������
	{
		ShowMessage("File is not selected");
		FNameLabel->Caption="The file is not selected";
	}
}

//---------------------------------------------------------------------------

void __fastcall TForm1::YesButtonClick(TObject *Sender)
{
	SpectrP[0].calcSpectr();
	s=SpectrP[0].getStr();
	HandListBox->Items->Add(s.c_str());
}
//---------------------------------------------------------------------------

