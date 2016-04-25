#include <queue>
#include <string.h>
#include "ga.h"
#define step 3
//extern vector<vector<int> >  vLadjmx;
int GAgame::ruleupdate(double dg, double dr)//���Ը��½ӿ�
{
	if(nSyncType==SYNC)      //SYNC=40
	{
		switch(nImitType)
		{
		case 30: imitmaxs();break;    //unconditional imitation
		case 31: imitrands();break;    // ���ѧϰ
		case 32: imitdyns(dg,dr);break;// replicator dynamic 
		case 33: imitgas();break;       //�Ŵ��㷨
		case 34: imitSkipLearns();break; //1��ѧϰ ��������������,û�޸�Ϊ1�� unconditionalѧϰ����
		case 35: imitMoreSkipLearns();break;//����ѧϰ unconditionalѧϰ���� 
		case 36: imitSkipLearnDyns(dg,dr);break; //����ѧϰ��replicator���� 
		default: exit(331);
		}	
	}
	else
	{
		switch(nImitType)
		{
		case 30: imitmaxas();break;
		case 31: imitrandas();break;
		case 32: imitdynas(dg);break;
		case 33: imitgaas();break;
		//case 34: imitSkipLearnas();break;
		default: exit(332);
		}	
	}
return 0;
}

int GAgame::imitrandas()// now not ga  2011 2 11
{
	//printf("Gene1 ");
	int max,i,j,k;
	double pp;

//		do
//		{i=rand()%Gsize;
//		}while (vLadjmx[i].size()==0)
		
		i=Randnode;	
		j=rand()%vLadj[i].size();   //vLadjΪ�ڽӾ��� 
		k=vLadj[i][j];

		pp=Fitness[k]-Fitness[i];   //Fitness��������Ĵ��ѧϰ���Ĳ��� 
		pp>0?max=k:max=i;
		for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
		{	
			Strategy[i][j]=Strategy[max][j];////////////////////////////??????????????????Strategy二维向量
			if (rand()%100<1) 
				Strategy[i][j]=1-Strategy[i][j];
			if(Strategy[i][j]>1)  
			{
				printf("strategy wrong at genetic algrithm  %d  %d\n",i,j);   //genetic algrithm遗传算法
				exit (65);
			}
		}
	return 0;
}

int GAgame::imitrands()
{
	int max,i,j,k;
	double pp;

	for(i=0;i<Gsize;i++)//For each NODE,we need to do SELECTION,CROSSOVER,AND MUTATION
	{
		if(vLadj[i].size()==0) 
		{   
			for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
				MidStrategy[i][j]=Strategy[i][j];////////////////////////////??????????????????
			continue;
		}
		//	if(vLadj[i].size()==0) continue;
		j=rand()%(int)vLadj[i].size();
		k=vLadj[i][j];
		pp=Fitness[k]-Fitness[i];

		pp>0?max=k:max=i;
		
		for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
		{	
			MidStrategy[i][j]=Strategy[max][j];////////////////////////////??????????????????
		}
	}//END OF for(i<Gsize)

	for(i=0;i<Gsize;i++) 
		for(j=0;j<MEMLEN;j++)
	    { 
	    	Strategy[i][j]=MidStrategy[i][j];
	//	    if (rand()%100<1) Strategy[i][j]=1-Strategy[i][j];
			if(Strategy[i][j]>1)  
			{
				printf("strategy wrong at geneticalgrithm  %d  %d\n",i,j);
				exit (66);
			}
	    }
	return 0;
}


int GAgame::imitdyns(double dg,double dr)
{
	int max,maxk,i,j,k;
	double pp,transrt,tt,maxp,minp,rr,gg,mx1,mx2,mn1,mn2;
    //ppΪ��Ƚ�2��֮��������; transrtΪ����ѧϰ�ĸ��� 
	for(i=0;i<Gsize;i++)//For each NODE,we need to do SELECTION,CROSSOVER,AND MUTATION
	{
		if(vLadj[i].size()==0) 
		{   
			for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
				MidStrategy[i][j]=Strategy[i][j];////////////////////////////??????????????????
			continue;
		}

		j=rand()%(int)vLadj[i].size();
		k=vLadj[i][j];
		pp=Fitness[k]-Fitness[i];
		max=i;
		
		if(pp>0)//��i����ڽӵ���������ߣ������ڸ��ֲ�ͬ�Ĳ����µ� transrt
		{
			(vLadj[i].size()>vLadj[k].size())?maxk=(int)vLadj[i].size():maxk=(int)vLadj[k].size();

			if(GAMETYPE!=20&&GAMETYPE!=24)//G2X2 20;EG2X2 24
				transrt=pp/((dg+1)*maxk);    //(b*maxk);
		//		transrt=pp/(dg+1);    //(b*maxk);  //before 130614
			else if(GAMETYPE==20) //not  changed 130614
			{
				maxp=(1>dg)?1:dg;
				minp=(dr<1)?dr-1:0;
				transrt=pp/((maxp-minp)*maxk);  //change 130809  before is pp/(maxp-minp)
			}		
			else  //130809  gametype 24
			{	
               	rr=(dr*10-4)*1.0/2;            //S     -2-5  14 samples
               	gg=(dg*10-2)*1.0/2;              //T   -1-6  14 samples
					
				if(rr>1) 
				{
					mx1=rr;
					mn1=1; 
				}
				else
				{
					mx1=1;
					mn1=rr; 
				}
					
				if(gg>0) 
				{
					mx2=gg;
					mn2=0;
				} 
				else
				{
					mx2=0;
					mn2=gg;
				}

				maxp=(mx1>mx2)?mx1:mx2;
				minp=(mn1<mn2)?mn1:mn2;
				transrt=pp/((maxp-minp)*maxk);
			//printf("/ntransrt%lf pp %lf  maxk %d,maxp %lf ,minp %lf,",transrt,pp,maxk,maxp,minp);
			//getchar();
			}//transrt������� 


			tt=double(rand()%100)/100;
			if(transrt>1)
			{
			printf("strategy transrt%d %d %lf %lf %lf %d %d %d\t",i,k,transrt,pp,dg+1,maxk,vLadj[i].size(),vLadj[k].size());
			getchar();
			}
			if(tt<transrt) 
			{	max=k;
				//	printf("strategy transferr transrt %lf %lf\t",transrt,tt);
			}//���������У���Ҫѧϰ���ھӵ��±�k������max�� 
		}

		for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
		{	
			MidStrategy[i][j]=Strategy[max][j];////////////////////////////??????????????????
		}
	}//END OF for(i<Gsize)
		
	for(i=0;i<Gsize;i++)//���м���ķ�ʽ���в��Ը��� 
		for(j=0;j<MEMLEN;j++)
		{
			Strategy[i][j]=MidStrategy[i][j];
// mutation=0 130609	
			if (rand()%100<1) 
				Strategy[i][j]=1-Strategy[i][j];
		}
//getchar();
   	return 0;
} 

