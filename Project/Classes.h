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

	double I, A;//������� �������� �������� � ���������
	double Integral[3];//��� ����� ������� ��������� ��� ������� ������
	double Amp[3];//��� ����� ������� ��������� ��� ������� ������
	int signI[3];//�������������� �����
	int signA[3];

	double BASE; //������� �������

	int ch;

  public:
	SpectrPoint (int);
	~SpectrPoint ();
	void to_zero(); //���������� � ����

	void zeroBase(); //���� � ����
	void extrAandI(DataPoint);//��������� ��������� � ����������
	void setBase( DataPoint , int ); //��������� ������� �����

	bool Check(double,double,double,double,double,double,double,double,double,double);
	//�������� ����������

	void setQ(double* )	; // ��������� ��������
	void setV(double* )	;

	void  getQ(double*); // ��������� ��������
	void getV(double*);

	void extrBase( DataPoint);//������������ ������� �����
	void extrSpectr( DataPoint);//����������, ���� ����������
	void calcSpectr(); // ������ ��������� � �������

	std::string getStr();
	void setStr(std::string);

protected:


};
//---------------------------------------------------------------------------
#endif
