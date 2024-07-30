//---------------------------------------------------------------------------

#pragma hdrstop

#include <cmath>
#include <math.h>
#include <vcl.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <stdlib.h>
#include <iomanip>

#include "Classes.h"
std::string DoubleToString(double a)
{
	std::stringstream ss;
	ss.setf(std::ios::scientific, std::ios::floatfield);
	ss << std::setprecision(2) << a;
	std::string s = ss.str();
	return s;
}
//---------------------------------------------------------------------------
			   //точка данных - время + значения напряжения на каналах
			   //+ коэффициентсвязи по амплитуде

	DataPoint::DataPoint (int N)
	{
		ch=N;
	} // число столбцов в конструкторе

	DataPoint::~DataPoint ()
	{
	}
	void DataPoint::setA(double a)			{dataStr[1]=a;} // установка значений
	void DataPoint::setB(double b)			{dataStr[2]=b;}
	void DataPoint::setT(double t)			{dataStr[0]=t;}
	void DataPoint::setP(double* P)
	{
		int count=0;
		while (count<ch)
		{
			dataStr[count]=P[count];
			count++;
		}
	}

	double DataPoint::getA()			{return dataStr[1];} // получение значений
	double DataPoint::getB()			{return dataStr[2];}
	double DataPoint::getT()			{return dataStr[0];}

	void DataPoint::getP(double* P)
	{
		int count=0;
		while (count<ch)
		{
			P[count]=dataStr[count];
			count++;
		}
	}

//---------------------------------------------------------------------------
				//точка спектра - амплитуда и скорость импульса
				//по каждому из каналов и вместе
	SpectrPoint::SpectrPoint (int N)
	{
		ch=N;
		int count=0;
		while (count<(ch-1))
		{
			Max[count]=-1;
			TMax[count]=0;
			Min[count]=1;
			TMin[count]=0;
			count++;
		}
	}
	SpectrPoint::~SpectrPoint ()
	{
    }
	void SpectrPoint::to_zero() //экстремумы в ноль
	{
		int count=0;
		while (count<(ch-1))
		{
			Max[count]=-1;
			TMax[count]=0;
			Min[count]=1;
			TMin[count]=0;
			count++;
		}
    }
	void SpectrPoint::setQ(double* q)
	{
		int count=0;
		while (count<(ch-1))
		{
			Q[count]=q[count];
			count++;
		}
	} // установка значений
	void SpectrPoint::setV(double* v)
	{
		int count=0;
		while (count<(ch-1))
		{
			V[count]=v[count];
			count++;
		}
	} // установка значений

	void SpectrPoint::getQ(double *q)
	{
		int count=0;
		while (count<(ch-1))
		{
			q[count]=Q[count];
			count++;
		}
	}
	 // получение значений
	void SpectrPoint::getV(double *v)
	{
		int count=0;
		while (count<(ch-1))
		{
			v[count]=V[count];
			count++;
		}
	}

	void SpectrPoint::extrSpectr( DataPoint Point)//сравниваем, ищем экстремумы
	{
		double* P=new double[ch];
		int count =0;
		while (count<(ch-1))
		{
			Point.getP(P);
			if ((P[count+1])<Min[count])
			{
				Min[count]=(P[count+1]);
				TMin[count]=P[0];
			}
			if ((P[count+1])>Max[count])
			{
				Max[count]=(P[count+1]);
				TMax[count]=P[0];
			}
			count++;
		}
		delete[] P;
	}

	void SpectrPoint::calcSpectr() // расчет скоростей и ампитуд
	{
		int count =0;
		while (count<(ch-1))
		{
			Q[count]=fabs(Max[count]-Min[count])/2;
			V[count]=0.07/((fabs(TMin[count]-TMax[count])+0.0000001)/1000);
			count++;
		}
		if(ch==3)
		{V[count]=1/((fabs(TMin[1]-TMin[0])+0.0000001)/1000);}
		else
		{V[count]=V[0];}
	}

	std::string SpectrPoint::getStr()
	{
		std::string STR="";
		int count =0;
		while (count<ch)
		{
			STR=STR+DoubleToString(V[count])+"\t";
			count++;
		}
		count =0;
		while (count<(ch-1))
		{
			STR=STR+DoubleToString(Q[count])+"\t";
			count++;
		}
		return STR;
	}


	void SpectrPoint::setStr(std::string STR)
	{
		int count=0;
		while (count<ch)
		{
			V[count]=atof(STR.c_str());
			STR.erase(0, 8);
			count++;
		}
		count=0;
		while (count<ch-1)
		{
			Q[count]=atof(STR.c_str());
			STR.erase(0, 8);
			count++;
		}

	}


//---------------------------------------------------------------------------
#pragma package(smart_init)