int GAgame::imitSkipLearns(){//������������ 
  //  int sum=2*step*(step+1);
  //  int numArray[sum];//��������Ĵ�С����ѧϰ�����������ھ����ܺͣ�������Ϊ�����ĵȲ����У�d=4,a1=4 ��sum= 2n(n+1)
    
    int max,i,j,k,temp; 
	for(i=0;i<Gsize;i++)
	{
	    
       max=i;
	    for(j=0;j<(int)vLadj[i].size();j++)
        {
			temp=vLadj[i][j];
			for(k=0;k<(int)vLadj[temp].size();k++)//����i���ڽӵ���ھ���ȣ�����i���ڽӵ�� 
			{
               if (Fitness[max]<Fitness[vLadj[temp][k]])
                max=k;
            }
			if (Fitness[max]<Fitness[temp])
                max=temp;
        } 

        for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
             MidStrategy[i][j]=Strategy[max][j];////////�����������ھ��±걣�� 
    }//END OF for(i<Gsize)  


    for(i=0;i<Gsize;i++) 
	{
		for(j=0;j<MEMLEN;j++)
        {	
        	Strategy[i][j]=MidStrategy[i][j];
			
			if (rand()%100<1) 
				Strategy[i][j]=1-Strategy[i][j];
            		
            if(Strategy[i][j]>1)
            {
            	printf("strategy wrong at geneticalgrithm %d %d\n",i,j);
                exit (0);
            }
        }
//	printf("%d%d%d%d\t",Strategy[i][0],Strategy[i][1],Strategy[i][2],Strategy[i][3] );
	}
//getchar();
  //	printf(" imitmaxs over  ");
	return 0;
}

int GAgame::imitMoreSkipLearns(){//step�ڸ��ļ�define�ж��� 
    int max,i,j,k,p,temp,temp1; 
	for(i=0;i<Gsize;i++)
	{
	    max=i;
	    int count=0;
	    int sum=2*step*(step+1);
        int numArray[sum];//��������Ĵ�С����ѧϰ�����������ھ����ܺͣ�������Ϊ�����ĵȲ����У�d=4,a1=4 ��sum= 2n(n+1)
        int flag[Gsize];//�±꣬�жϸõ��Ƿ���ӣ�1Ϊ��� 
        memset(flag,0,sizeof(flag));
        memset(numArray,0,sizeof(numArray));
        flag[i]=1;//����ĵ㲻��� 
        queue<int> qu;
        for(temp=0;temp<(int)vLadj[i].size();temp++){
            qu.push(vLadj[i][temp]);
            flag[vLadj[i][temp]]=1;
            }
        while(count!=sum){
            int tempV=qu.front();
            qu.pop();
            numArray[count]=tempV;
            count++;
            if(qu.size()<sum)//����������Ԫ�ظ���û�дﵽҪ��ľͽ�����Ӳ��� 
            for(temp=0;temp<(int)vLadj[tempV].size();temp++){
              if(flag[vLadj[tempV][temp]==0]){
              qu.push(vLadj[tempV][temp]);
              flag[vLadj[i][temp]]=1;
              }
            }    
        }//���ˣ�numArray�ж�Ϊ������Ҫ��i�Ƚϵĸ����±�
         for(j=0;j<sum;j++){
             if (Fitness[max]<Fitness[numArray[j]])
             max=k;
         }//�����������ĸ�����±굽max 
         
        for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
             MidStrategy[i][j]=Strategy[max][j];////////�����������ھ��±걣�� 
    }//END OF for(i<Gsize)  


    for(i=0;i<Gsize;i++) 
	{
		for(j=0;j<MEMLEN;j++)
        {	
        	Strategy[i][j]=MidStrategy[i][j];
			
			if (rand()%100<1) 
				Strategy[i][j]=1-Strategy[i][j];
            		
            if(Strategy[i][j]>1)
            {
            	printf("strategy wrong at geneticalgrithm %d %d\n",i,j);
                exit (0);
            }
        }
//	printf("%d%d%d%d\t",Strategy[i][0],Strategy[i][1],Strategy[i][2],Strategy[i][3] );
	}
//getchar();
//	printf(" imitmaxs over  ");
	return 0;
} 

