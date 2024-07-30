//---------------------------------------------------------------------------

#ifndef ClassesH
#define ClassesH

#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <cmath>

class DataPoint
{
  private:
	double dataStr[3];
	int ch;
  public:
	DataPoint (int);//при создании объекта класса задается размерность
	~DataPoint ();
	void setA(double ); // установка значений
	void setB(double );
	void setT(double );
	void setP(double* );
	double getA();// получение значений
	double getB();
	double getT();
	void getP(double*);
  protected:

};
//---------------------------------------------------------------------------
				//точка спектра - амплитуда и скорость импульса
				//по каждому из каналов и вместе
class SpectrPoint
{
  private:
	double Q[2];   //Искомые параметры
	double V[3];
	double Max[2];   //получаем из спектра
	double TMax[2];
	double Min[2];
	double TMin[2];

	int ch;

  public:
	SpectrPoint (int);
	~SpectrPoint ();
	void to_zero(); //экстремумы в ноль

	void setQ(double* )	; // установка значений
	void setV(double* )	;

	void  getQ(double*); // получение значений
	void getV(double*);
	void extrSpectr( DataPoint);//сравниваем, ищем экстремумы
	void calcSpectr(); // расчет скоростей и ампитуд

	std::string getStr();
	void setStr(std::string);

protected:


};
//---------------------------------------------------------------------------
#endif
