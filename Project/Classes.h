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
	DataPoint (int);//при создании объекта класса задаетс€ размерность
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
	double Q[2];   //»скомые параметры
	double V[3];
	double Max[2];   //получаем из спектра
	double TMax[2];
	double Min[2];
	double TMin[2];

	double I, A;//“екущие значени€ интеграа и амплитуды
	double Integral[3];//три самых больших интеграла над базовой линией
	double Amp[3];//три самых больших амплитуды над базовой линией
	int signI[3];//соответсвующие знаки
	int signA[3];

	double BASE; //базовый уровень

	int ch;

  public:
	SpectrPoint (int);
	~SpectrPoint ();
	void to_zero(); //экстремумы в ноль

	void zeroBase(); //базу ы ноль
	void extrAandI(DataPoint);//установка амплитуды и интегралов
	void setBase( DataPoint , int ); //установка базовой линии

	bool Check(double,double,double,double,double,double,double,double,double,double);
	//проверка отклонений

	void setQ(double* )	; // установка значений
	void setV(double* )	;

	void  getQ(double*); // получение значений
	void getV(double*);

	void extrBase( DataPoint);//формирование базовой линии
	void extrSpectr( DataPoint);//сравниваем, ищем экстремумы
	void calcSpectr(); // расчет скоростей и ампитуд

	std::string getStr();
	void setStr(std::string);

protected:


};
//---------------------------------------------------------------------------
#endif