int GAgame::imitSkipLearnDyns(double dg,double dr){
    int max,maxk,i,j,k,temp; 
    double pp,transrt,tt,maxp,minp,rr,gg,mx1,mx2,mn1,mn2;
	for(i=0;i<Gsize;i++)
	{
	    if(vLadj[i].size()==0) 
		{   
			for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
				MidStrategy[i][j]=Strategy[i][j];////////////////////////////??????????????????
			continue;
		}
		
	    max=i;
	    int count=0;
	    int sum=2*step*(step+1);
        int numArray[sum];//��������Ĵ�С����ѧϰ�����������ھ����ܺͣ�������Ϊ�����ĵȲ����У�d=4,a1=4 ��sum= 2n(n+1)
        int flag[Gsize];//�±꣬�жϸõ��Ƿ���ӣ�1Ϊ��� 
        memset(flag,0,sizeof(flag));
        memset(numArray,0,sizeof(numArray));
        flag[i]=1;//����ĵ㲻��� 
        queue<int> qu;
        for(temp=0;temp<(int)vLadj[i].size();temp++){
            qu.push(vLadj[i][temp]);
            flag[vLadj[i][temp]]=1;
            }
        while(count!=sum){
            int tempV=qu.front();
            qu.pop();
            numArray[count]=tempV;
            count++;
            if(qu.size()<sum)//����������Ԫ�ظ���û�дﵽҪ��ľͽ�����Ӳ��� 
            for(temp=0;temp<(int)vLadj[tempV].size();temp++){
              if(flag[vLadj[tempV][temp]==0]){
              qu.push(vLadj[tempV][temp]);
              flag[vLadj[i][temp]]=1;
              }
            }    
        }//���ˣ�numArray�ж�Ϊ������Ҫ��i�Ƚϵĸ����±�
        
        k = numArray[rand()%sum];//���ѡȡ���±� 
        pp=Fitness[k]-Fitness[i];
		
		if(pp>0)//��i����ڽӵ���������ߣ������ڸ��ֲ�ͬ�Ĳ����µ� transrt
		{
			(vLadj[i].size()>vLadj[k].size())?maxk=(int)vLadj[i].size():maxk=(int)vLadj[k].size();

			if(GAMETYPE!=20&&GAMETYPE!=24)//G2X2 20;EG2X2 24
				transrt=pp/((dg+1)*maxk);    //(b*maxk);
		//		transrt=pp/(dg+1);    //(b*maxk);  //before 130614
			else if(GAMETYPE==20) //not  changed 130614
			{
				maxp=(1>dg)?1:dg;
				minp=(dr<1)?dr-1:0;
				transrt=pp/((maxp-minp)*maxk);  //change 130809  before is pp/(maxp-minp)
			}		
			else  //130809  gametype 24
			{	
               	rr=(dr*10-4)*1.0/2;            //S     -2-5  14 samples
               	gg=(dg*10-2)*1.0/2;              //T   -1-6  14 samples
					
				if(rr>1) 
				{
					mx1=rr;
					mn1=1; 
				}
				else
				{
					mx1=1;
					mn1=rr; 
				}
					
				if(gg>0) 
				{
					mx2=gg;
					mn2=0;
				} 
				else
				{
					mx2=0;
					mn2=gg;
				}

				maxp=(mx1>mx2)?mx1:mx2;
				minp=(mn1<mn2)?mn1:mn2;
				transrt=pp/((maxp-minp)*maxk);
			//printf("/ntransrt%lf pp %lf  maxk %d,maxp %lf ,minp %lf,",transrt,pp,maxk,maxp,minp);
			//getchar();
			}//transrt������� 


			tt=double(rand()%100)/100;
			if(transrt>1)
			{
			printf("strategy transrt%d %d %lf %lf %lf %d %d %d\t",i,k,transrt,pp,dg+1,maxk,vLadj[i].size(),vLadj[k].size());
			getchar();
			}
			if(tt<transrt) 
			{	max=k;
				//	printf("strategy transferr transrt %lf %lf\t",transrt,tt);
			}//���������У���Ҫѧϰ���ھӵ��±�k������max�� 
		} 
         
        for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
             MidStrategy[i][j]=Strategy[max][j];////////�����������ھ��±걣�� 
    }//END OF for(i<Gsize)
        
    return 0;
}

int GAgame::imitdynas(double b)
{
	int max,maxk,i,j,k;
	double pp,transrt,tt;
	
	i=Randnode;
	j=rand()%(int)vLadj[i].size();
	k=vLadj[i][j];
	pp=Fitness[k]-Fitness[i];
	max=i;
	
	if(pp>0)
	{
//		(vLadj[i].size()-vLadj[k].size())>0?maxk=(int)vLadj[i].size():maxk=(int)vLadj[k].size();
		transrt=pp/(b+1); // (b*maxk);
		tt=double(rand()%100)/100;
		if(tt<transrt) 
		{	
			max=k;
			for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
			{
				Strategy[i][j]=Strategy[max][j];////////////////////////////??????????????????
				if (rand()%100<1) 
					Strategy[i][j]=1-Strategy[i][j];	
			}
	//		printf("strategy transferr transrt %lf %lf",transrt,tt);
		}
	}

	 return 0;
}


