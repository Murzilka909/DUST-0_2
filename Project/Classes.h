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
	DataPoint (int);//��� �������� ������� ������ �������� �����������
	~DataPoint ();
	void setA(double ); // ��������� ��������
	void setB(double );
	void setT(double );
	void setP(double* );
	double getA();// ��������� ��������
	double getB();
	double getT();
	void getP(double*);
  protected:

};
//---------------------------------------------------------------------------
				//����� ������� - ��������� � �������� ��������
				//�� ������� �� ������� � ������
class SpectrPoint
{
  private:
	double Q[2];   //������� ���������
	double V[3];
	double Max[2];   //�������� �� �������
	double TMax[2];
	double Min[2];
	double TMin[2];

	int ch;

  public:
	SpectrPoint (int);
	~SpectrPoint ();
	void to_zero(); //���������� � ����

	void setQ(double* )	; // ��������� ��������
	void setV(double* )	;

	void  getQ(double*); // ��������� ��������
	void getV(double*);
	void extrSpectr( DataPoint);//����������, ���� ����������
	void calcSpectr(); // ������ ��������� � �������

	std::string getStr();
	void setStr(std::string);

protected:


};
//---------------------------------------------------------------------------
#endif
