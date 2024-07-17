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

double** dataArr;  //������ ��� ����� ������
double limV=2000;//������ ����������

int i,j,k;//��������
char c;//�����
char cBuf[8];//�����
std::string s;//�����

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
	ss << std::setprecision(5) << a;
	std::string s = ss.str();
	return s;
}
double StringToDouble (std::string str)
{
	//std::string str = a;
	std::istringstream iss(str);
	double result;
	iss >> result;
	return result;
}
//--------------------��������� ������� �����,��������� ������---------------
void GetFileSize()
{
	fseek( file_Data , 0 , SEEK_END );//� ����� ����� ������
	fileSize = ftell(file_Data);//������ ����� � ������
	fseek( file_Data , 0 , SEEK_SET );//�������
	i=0;
	strNum=0;
	colNum=0;
	while (ftell(file_Data)<fileSize)//������� �������� �����
	{
		fread(&c,1,1,file_Data);
		if (c=='\n')
		{strNum++;}
		if (c=='\t')
		{colNum++;}
		i++;
	}
	strNum=strNum-3;
	colNum=((colNum-2)/strNum)+1;       //�������� ��������

	dataArr = new double*[colNum];//��������� ������
	i=0;
	while (i<colNum)
	{
		dataArr[i] = new double[strNum];
		i++;
	}
}

//--------------------������ ����� � ������----------------------------------
void ReadFile()
{
	fseek( file_Data , 0 , SEEK_SET );//������ � ������
	i=0;
	while (i<3)  //������ ������ ���������
	{
		fread(&c,1,1,file_Data);
		if (c=='\n') {i++;}
	}
	i=0;
	while (i<strNum)//c������
	{
		j=0;
		while(j<colNum)//������
		{
			k=0;
			c=0;
			while((k<8)&(c!='\t')&(c!='\n'))//�����
			{
				fread(&c,1,1,file_Data);
				cBuf[k]=c;
				k++;
			}
			if (k<8)     //���� ������
			{
				if (cBuf[1]=='-'){dataArr[j][i]=-limV;}
				else {dataArr[i][j]=limV;}
			}
			else        //���� �� ������
			{
				s=cBuf;
				dataArr[j][i]=atof(s.c_str());
				while ((c!='\t')&(c!='\n')) {fread(&c,1,1,file_Data);}
			}
			j++;
		}
		i++;
    }
}

//--------------------��������� ������----------------------------------
void Calc()
{

}

//----------------------�������� ����----------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------�������� ����-----------------------------------------
void __fastcall TForm1::Exit_ButtonClick(TObject *Sender)
{
	delete dataArr;
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
			GetFileSize();
			ReadFile();
			i=0;
			while (i<(colNum-1))
			{
				TLineSeries *serie = new TLineSeries(HandChart);
				HandChart->AddSeries(serie);
				serie->Title = IntToString(i+1).c_str();
				serie->LinePen->Width = 2;
				j=0;
				while(j<strNum)
				{
					serie->AddXY(dataArr[0][j],dataArr[i+1][j]);
					j++;
					s=DoubleToString(dataArr[0][j])+"\t"+DoubleToString(dataArr[i+1][j]);
					HandListBox->Items->Add(s.c_str());
				}
				i++;
			}
			fclose (file_Data);
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