int GAgame::imitgas()/////only for well mixed network
{
///////////////////////////////////////////////////
/*
	int max,maxk,i,j,k,tmp;
	double pp,transrt,tt,fitsum=0,jj,kk;
	for(i=0;i<Gsize;i++)
		for(j=0;j<MEMLEN;j++)
			MidStrategy[i][j]=Strategy[i][j];

	vector<int> tsort;
	vector<double> tfit;

	tsort.resize(Gsize,0);
	tfit.resize(Gsize,0);
	for(i=0;i<Gsize;i++) 
		{
			tsort[i]=i;
			fitsum=fitsum+Fitness[i];
		}

	for(i=0;i<Gsize;i++)
		for(j=i;j<Gsize;j++)
			if(Fitness[i]>Fitness[j])
			{
				tmp=tsort[i];
				tsort[i]=tsort[j];
				tsort[j]=tmp;	
			}

	tfit[0]=Fitness[tsort[0]]/fitsum;
	for(i=1;i<Gsize;i++)
		tfit[i]=tfit[i-1]+Fitness[tsort[i]]/fitsum;


	int n1,n2;
	for(i=0;i<Gsize;i++)//For each NODE,we need to do SELECTION,CROSSOVER,AND MUTATION
		{
			if(vLadj[i].size()==0)
				continue;
			
			//j=rand()%(int)vLadj[i].size();
			//k=vLadj[i][j];
			//pp=Fitness[k]-Fitness[i];
			
			jj=1.0*(rand()%10000)/10000;
			kk=1.0*(rand()%10000)/10000;
			for(j=0;j<Gsize;j++)
				if(tfit[j]>jj)
				{
					 n1=tsort[j];
					break;
				}
			for(j=0;j<Gsize;j++)
				if(tfit[j]>kk)
				{
					 n2=tsort[j];
					break;
				}

						

			
			{//cross
				if(rand()%2)
				{	for(j=0;j<MEMLEN/2;j++)
					MidStrategy[i][j]=Strategy[n1][j];
	//				for(j=MEMLEN/2;j<MEMLEN;j++)
	//				MidStrategy[i][j]=Strategy[n2][j];
				}
				else
				{//	for(j=0;j<MEMLEN/2;j++)
				//	MidStrategy[i][j]=Strategy[n2][j];
					for(j=MEMLEN/2;j<MEMLEN;j++)
					MidStrategy[i][j]=Strategy[n1][j];
				}
			}
		}//END OF for(i<Gsize)


		for(i=0;i<Gsize;i++) for(j=0;j<MEMLEN;j++)
			{ Strategy[i][j]=MidStrategy[i][j];
							  if (rand()%100<1) Strategy[i][j]=1-Strategy[i][j];
			}
	 return 0;

//////////////////////////////////////////////////
//
*/
    int max,maxk,i,j,k;
    double pp,transrt,tt;
    
    for(i=0;i<Gsize;i++)
        for(j=0;j<MEMLEN;j++)
            MidStrategy[i][j]=Strategy[i][j];

    for(i=0;i<Gsize;i++)//For each NODE,we need to do SELECTION,CROSSOVER,AND MUTATION
    {
        if(vLadj[i].size()==0)
            continue;

        j=rand()%(int)vLadj[i].size();
        k=vLadj[i][j];
        pp=Fitness[k]-Fitness[i];

        if(pp>0)
        {
            if(rand()%2)
                for(j=0;j<MEMLEN/2;j++)
                    MidStrategy[i][j]=Strategy[k][j];
            else
                for(j=MEMLEN/2;j<MEMLEN;j++)
                    MidStrategy[i][j]=Strategy[k][j];
        }
    }//END OF for(i<Gsize)

    for(i=0;i<Gsize;i++) 
        for(j=0;j<MEMLEN;j++)
        { 
            Strategy[i][j]=MidStrategy[i][j];
            if (rand()%100<1) 
            	Strategy[i][j]=1-Strategy[i][j];
        }
        
    return 0;
}

int GAgame::imitgaas()
{ 
	return 0;
}

int GAgame::imitmaxas()// now not ga  2011 2 11
{
    int i,j,k,max;
	i=Randnode; 
	max=i;
//			if(vLadj[i].size()==0) continue;
    for(j=0;j<(int)vLadj[i].size();j++)
    {
		k=vLadj[i][j];
		if (Fitness[max]<Fitness[k])
            max=k;
    }
	for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
	{
		Strategy[i][j]=Strategy[max][j];////////////////////////////??????????????????
 		if (rand()%100<1) 
 			Strategy[i][j]=1-Strategy[i][j];
	
	}

//	printf(" imitmaxs over  ");
     return 0;
}

