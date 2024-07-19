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
	double * dataStr;
	int ch;
  public:
	DataPoint (int);//при создании объекта класса задается размерность
	//2 или 3 столбца
	void setA(double ); // установка значений
	void setB(double );
	void setT(double );
	void setP(double* );
	double getA();// получение значений
	double getB();
	double getT();
	double* getP();
  protected:

};
//---------------------------------------------------------------------------
				//точка спектра - амплитуда и скорость импульса
				//по каждому из каналов и вместе
class SpectrPoint
{
  private:
	double*	Q;   //Искомые параметры
	double*	V;
	double* Max;   //получаем из спектра
	double* TMax;
	double* Min;
	double* TMin;

	int ch, count;

  public:
	SpectrPoint (int);
	void to_zero(); //экстремумы в ноль

	void setQ(double* )	; // установка значений
	void setV(double* )	;

	double* getQ(); // получение значений
	double* getV();
	void extrSpectr( DataPoint);//сравниваем, ищем экстремумы
	void calcSpectr(); // расчет скоростей и ампитуд

	std::string getStr();
	void setStr(std::string);

protected:


};
//---------------------------------------------------------------------------
#endif
