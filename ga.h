//#include "network.h"
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
//#include"globev.h"
#include "evgame.h"



class GAgame
{
	//DATA  OF GAGAME
public:

	GAgame( int gamet,int imitt,int synct,int mem, const vector<vector<int> > &vTemp);
	~GAgame();
	int Strtinit();
	int Hstinit(double rt=0.5);
	int Fitinit();
	
	double Game(double dg,double dr);//具体博弈  静止模式 
	int Gameas(double dg);//异步模式下的博弈
	double Gamemob(double dg,double dr);
	int Gameasmob(double dg);
	int Pfpmob();
	int ruleupdate(double dg,double dr);  //更新规则 
	//各类模仿规则 ,由 ruleupdate来选择调用 
	int imitdyns(double dg,double dr); 
	int imitmaxs();
	int imitrands();
	int imitgas();
	int imitdynas(double b);
	int imitmaxas();
	int imitrandas();                     //
	int imitgaas();
	int imitSkipLearns();//1跳学习 
	int imitMoreSkipLearns();//多跳学习 
	int imitSkipLearnDyns(double dg,double dr);//replicator规则下的多跳学习
  
	int imitrandomdys(double b);
	double getpayoff();
	int Infoprint();
	double getCratioas();
	
	vector<vector<unsigned> > GameHistory; //博弈历史 
	vector<vector<double> > Pfmx; //payoff 矩阵 
	vector<vector<int> > Strategy; //策略 
	vector<vector<int> > MidStrategy; //中间策略保存 
	vector<double> Fitness; //计算适应度 
	vector<vector<int> > GameCountmx;	//博弈轮数 

	 const vector<vector<int> > &vLadj; //邻接矩阵 
	int Randnode;//异步模式下才用的随机生成的点下标 
	int Gsize, GAMETYPE, MEM, MEMLEN,GLOOP,nImitType,nSyncType;//game loops in one generation
	//int ILOOP;// I loop times in main  rerun the whole sytem repeat times
	//int JLOOP;//k loop times in main ,Gene algrithm generations
private:
};