int GAgame::imitmaxs()
{
    int i,j,k,max;
//printf("  imitmaxs  ");
	for(i=0;i<Gsize;i++)//For each NODE,we need to do SELECTION,CROSSOVER,AND MUTATION
    {
        max=i;
		if(vLadj[i].size()==0) 
		{   
			for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
				MidStrategy[i][j]=Strategy[i][j];////////////////////////////??????????????????
			continue;
		}
	//		if(vLadj[i].size()==0) continue;
        for(j=0;j<(int)vLadj[i].size();j++)
        {
			k=vLadj[i][j];
			if (Fitness[max]<Fitness[k])
                max=k;
        }
		
		for(j=0;j<MEMLEN;j++)/////////////////////////////////////////memlength///////////////
             MidStrategy[i][j]=Strategy[max][j];////////////////////////////??????????????????
    }//END OF for(i<Gsize)
//printf("\nstrategt ga \n");
    for(i=0;i<Gsize;i++) 
	{
		for(j=0;j<MEMLEN;j++)
        {	
        	Strategy[i][j]=MidStrategy[i][j];
			
			if (rand()%100<1) 
				Strategy[i][j]=1-Strategy[i][j];
            		
            if(Strategy[i][j]>1)
            {
            	printf("strategy wrong at geneticalgrithm %d %d\n",i,j);
                exit (0);
            }
        }
//	printf("%d%d%d%d\t",Strategy[i][0],Strategy[i][1],Strategy[i][2],Strategy[i][3] );
	}
//getchar();
//	printf(" imitmaxs over  ");
	return 0;
}

double GAgame::getpayoff()// ���� ���㣬ȡ����ƽ�������Ĵ�����Ⱥ�����
{
	int i;
	double payoff=0;
	
	if(Gsize>100)
	{
		for(i=0;i<Gsize;i++)
		{
			if(vLadj[i].size()>0)
				payoff=payoff+Fitness[i];
		}
		payoff=payoff/(Gsize*200*JLOOP);		
	}
	else
	{
		for(i=0;i<Gsize;i++)
		{
			if(vLadj[i].size()>0)
				payoff=payoff+Fitness[i]/vLadj[i].size();

		}
		payoff=payoff/Gsize;
	}
	return payoff;
}

int GAgame::Strtinit()//������Գ�ʼ��
{
	int i,k;
	
	for(i=0;i<Gsize;i++)
		for(k=0;k<MEMLEN;k++)////////////////////////////////////////memlength///////////////
		{
			Strategy[i][k]=(unsigned short)(rand()%2);
		//	cout<<Strategy[i][k]<<"\t";
		//	if(Strategy[i][k]>1) {printf("strategy wrong at Strategy init i %d k %d\n",i,k); exit (0);}
		}
	return 0;
}

int GAgame::Infoprint()//��ӡһЩ��Ϣ
{
	int i,j,k;
	for(i=0;i<Gsize;i++)
	{
		printf("\t node %d ",i);
		for(k=0;k<MEMLEN;k++)////////////////////////////////////////memlength///////////////
		{
			printf(" %d ",Strategy[i][k]);
		//	if(Strategy[i][k]>1) {printf("strategy wrong at Strategy init i %d k %d\n",i,k); exit (0);}
		}
	}
	printf("\n");
	for(i=0;i<Gsize;i++)
	{
		printf("\t %d  %lf ",i,Fitness[i]);
	}
/*	for(i=0;i<Gsize;i++)
	{
		printf("\n %d ",i);
		for(j=0;j<vLadj[i].size();j++)
		printf("%lf ",Pfmx[i][vLadj[i][j]]);
	}	
*/
	printf("history\n");
	for (i=0;i<Gsize;i++)
		for(j=0;j<vLadj[i].size();j++)
			printf("%d %d %d\t",i,vLadj[i][j],(GameHistory[i][vLadj[i][j]])%2);

	return 0;
}

int GAgame::Hstinit(double rt)//������ʷ��ʼ������Ҫ���м������
{
	int i,j,k,ans1,ans2;
	for(i=0;i<Gsize;i++)
		for(k=i+1;k<Gsize;k++)//Some values are meaningless
		{
			for(j=0;j<MEM;j++)////////////////////////////////////////memlength///////////////
			{
				if(rand()%100/100.00<rt)//50%�ļ��� 
					ans1=1;
				else 
					ans1=0;

				if(rand()%100/100.00<rt)
					ans2=1;
				else 
					ans2=0;

				GameHistory[i][k]=(GameHistory[i][k]<<2);    //左移两位
				GameHistory[i][k]=GameHistory[i][k]+ans1*2+ans2;

				GameHistory[k][i]=(GameHistory[k][i]<<2);
				GameHistory[k][i]=GameHistory[k][i]+ans2*2+ans1;
			}
		}
	return 0;
}

int GAgame::Fitinit()//������Ӧ��ˮƽ��ʼ��
{
	Fitness.assign(Gsize,0.0);
	Pfmx.assign(Gsize, vector<double>(Gsize,0.0));
	GameCountmx.assign(Gsize, vector<int>(Gsize,0));
	return 0;
}

