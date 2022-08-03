#pragma once
struct CoorDinate
{
	float x;
	float y;
	float z;
};

struct F_RevolvingBody //F��ת��
{
	int Field;//����
	int Yaw;//ƫ��
	int turn;//ת��
};

struct FTPOV
{
	CoorDinate Position;//λ��
	F_RevolvingBody RevolvingBody;//��ת��
	float FovAngle;//Fov�Ƕ�
};


class Algorithm_s
{
public:
	//==========================���Ǻ�������==============================================
	double Seek_X_Angle(CoorDinate Own, CoorDinate Target);//��X�Ƕ�
	double SeekDistance(CoorDinate Own, CoorDinate Target);//�����
	double Seek_Y_Angle(double Distance, CoorDinate Own, CoorDinate Target);//��Y�Ƕ�
	double Get_Angle_deviation(double OwnAngle, double TestAngle);//ȡ�ǶȲ�

	//=========================����������==========================================
	FTPOV GetVisualAngle(CoorDinate Vector, CoorDinate VisualAngle, float FovAngle);//����ӽ� //Vector�Լ����� // VisualAngle�Լ��ӽ�//FovAngle�Լ�Fov�ӽ�
	CoorDinate MapCoordinatesToScreenCoordinates(CoorDinate LocalLocation, CoorDinate TargetLocation, float FovAngle, F_RevolvingBody RevolvingBody, CoorDinate GameWindowSize);//��ͼ���굽��Ļ����
private:
private:

};

extern Algorithm_s Algorithm;