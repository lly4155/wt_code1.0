#include "evgame.h"
int main(int argc,char **argv)
{
	//MIX = 10
	//EG2X2 = 24
	//IGA = 33
	//SYNC = 40
	//M0 = 0, M1 = 1, M2 = 2

	{Evgame egm0(LAT,PD,ISL,SYNC,M0);}//egm1(LAT,SD,M1
	{Evgame egm0(LAT,PD,IMSL,SYNC,M0);}//2跳学习 
	{Evgame egm0(LAT,PD,ISLD,SYNC,M0);}//replicator下的2跳学习 
	{Evgame egm0(LAT,PD,IMX,SYNC,M0);}//egm1(LAT,SD,M1
//	{Evgame egm0(LAT,EG2X2,IDY,SYNC,M0);}//egm1(LAT,SD,M1
//	{Evgame egm0(MIX,EG2X2,IGA,SYNC,M3);}//egm1(LAT,SD,M1
//	{Evgame egm0(MIX,GEN,IGA,SYNC,M3);}//egm1(LAT,SD,M1
//	{Evgame egm0(MIX,SD,IGA,SYNC,M1);}//egm1(LAT,SD,M1
//	{Evgame egm0(MIX,SH,IGA,SYNC,M1);}//egm1(LAT,SD,M1

//	{Evgame egm0(MIX,SH,IMX,SYNC,M1,&argc,&argv);}//egm1(LAT,SD,M1
return 0;
}