GAgame::GAgame( int gamet,int imitt,int synct,int mem,const vector<vector<int> > &vTemp):vLadj(vTemp)//���캯����������ṹͨ��vTemp������
{
//	vLadj=vTemp;
	Gsize=(int)vLadj.size();
	GAMETYPE=gamet;
	nImitType=imitt;
	nSyncType=synct;
	MEM=mem;     //  printf("ga ok0");

	switch(mem)
	{
	case 0: MEMLEN=1,GLOOP=1;break;
	case 1: MEMLEN=4,GLOOP=20;break;//if(synctype==41)GLOOP=8;
	case 2: MEMLEN=16,GLOOP=40;break;//if(synctype==41)GLOOP=32;
	case 3: MEMLEN=64,GLOOP=80;break;//if(synctype==41)GLOOP=32;
	case 4: MEMLEN=256,GLOOP=100;break;//if(synctype==41)GLOOP=32;
	case 5: MEMLEN=1024,GLOOP=200;break;//if(synctype==41)GLOOP=32;
	case 6: MEMLEN=4096,GLOOP=200;break;//if(synctype==41)GLOOP=32;
	
	default:exit(24);
	}
 //      printf("ga ok");

	Strategy.resize(Gsize,vector<int>(MEMLEN));
	MidStrategy.resize(Gsize,vector<int>(MEMLEN,0));
	GameHistory.resize(Gsize,vector<unsigned>(Gsize));
	Pfmx.resize(Gsize,vector<double>(Gsize,0.0));
	Fitness.resize(Gsize,0);
 //   cout<<Strategy[1][1]<<" ";
	GameCountmx.resize(Gsize,vector<int>(Gsize,0));
	Strtinit();

	Hstinit(0.5);
}

GAgame::~GAgame()
{	
}

double GAgame::Game(double dg,double dr)//Determine the fitness of each strategy���岩��  ��ֹģʽ  
{
//	printf("  Game dg ");
	double incomeMatrix[2][2], C_Ratio;
	int m,n,i,j,node1,node2;
	int strategy1,strategy2;
	int StrategyCount[2]={0,0};

    switch(GAMETYPE)
    {
    case 20:
        //for 2x2 incomeMatrix, the subscript variable have the opposite meaning of game stratege,in game 0 means betray,1 means cooperate.
        incomeMatrix[0][0]=1;                 //R
        incomeMatrix[0][1]=dr-1;             //S -1~1
        incomeMatrix[1][0]=dg;              //T   0~2  dg gr 0-2
        incomeMatrix[1][1]=0;                //P
        break;
    case 21:   // pd game
        incomeMatrix[0][0]=1.0;                 //R             dg 0-1
        incomeMatrix[0][1]=0.0;            //S
        incomeMatrix[1][0]=dg+1.0;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 22:   // SD
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=1.0-dg;            //S
        incomeMatrix[1][0]=1.0+dg;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 23:   //SH
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=-dg;            //S
        incomeMatrix[1][0]=dg;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 24:   //great2x2              dg dr 0-1.5
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=(dr*10-4)*1.0/2;            //S     -2-5  14 samples
        incomeMatrix[1][0]=(dg*10-2)*1.0/2;              //T   -1-6  14 samples
        incomeMatrix[1][1]=0.0;                //P
        break;
	case 25: //general
		incomeMatrix[0][0]=1.0;
        incomeMatrix[0][1]=dg;            //S
        incomeMatrix[1][0]=dr;              //T
        incomeMatrix[1][1]=0.0;                //P
		break;
	 
    default: exit(29);
    }
//	Fitinit();
//	Hstinit();

    if(Gsize>100)// Ⱥ���Сһ����1000��С��100 �������� ����������߼����ٶȣ����ﲻ̫�ǵ���
	{	
		int ti;
		for( m=0;m<Gsize;m++)
			for( n=0;n<100;n++)
			{
				node1=m;
				ti=rand()%(int)vLadj[m].size();
				node2=vLadj[m][ti];

				for(i=0;i<GLOOP;i++)
				{
				//			cout <<GameHistory[node1][node2]<< "    gamehistory"<<endl;
					strategy1=Strategy[node1][GameHistory[node1][node2]%MEMLEN];//////////////memlenghth////////////////////////
					strategy2=Strategy[node2][GameHistory[node2][node1]%MEMLEN];//////////////memlenghth////////////////////////

					Pfmx[node1][node2]=Pfmx[node1][node2]+incomeMatrix[1-strategy1][1-strategy2];
					Pfmx[node2][node1]=Pfmx[node2][node1]+incomeMatrix[1-strategy2][1-strategy1];
					StrategyCount[strategy1]++;
					StrategyCount[strategy2]++;

					GameHistory[node1][node2]=(GameHistory[node1][node2]<<2);
					GameHistory[node1][node2]=GameHistory[node1][node2]+strategy1*2+strategy2;
					GameHistory[node2][node1]=(GameHistory[node2][node1]<<2);
					GameHistory[node2][node1]=GameHistory[node2][node1]+strategy2*2+strategy1;
				}
			}
		
		for(i=0;i<Gsize;i++)
		{
			Fitness[i]=0;
			for(j=0;j<Gsize;j++)
				Fitness[i]=Fitness[i]+Pfmx[i][j];
		}	
	}

	else
	{
		for(i=0;i<GLOOP;i++)
		{
			for( m=0;m<(int)vLadj.size();m++)
				for( n=0;n<(int)vLadj[m].size();n++)
				{
					node1=m;
					node2=vLadj[m][n];
	//				cout <<GameHistory[node1][node2]<< "    gamehistory"<<endl;
					strategy1=Strategy[node1][GameHistory[node1][node2]%MEMLEN];//////////////memlenghth////////////////////////
					strategy2=Strategy[node2][GameHistory[node2][node1]%MEMLEN];//////////////memlenghth////////////////////////

					Pfmx[node1][node2]=Pfmx[node1][node2]+incomeMatrix[1-strategy1][1-strategy2];
					Pfmx[node2][node1]=Pfmx[node2][node1]+incomeMatrix[1-strategy2][1-strategy1];
//					Fitness[node1]=Fitness[node1]+incomeMatrix[1-strategy1][1-strategy2];
//					Fitness[node2]=Fitness[node2]+incomeMatrix[1-strategy2][1-strategy1];
					StrategyCount[strategy1]++;
					StrategyCount[strategy2]++;

					GameHistory[node1][node2]=(GameHistory[node1][node2]<<2);
					GameHistory[node1][node2]=GameHistory[node1][node2]+strategy1*2+strategy2;
					GameHistory[node2][node1]=(GameHistory[node2][node1]<<2);
					GameHistory[node2][node1]=GameHistory[node2][node1]+strategy2*2+strategy1;
				}
		}
		
		for(i=0;i<Gsize;i++)
			for(j=0;j<vLadj[i].size();j++)
				Pfmx[i][vLadj[i][j]]/=(2*GLOOP);//previous' /2'  //conside 2 times count for one game in vladjmx
		
		for(i=0;i<Gsize;i++)
		{
			Fitness[i]=0;
			for(j=0;j<vLadj[i].size();j++)
				Fitness[i]=Fitness[i]+Pfmx[i][vLadj[i][j]];
	//		if (vLadj[i].size()>0) Fitness[i]=Fitness[i]/vLadj[i].size();   //(GLOOP*2); 130614
		}	

//	for(i=0;i<Gsize;i++)
//	if (vLadj[i].size()>0) Fitness[i]=Fitness[i]/(GLOOP*2);////conside the degree effection
	}
    
	C_Ratio=(double)StrategyCount[1]/(StrategyCount[0]+StrategyCount[1]);
//cout <<C_Ratio<<endl;
//	printf(" game dg over  ");
	return C_Ratio;
}




