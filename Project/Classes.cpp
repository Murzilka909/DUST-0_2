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

double DeltaCalc(double A, double B)
{
	if (A==B)
	{
		return 0;
	}
	else
	{
		if (A>B)
		{
			return ((A-B)/(B+0.000001));
		}
		else
		{return ((B-A)/(A+0.000001));}
	}
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
		count=0;
		A=0;
		I=0;
		while (count<(3))//если два канала, то проверку будем делать
		{
			Integral[count]=0;
			Amp[count]=0;
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
	}

	// установка значений
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
		while (count<(ch))
		{
			v[count]=V[count];
			count++;
		}
	}

	 //базовую линию в ноль
	void SpectrPoint::zeroBase()
	{
		BASE=0;
		int count=0;
		A=0;
		I=0;
		while (count<3)
		{
			Integral[count]=0;
			Amp[count]=0;
			count++;
		}
	}

	//установка базовой линии по точке данных
	void SpectrPoint::setBase( DataPoint Point, int NUM)
	{
		double* P=new double[ch];
		Point.getP(P);
		BASE=BASE+P[1]/NUM;
		delete[] P;
	}

	//получение интегралов и амплитуд
	void SpectrPoint::extrAandI( DataPoint Point)
	{
		double* P=new double[ch];
		if (I*(P[1]-BASE)<0) //если знак сменился
		{
			if((Integral[0])<(fabs(I)))
			{
				Integral[2]=Integral[1];
				Integral[1]=Integral[0];
				Integral[0]=fabs(I);
			}
			else
			{
				if((Integral[1])<(fabs(I)))
				{
					Integral[2]=Integral[1];
					Integral[1]=fabs(I);
				}
				else
				{
					if((Integral[2])<(fabs(I))){Integral[2]=fabs(I);}
				}
			}

			if((Amp[0])<(fabs(A)))
			{
				Amp[2]=Amp[1];
				Amp[1]=Amp[0];
				Amp[0]=fabs(A);
			}
			else
			{
				if((Amp[1])<(fabs(A)))
				{
					Amp[2]=Amp[1];
					Amp[1]=fabs(A);
				}
				else
				{
					if((Amp[2])<(fabs(A))){Amp[2]=fabs(A);}
				}
			}
			I=P[1]-BASE;
			A=fabs(P[1]-BASE);
		}
		else
		{
			I=I+P[1]-BASE;
			if (fabs(P[1]-BASE)>A) {A=fabs(P[1]-BASE);}
        }
		delete[] P;
	}

	//проверка отклонений
	bool SpectrPoint::Check(double A12,
				double A23,
				double I12,
				double I23,
				double dS,
				double dS_AB,
				double dQ,
				double COEF1,
				double COEF2,
				double VperVcomm)
	{
		bool a=1;
		bool b;
		if (ch==3)
		{
			b=DeltaCalc((V[0]+V[1])*VperVcomm, 2*V[2])<dS;
			a=a&b;
			b=DeltaCalc(V[0], V[1])<dS_AB;
			a=a&b;
			b=DeltaCalc(Q[0]*COEF1, Q[1]*COEF2)<dQ;
			a=a&b;
			return a;
		}
		else
		{
			b=DeltaCalc(Amp[0], Amp[1])<A12;
			a=a&b;
			b=DeltaCalc(Amp[1], Amp[3])>A23;
			a=a&b;
			b=DeltaCalc(Integral[0], Integral[1])<I12;
			a=a&b;
			b=DeltaCalc(Integral[1], Integral[3])>I23;
			a=a&b;
			return a;
        }
    }


	//сравниваем, ищем экстремумы
	void SpectrPoint::extrSpectr( DataPoint Point)
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

	// расчет скоростей и ампитуд
	void SpectrPoint::calcSpectr()
	{
		int count =0;
		while (count<(ch-1))
		{
			Q[count]=fabs(Max[count]-Min[count])/2.0;
			V[count]=0.07/((fabs(TMin[count]-TMax[count])+0.0000001)/1000);
			count++;
		}
		if(ch==3)
		{V[count]=1/((fabs(TMin[1]-TMin[0])+0.0000001)/1000);}
		else
		{V[count]=V[0];}
	}

	// работа со строками
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
			STR.erase(0, 9);
			count++;
		}
		count=0;
		while (count<ch-1)
		{
			Q[count]=atof(STR.c_str());
			STR.erase(0, 9);
			count++;
		}

	}


//---------------------------------------------------------------------------
#pragma package(smart_init)
