#include "network.h"
#include "math.h"

vector<vector<int> >  vLadjmx;

NodeAdj::NodeAdj(int nettype,double movr)
{

	switch(nettype)
	{
		case 10:mixbuld();break;
		case 11:latbuld();break;	
		case MOV:movbuld(movr);break;     //MOV 12
		default: exit(110);
	}
	printf("net ok");//cout<<"network init\n"<<endl;
}

NodeAdj::~NodeAdj()
{     

}

int NodeAdj::mixbuld() //ȫ��������
{                        //void resize (size_type n); void resize (size_type n, value_type val);
	Size=1000;           //  
	vLadjmx.resize(Size);//��ʼ������
	int i,j;             //
    double tpa,tpb,tpc;
	for (i=0;i<Size;i++)
	{	vLadjmx[i].clear();       //void reserve (size_type n)
		vLadjmx[i].reserve(Size); //reserver����������vectorԤ����洢����С����capacity��ֵ ������û�и�����ڴ���г�ʼ����
	}                             //reserve �Ĳ���n���Ƽ�Ԥ�����ڴ�Ĵ�С��ʵ�ʷ���Ŀ��ܵ��ڻ�������ֵ����n����capacity��ֵ���ͻ�reallocate�ڴ�?capacity��ֵ����ڻ��ߵ���n ��

	for(i=0;i<Size;i++)
		for(j=0;j<Size;j++)
				if(j!=i)
					vLadjmx[i].push_back(j);//������β������
//printf("mmat2adj over  ");
	return 0;
}

int NodeAdj::latbuld()//����
{
	int i,j,k;
	int side=30;
	Size=side*side;
	vLadjmx.resize(Size);
	//�����񣬹�����β���������� ȥ���߽�Ӱ��
	for(i=0;i<Size;i++)
	{
		vLadjmx[i].clear();
		vLadjmx[i].reserve(4);
		vLadjmx[i].push_back((side+i-1)%side+(i/side)*side);
		vLadjmx[i].push_back((i+1)%side+(i/side)*side);
		vLadjmx[i].push_back(i%side+((side+i/side-1)%side)*side);
		vLadjmx[i].push_back(i%side+((i/side+1)%side)*side);	
	}
	
	
	return 0;
}

int NodeAdj::movbuld(double movr)//�ƶ�����
{
	Nratio=1.3;//number of nodes in a unit area�ܶ�
	Mv=movr;   //move ratio���������������������������������������������������������������������ƶ��ٶ�֮��
	Size=300;  //number of nodes
	vLadjmx.resize(Size);

	dSide=sqrt(Size/Nratio);// one side of square where the nodes put;
//	iSide=(int)dSide*10000;//
// getchar();

	MplBuld();
 //       AdjPrint();		
//	getchar();
	return 0;	
}
int NodeAdj::MplBuld()//�����ƶ�ƽ��
{       
	printf("Mpl buld ok");
	double row,column;
	int i;
//	vLmatrix.resize(SIDE,vector<int>(SIDE,-1));
	vLaxis.resize(Size, vector<double>(2,0));

	for(i=0;i<Size;i++)
	{
		{	row=dSide*(double(rand()%1000)/1000);
			column=dSide*(double(rand()%1000)/1000);
		}//while (vLmatrix[row][column]!=-1);
	//	vLmatrix[row][column]=i;
		vLaxis[i][0]=row;
		vLaxis[i][1]=column;
	}
	Mpl2adj();
	return 0;
}
int NodeAdj::Mpl2adj()//�����ڽӾ���
{
	int i,j;
    double tpa,tpb,tpc;
	for (i=0;i<Size;i++)
	{	vLadjmx[i].clear();
		vLadjmx[i].reserve(4);
	}

	for(i=0;i<Size;i++)
		for(j=i+1;j<Size;j++)
		{
			
			tpa=fabs(vLaxis[i][0]-vLaxis[j][0]);//fabs(a)=|a|�����ֵ
			tpb=fabs(vLaxis[i][1]-vLaxis[j][1]);
			if((tpa<=1||dSide-tpa<=1)&&(tpb<=1||dSide-tpb<=1))
			{
				if (dSide-tpa<=1)
					tpa=dSide-tpa;
				if (dSide-tpb<=1)
					tpb=dSide-tpb;
				tpc=sqrt(tpa*tpa+tpb*tpb);
				if(tpc<=1)
				{	
					vLadjmx[i].push_back(j);
					vLadjmx[j].push_back(i);
				}
			}
		}
//printf("mmat2adj over  ");
	return 0;
}

int NodeAdj::Mplmove() //�ƶ� 
{
	int i;
	double x,y,rr;
	for(i=0;i<Size;i++)
	{
		rr=(double(rand()%360)/360)*2*3.1415926;
		x=Mv*cos(rr); y=Mv*sin(rr);           //���Ǻ���
		vLaxis[i][0]=vLaxis[i][0]+x;
		vLaxis[i][1]=vLaxis[i][1]+y;

		if(vLaxis[i][0]<0)
			vLaxis[i][0]=vLaxis[i][0]+dSide;
		else if(vLaxis[i][0]>dSide)
			vLaxis[i][0]=vLaxis[i][0]-dSide;
		if(vLaxis[i][1]<0)
			vLaxis[i][1]=vLaxis[i][1]+dSide;
		else if(vLaxis[i][1]>dSide)
			vLaxis[i][1]=vLaxis[i][1]-dSide;
	}
	Mpl2adj();
//	AdjPrint();
	return 0;
}

int NodeAdj::AdjPrint()//��ӡ�ڽӾ���
{
	int i,j;
	for(i=0;i<vLadjmx.size();i++)
		for(j=0;j<vLadjmx[i].size();j++)
		{
			printf("%d %d    ",i,vLadjmx[i][j]);
		}
	printf("\n");
//	for(i=0;i<Size;i++)
//		{
//		printf("%d %lf %lf\t",i,vLaxis[i][0],vLaxis[i][1]);	
//	}


return 0;
}