double GAgame::Gamemob(double dg,double dr)//Determine the fitness of each strategy�ƶ�ģʽ�µĲ���
{
//	printf("  Game dg ");
	double incomeMatrix[2][2], C_Ratio;
	int m,n,i,j,node1,node2;
	int strategy1,strategy2;
	int StrategyCount[2]={0,0};

    switch(GAMETYPE)
    {
    case 20:
        //for 2x2 incomeMatrix, the subscript variable have the opposite meaning of game stratege,in game 0 means betray,1 means cooperate.
        incomeMatrix[0][0]=1;                 //R
        incomeMatrix[0][1]=dr-1;             //S -1~1
        incomeMatrix[1][0]=dg;              //T   0~2  dg gr 0-2
        incomeMatrix[1][1]=0;                //P
        break;
    case 21:   // pd game
        incomeMatrix[0][0]=1.0;                 //R             dg 0-1
        incomeMatrix[0][1]=0.0;            //S
        incomeMatrix[1][0]=dg+1.0;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 22:   // SD
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=1.0-dg;            //S
        incomeMatrix[1][0]=1.0+dg;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 23:   //SH
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=-dg;            //S
        incomeMatrix[1][0]=dg;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 24:   //great2x2
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=(dr*10-4)*1.0/2;            //S     -2-5  14 samples
        incomeMatrix[1][0]=(dg*10-2)*1.0/2;              //T   -1-6  14 samples
        incomeMatrix[1][1]=0.0;                //P
        break;
    default: exit(25);
    }


	for( m=0;m<(int)vLadj.size();m++)
		for( n=0;n<(int)vLadj[m].size();n++)
		{
			node1=m;
			node2=vLadj[m][n];
	//		cout <<GameHistory[node1][node2]<< "    gamehistory"<<endl;
			strategy1=Strategy[node1][GameHistory[node1][node2]%MEMLEN];//////////////memlenghth////////////////////////
			strategy2=Strategy[node2][GameHistory[node2][node1]%MEMLEN];//////////////memlenghth////////////////////////

			Pfmx[node1][node2]=Pfmx[node1][node2]+incomeMatrix[1-strategy1][1-strategy2];
			Pfmx[node2][node1]=Pfmx[node2][node1]+incomeMatrix[1-strategy2][1-strategy1];
//			Fitness[node1]=Fitness[node1]+incomeMatrix[1-strategy1][1-strategy2];
//			Fitness[node2]=Fitness[node2]+incomeMatrix[1-strategy2][1-strategy1];
			GameCountmx[node1][node2]++;
			GameCountmx[node2][node1]++;
			StrategyCount[strategy1]++;
			StrategyCount[strategy2]++;

			GameHistory[node1][node2]=(GameHistory[node1][node2]<<2);
			GameHistory[node1][node2]=GameHistory[node1][node2]+strategy1*2+strategy2;
			GameHistory[node2][node1]=(GameHistory[node2][node1]<<2);
			GameHistory[node2][node1]=GameHistory[node2][node1]+strategy2*2+strategy1;
		}
			
	C_Ratio=(double)StrategyCount[1]/(StrategyCount[0]+StrategyCount[1]);
//cout <<C_Ratio<<endl;
//	printf(" game dg over  ");
	return C_Ratio;
}

