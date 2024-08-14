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
int fNumMin, fNumMax;//диапазон номеров файлов

double limV;//предел напряжения
double gainA; //усиление по каналам
double gainB;

double SinglePerDoubleC; //коэффициент для домножения в случае одного канала

double stepDistrV;//области суммирования при построении спектров
double stepDistrQ;

double deltaV, deltaV_AB, deltaQ_AB;//расчёт для двух каналов

double deltaI12, deltaI23; //предельные отклонения амплитуд и интегралов
double deltaA12, deltaA23;
int baseLenght;  //длина отрезка, по которому строится базовая линия

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

//---------------------целое число из Editа---------------------------
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

//---------------------дробное число из Editа---------------------------
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

//--------------------имя и путь к файлу по счётчику--------------------------
void CounterToFnum (int n)
{
	s= NumToString(n); //n -> "(n)"
	fName=fBaseName+" "+s+".txt";
}

//--------------------сортировка массива-------------------------------------
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

//--------------------получение базового названия файла----------------------
void GetFBaseName()
{
	fBaseName=fName;// решение - пока стартуем с начала
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
		k=0;
		while(k<colNum-1)
		{
			Form1->HandChart->Series[k]->Clear();
			k++;
		}

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

//--------------------чтение данных---------------------------------------
void AutoReadFile()
{
		file_Data = fopen(fName.c_str(), "r");
		if (file_Data != NULL)  //файл открылся
		{

			if (CheckFileSize()){GetFileSize();} //если несоответствие - считали размер
			PrepareForRead();//подготовка к чтению

			SpectrP->zeroBase();
			m=0;
			while(m<baseLenght) //построение базовой линии
			{
				ReadStrFile(Buf);//чтение строки
				DataP->setP(Buf);//значения в класс
				SpectrP->setBase(*DataP, baseLenght);
				m++;
			}
			while(m<strNum)
			{
				ReadStrFile(Buf);//чтение строки
				DataP->setP(Buf);//значения в класс
				SpectrP->extrSpectr(*DataP);//снятие спектров
				SpectrP-> extrAandI(*DataP);//получение контр. параметров
				m++;
			}
			SpectrP[0].calcSpectr();

			fclose (file_Data);
		}
		else    //файл не открылся
		{
			ShowMessage("File is not opened");
			Form1->FNameLabel->Caption="The file is not selected";
		}
}

//----------------------построение спектров----------------------------------
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
	int P_NUM = LIST->Count;//сколько всего строк записано
	double* DATA_V=new double[P_NUM];
	double* DATA_Q=new double[P_NUM];
	i=0;
	while (i<P_NUM) //все строки считываю
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

	Sort(DATA_V, P_NUM);      //сортируем массивы
    Sort(DATA_Q, P_NUM);

	j=1;                 //номера интервалов по скорости
	k=1;                 //по заряду

    int NUM_V=0;  //число частиц в интервале
    int NUM_Q=0;

	i=0;                 //номер строки в массиве

	Form1->SpeedChart->Series[0]->Clear();
	Form1->ChargeChart->Series[0]->Clear();

	Form1->SpeedChart->Series[0]->AddXY(0,0);
	Form1->ChargeChart->Series[0]->AddXY(0,0);
	while (i<P_NUM)
	{
		if ((DATA_V[i]<=j*stepDistrV)&(DATA_V[i]>(j-1)*stepDistrV))//если в интервале
		{
			NUM_V++; //плюс 1 к высоте столбца
		}
		else        //иначе
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
		if ((DATA_Q[i]<=k*stepDistrQ)&(DATA_Q[i]>(k-1)*stepDistrQ))//если в интервале
		{
			NUM_Q++; //плюс 1 к высоте столбца
		}
		else        //иначе
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

//----------------------открытие окна----------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	limV = PhDoubleFromEdit(LimVEdit,0);  //считывание значений параметров с экрана
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

	HandSpectraButton->Enabled=1; //можно считать спектр

	if(HandCheckBox->Checked==0) //если отключен одиночный режим
	{
		fileCount++;  //новый файл
		CounterToFnum(fileCount);
		FNameLabel->Caption=fName.c_str();
		HandReadFile();
	}
	else                                   //если включен
	{
		HandFNameButton->Enabled=1;
	}
}

//-------------------графики отклонены в ручном режиме-----------------------
void __fastcall TForm1::NoButtonClick(TObject *Sender)
{
	YesButton->Enabled=0;
	NoButton->Enabled=0;

	if(HandCheckBox->Checked==0)    //если отключен одиночный режим
	{
		fileCount++;  //новый файл
		CounterToFnum(fileCount);
		FNameLabel->Caption=fName.c_str();
		HandReadFile();
	}
	else                            //если включен
	{
		HandFNameButton->Enabled=1;
	}
}

//------------------Установка значение с вкладки сетингс---------------------
void __fastcall TForm1::SetValButtonClick(TObject *Sender)
{
	limV = PhDoubleFromEdit(LimVEdit,0);  //считывание значений параметров с экрана
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

//------------------построение спектров по данным ручного режима-------------
void __fastcall TForm1::HandSpectraButtonClick(TObject *Sender)
{
	GetSpectrChart(HandListBox);
}

//-------------------очистка всего на вкладке ручного режима-----------------
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

//-----------------подготовка к чтению в автоматическом режиме---------------
void __fastcall TForm1::AutoFNameButtonClick(TObject *Sender)
{

	if ( AutoTextFileDialog->Execute() )
	//диалог сработал
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
	else //диалог не сработал
	{
		ShowMessage("File is not selected");
		FNameLabel->Caption="The file is not selected";
	}
}

//-----------------последовательно считывание файлов в авт режиме------------
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
			SpectrP->calcSpectr();//расчёт величин, вывод на экран
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
					SpectrP->calcSpectr();//расчёт величин, вывод на экран
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

//-----------------построение спектров по данным авто режима-----------------
void __fastcall TForm1::AutoSpectraButtonClick(TObject *Sender)
{
		GetSpectrChart(AutoListBox);
}

//-----------------очистка всего во вкладке авт режима-----------------------
void __fastcall TForm1::AutoClearButtonClick(TObject *Sender)
{
	AutoListBox->Clear();
	AutoFNameButton->Enabled=1;
	StartButton->Enabled=0;
	AutoSpectraButton->Enabled=0;
}
//---------------------------------------------------------------------------

