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
	DataPoint (int);//��� �������� ������� ������ �������� �����������
	//2 ��� 3 �������
	void setA(double ); // ��������� ��������
	void setB(double );
	void setT(double );
	void setP(double* );
	double getA();// ��������� ��������
	double getB();
	double getT();
	double* getP();
  protected:

};
//---------------------------------------------------------------------------
				//����� ������� - ��������� � �������� ��������
				//�� ������� �� ������� � ������
class SpectrPoint
{
  private:
	double*	Q;   //������� ���������
	double*	V;
	double* Max;   //�������� �� �������
	double* TMax;
	double* Min;
	double* TMin;

	int ch, count;

  public:
	SpectrPoint (int);
	void to_zero(); //���������� � ����

	void setQ(double* )	; // ��������� ��������
	void setV(double* )	;

	double* getQ(); // ��������� ��������
	double* getV();
	void extrSpectr( DataPoint);//����������, ���� ����������
	void calcSpectr(); // ������ ��������� � �������

	std::string getStr();
	void setStr(std::string);

protected:


};
//---------------------------------------------------------------------------
#endif