int GAgame::Pfpmob() //�ƶ�ģʽ���������
{
	int i,j,k,ct;
//cout<<"\npfmx\n";
	for(i=0;i<Gsize;i++)
	{
		for(j=0;j<Gsize;j++)
		{
	//		cout<<i<<" "<<j<<" "<<Pfmx[i][j]<<" "<<GameCountmx[i][j]<<"\t";
            if(GameCountmx[i][j]==0&&Pfmx[i][j]>0)
				printf("\npf  error!!!!!!!\n");
            if(GameCountmx[i][j]>0)
                Pfmx[i][j]/=GameCountmx[i][j];
//			cout<<i<<" "<<j<<" "<<Pfmx[i][j]<<" "<<GameCountmx[i][j]<<"\t";
		}
	}

	for(k=0;k<Gsize;k++)
	{	
		Fitness[k]=0.0;
		ct=0;
		for(i=0;i<Gsize;i++)
		{
			Fitness[k]+=Pfmx[k][i];
			if(GameCountmx[k][i]>0)
				ct++;
		}
	}

	return (0);
}


int GAgame::Gameas(double dg)//�첽ģʽ�µĲ���
{
//	printf("  Game dg ");
	double incomeMatrix[2][2],C_Ratio;
	int m,n,i,j,node1,node2,ans1,ans2;
	int strategy1,strategy2;
	int StrategyCount[2]={0,0};

    switch(GAMETYPE)
    {
    case 20:
        //for 2x2 incomeMatrix, the subscript variable have the opposite meaning of game stratege,in game 0 means betray,1 means cooperate.
        incomeMatrix[0][0]=1;                 //R
        //incomeMatrix[0][1]=dr-1;             //S -1~1
        incomeMatrix[1][0]=dg;              //T   0~2  dg gr 0-2
        incomeMatrix[1][1]=0;                //P
        break;
    case 21:   // pd game
        incomeMatrix[0][0]=1.0;                 //R             dg 0-1
        incomeMatrix[0][1]=0.0;            //S
        incomeMatrix[1][0]=dg+1.0;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 22:   // SD
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=1.0-dg;            //S
        incomeMatrix[1][0]=1.0+dg;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    case 23:   //SH
        incomeMatrix[0][0]=1.0;                 //R
        incomeMatrix[0][1]=-dg;            //S
        incomeMatrix[1][0]=dg;              //T
        incomeMatrix[1][1]=0.0;                //P
        break;
    default: exit(25);
    }


//	Fitinit();
//	Hstinit();
	Randnode=rand()%Gsize;
	m=Randnode;
	node1=m;
	for( n=0;n<(int)vLadj[m].size();n++)
	{
		node2=vLadj[m][n];
		Pfmx[node1][node2]=0;
		Pfmx[node2][node1]=0;

        for(j=0;j<MEM;j++)////////////////////////////////////////memlength///////////////
        {
            ans1=rand()%2;
            ans2=rand()%2;
            GameHistory[node1][node2]=(GameHistory[node1][node2]<<2);
            GameHistory[node1][node2]=GameHistory[node1][node2]+ans1*2+ans2;

            GameHistory[node2][node1]=(GameHistory[node2][node1]<<2);
            GameHistory[node2][node1]=GameHistory[node2][node1]+ans2*2+ans1;
        }
 
	}	
	for(i=0;i<GLOOP;i++)
		for( n=0;n<(int)vLadj[m].size();n++)
		{
			node2=vLadj[m][n];
	//			cout <<GameHistory[node1][node2]<< "    gamehistory"<<endl;
			strategy1=Strategy[node1][GameHistory[node1][node2]%MEMLEN];//////////////memlenghth////////////////////////
			strategy2=Strategy[node2][GameHistory[node2][node1]%MEMLEN];//////////////memlenghth////////////////////////

			Pfmx[node1][node2]=Pfmx[node1][node2]+incomeMatrix[1-strategy1][1-strategy2];
			Pfmx[node2][node1]=Pfmx[node2][node1]+incomeMatrix[1-strategy2][1-strategy1];

//			StrategyCount[strategy1]++;
//			StrategyCount[strategy2]++;

			GameHistory[node1][node2]=(GameHistory[node1][node2]<<2);
			GameHistory[node1][node2]=GameHistory[node1][node2]+strategy1*2+strategy2;
			GameHistory[node2][node1]=(GameHistory[node2][node1]<<2);
			GameHistory[node2][node1]=GameHistory[node2][node1]+strategy2*2+strategy1;
		}

	for( n=0;n<(int)vLadj[m].size();n++)
	{
		node2=vLadj[m][n];
		Pfmx[node1][node2]/=GLOOP;
		Pfmx[node2][node1]/=GLOOP;
	}	

	for(i=0;i<Gsize;i++)
	{
		Fitness[i]=0;
		
		for(j=0;j<vLadj[i].size();j++)
			Fitness[i]=Fitness[i]+Pfmx[i][vLadj[i][j]];
		
		if (vLadj[i].size()>0) 
			Fitness[i]=Fitness[i]/vLadj[i].size();////conside the degree effection
	}	

//	C_Ratio=(double)StrategyCount[1]/(StrategyCount[0]+StrategyCount[1]);
//cout <<C_Ratio<<endl;
//	printf(" game dg over  ");
	return 0;
}

double GAgame::getCratioas()//�첽ģʽ�µĺ������ʼ���
{
	int i,j;
	int StrategyCount[2]={0,0};
	double Cratio;
	
	for (i=0;i<Gsize;i++)
		for(j=0;j<vLadj[i].size();j++)
			StrategyCount[(GameHistory[i][vLadj[i][j]])%2]++;
	
	Cratio=(double)StrategyCount[1]/(StrategyCount[0]+StrategyCount[1]);
	//printf("\ncr %lf\n",Cratio);
    return Cratio;
}
