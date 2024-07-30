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

//----------------------глобальные переменные--------------------------------
FILE* file_Data;          //осциллограмма - чтение
FILE* file_Res;           //спектр - запись

std::string fName; //имя и путь к файлу
std::string fBaseName; //имя и путь к файлу

int strNum, colNum; //кол-во строк и столбцов в файле данных
int fileSize;      //размер файла в байтах

double limV=5000;//предел напряжения
bool mvFlag=0;//флаг размерности, если 1 - мВ


int fileCount; //счётчик файлов
int i,j,k,m;//счётчики

char c;//буферы
char cBuf[8];//буфер
std::string s;//буфер
double Buf[3];

DataPoint* DataP=new DataPoint(2); //буфер точки осцилограммы
SpectrPoint* SpectrP=new SpectrPoint(2);//буфер точки спектра

//---------------------преобразования типов всякие---------------------------
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
	int SIZE=2;  //размер строки
	int N=n;
	while (N>0)
	{
		N=N/10;
		SIZE++;
	}

	cBuf[0]='(';
	s=IntToString(n);

	N=1; //теперь это счётчик
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

//--------------------имя и путь к файлу по счётчику--------------------------
void CounterToFnum (int n)
{
	s= NumToString(n); //n -> "(n)"
	fName=fBaseName+" "+s+".txt";
}

//--------------------получение базового названия файла----------------------
void GetFBaseName()
{
	fBaseName=fName;//временное(?) решение - пока стартуем с начала
	std::string to_delete=").txt";  // какую подстроку удалить
	size_t start =fBaseName.find(to_delete);            // находим позицию подстроки
	if (start != std::string::npos) // если такая подстрока есть, перебираем числа
	{
		fileCount=0;
		to_delete=" "+NumToString(fileCount)+".txt";
		start =fBaseName.find(to_delete);
		while ((start == std::string::npos)&(i<MAX_FNUM)) //
		{
			fileCount++;
			to_delete=" "+NumToString(fileCount)+".txt";
			start =fBaseName.find(to_delete);
			if (start != std::string::npos) // находим и удаляем все вхождения to_delete
			{
				fBaseName.erase(start, to_delete.length());
				//start = fBaseName.find(to_delete, start + to_delete.length());
			}
		}
	}
	else
	{
		to_delete=" .txt";
		if (start != std::string::npos) // находим и удаляем все вхождения to_delete
			{
				fBaseName.erase(start, to_delete.length());
				//start = fBaseName.find(to_delete, start + to_delete.length());
			}
		fileCount=1;
	}
}

//--------------------проверка соответствия размера файла--------------------
bool CheckFileSize()
{
	fseek( file_Data , 0 , SEEK_END );//в конец файла маркер
	bool B=((fileSize-ftell(file_Data))>1000)||((fileSize-ftell(file_Data))<-1000);
	fileSize = ftell(file_Data);
	return(B);
}

//--------------------получение размера таблицы------------------------------
void GetFileSize()
{
	fseek( file_Data , 0 , SEEK_END );//в конец файла маркер
	fileSize = ftell(file_Data);//размер файла в байтах
	fseek( file_Data , 0 , SEEK_SET );//обратно
	strNum=0;
	colNum=0;
	while (ftell(file_Data)<fileSize)//подсчёт размеров файла
	{
		fread(&c,1,1,file_Data);
		if (c=='\n')
		{strNum++;}
		if (c=='\t')
		{colNum++;}
	}
	strNum=strNum-3;
	colNum=((colNum-2)/strNum)+1;       //подбивка размеров
	delete DataP;
	delete SpectrP;
	DataP=new DataPoint(colNum);
	SpectrP=new SpectrPoint(colNum);
}

//--------------------подготовка к чтению,выделение памяти-------------------
void PrepareForRead()
{
	fseek( file_Data , 0 , SEEK_SET );//маркер в начало
	i=0;
	j=0;
	mvFlag=1;
	while (i<3)  //первые строки пропустил
	{
		fread(&c,1,1,file_Data);
		if (i==1)
		{
			j=0;
			while (j<7)
			{
				cBuf[j]=cBuf[j+1];
				j++;
			}                              //проверка наличия В во второй строке
			cBuf[7]=c;                     //если есть то флаг в 0
			s=cBuf;
			if (s=="СЃ)\t(Р’)"){mvFlag=0;}
		}
		if (c=='\n') {i++;}
	}
	SpectrP->to_zero();//экстремумы в ноль для нового вычисления максимумов
}

//--------------------чтение строки из файла в память-------------------------
void ReadStrFile(double* DAT)
{
	fseek( file_Data , -1 , SEEK_CUR );//шаг назад для чтения
	i=0;
	while (c!='\n') {fread(&c,1,1,file_Data);}
	fread(&c,1,1,file_Data);
	while(i<colNum)//пока строка
	{
		j=0;
		c=0;
		while((j<7)&(c!='\t')&(c!='\n'))//цифры
		{
			fread(&c,1,1,file_Data);
			cBuf[j]=c;
			j++;
		}
		if (j<7)     //если зашкал
		{
			if (cBuf[1]=='-'){DAT[i]=-limV/1000;}
			else {DAT[i]=limV/1000;}
		}
		else        //если не зашкал
		{
			s=cBuf;
			DAT[i]=atof(s.c_str());
			while ((c!='\t')&(c!='\n')) {fread(&c,1,1,file_Data);}
		}
		if ((mvFlag==0)&(i!=0))
		{DAT[i]=DAT[i]*1000;}  //подгонка размерности под мВ
		i++;
	}

}

//--------------------чтение данных---------------------------------------
void HandReadFile()
{
		Form1->Series1->Clear();
		Form1->Series2->Clear();

		file_Data = fopen(fName.c_str(), "r");
		if (file_Data != NULL)  //файл открылся
		{

			if (CheckFileSize()){GetFileSize();} //если несоответствие - считали размер
			PrepareForRead();//подготовка к чтению

			m=0;
			while(m<strNum)
			{
				ReadStrFile(Buf);//чтение строки
				DataP->setP(Buf);//значения в класс
				SpectrP->extrSpectr(*DataP);//снятие спектров
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
		else    //файл не открылся
		{
			ShowMessage("File is not opened");
			Form1->FNameLabel->Caption="The file is not selected";
		}
}

//----------------------открытие окна----------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

}

//---------------------закрытие окна-----------------------------------------
void __fastcall TForm1::Exit_ButtonClick(TObject *Sender)
{
	delete DataP;
    delete SpectrP;
	fclose (file_Data);
	Close();
}

//---------------------чтение файла в ручном режиме--------------------------
void __fastcall TForm1::HandFNameButtonClick(TObject *Sender)
{
	if ( HandTextFileDialog->Execute() )
	//диалог сработал
	{
		HandFNameButton->Enabled=0;
		FNameLabel->Caption=HandTextFileDialog->FileName;
		fName=UnicodeToString(FNameLabel->Caption);
		GetFBaseName();
		HandReadFile();
	}
	else //диалог не сработал
	{
		ShowMessage("File is not selected");
		FNameLabel->Caption="The file is not selected";
	}
}

//--------------------графики одобрены в ручном режие------------------------

void __fastcall TForm1::YesButtonClick(TObject *Sender)
{
	YesButton->Enabled=0;
	NoButton->Enabled=0;

	SpectrP[0].calcSpectr();//расчёт величин, вывод на экран
	s=SpectrP[0].getStr();
	HandListBox->Items->Add(s.c_str());

	if(HandCheckBox->Checked==0)
	{
		fileCount++;  //новый файл
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
		fileCount++;  //новый файл
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

