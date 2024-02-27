#include "rBF.h"
#include <time.h>

using namespace std;

int main() 
{
    char ch,buff[10240];
    unsigned long int n = 10000000;
	unsigned long int l,u;
	unsigned long int i,r;
	unsigned long int TP,TN;
	unsigned long int count=0;
    double fp=0.0;
    
	//////////////////////
	// ! Insertion process
	//////////////////////

    rBF rbf(n,0.001,0.0);
	FILE *f=fopen("10M_r.txt","w");
	clock_t start, end;
    start=clock();
	for(i=0;i<n;i++)
	{
		sprintf(buff,"%lu",i);
		rbf.insert(buff);
	}
	end=clock();
	double diff=(double)(end-start)/CLOCKS_PER_SEC;
	// i is now equal n - size of the 2D bitmap - 
	printf("Total insertion:%lu\n",i);
	// fprintf(f,"Total insertion:%lu\n",i);
	printf("Elapsed Time of insertion:%f\n\n", (double)(end-start)/CLOCKS_PER_SEC);
	// fprintf(f,"Elapsed Time of insertion:%f\n\n", (double)(end-start)/CLOCKS_PER_SEC);
	
	// why is this needed?
	n=i;

	///////////////////
	// ! Lookup process
	///////////////////
	printf("Lookup process of %lu\n",n);	
	// fprintf(f,"Lookup process %lu\n",n);


	///////////////////////
	// * Same set
	///////////////////////
	start=clock();
	i=0;
	fp=0.0;
	for(i=0;i<n;i++)
	{
		sprintf(buff,"%lu",i);
		rbf.lookup(buff);
	}
	end=clock();
	TN = rbf.getTN(); TP = rbf.getTP();
    fp=(TN)/(double)n;
	//fp=(double)(TP+TN+CTN)/(double)(TP+TN+CTN+FN+FP);
	diff=(double)(end-start)/CLOCKS_PER_SEC;
	
	printf("\nSame set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100,(fp));
	printf("Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	// fprintf(f,"\nSame set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100,(fp));
	// fprintf(f,"Millions insertion:%lf\n",(double)n/diff);
	// fprintf(f,"Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);

	printf("Summary:\n");
	printf("TP: %lu\tTN:  %lu\n",TP,TN);
	// fprintf(f,"Summary:\n");
	// fprintf(f,"TP: %lu\tTN:  %lu\n",TP,TN);
	
	rbf.resetStat();

	
	
	///////////////////////
	// * Mixed set
	///////////////////////
	start=clock();
	i=0;
	l=n/2;
	u=2*l+l;
	fp=0.0;
	for(i=l;i<u;i++)
	{
		sprintf(buff,"%lu",i);
		rbf.lookup(buff);
	}
	end=clock();
	TN = rbf.getTN(); TP = rbf.getTP();
    //fp=(double)(found-l)/(double)n;
	fp=(double)(TP-l)/(double)(n);
	diff=(double)(end-start)/CLOCKS_PER_SEC;
	printf("\nMixed set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100.0,fp);
	//printf("Found: %lu\tupper:%lu\tlower:%lu\n",found,u,l);
	printf("Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	// fprintf(f,"\nMixed set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100.0,fp);
	// fprintf(f,"Millions insertion:%lf\n",(double)n/diff);
    // fprintf(f,"Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);

	printf("Summary:\n");
	printf("TP: %lu\tTN:  %lu\n",TP,TN);
	// fprintf(f,"Summary:\n");
	// fprintf(f,"TP: %lu\tTN:  %lu\n",TP,TN);
	
	rbf.resetStat();


	///////////////////////
	// * Dijsoint set
	///////////////////////
	start=clock();
	i=0;l=n+1;u=1000*n;fp=0.0;
	for(i=1;i<=n;i++)
	{
		r=rand()%(u-l+1)+l;
		sprintf(buff,"%lu",r);
		rbf.lookup(buff);
	}
	end=clock();
	TN = rbf.getTN(); TP = rbf.getTP();
    //fp=(double)(found)/(double)n;
	fp=(double)(TP)/(double)(n);
	diff=(double)(end-start)/CLOCKS_PER_SEC;
	printf("\nDisjoint set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100.0,fp);
	printf("Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	// fprintf(f,"\nDisjoint set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100.0,fp);
	// fprintf(f,"Millions insertion:%lf\n",(double)n/diff);
	// fprintf(f,"Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	
	printf("Summary:\n");
	printf("TP: %lu\tTN:  %lu\n",TP,TN);
	// fprintf(f,"Summary:\n");
	// fprintf(f,"TP: %lu\tTN:  %lu\n",TP,TN);
	
	rbf.resetStat();

	///////////////////////
	// * Random set
	///////////////////////
	start=clock();
	i=0;fp=0.0;
	for(i=1;i<=n;i++)
	{
		r=rand();
		if(r<=n)
			count++;
		sprintf(buff,"%lu",r);
		rbf.lookup(buff);
	}
	end=clock();
	TN = rbf.getTN(); TP = rbf.getTP();
    //fp=(double)(found-count)/(double)n;
	fp=(double)(TP-count)/(double)(n);
	diff=(double)(end-start)/CLOCKS_PER_SEC;
	
	printf("\nRandom set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100.0,fp);
	printf("Count:%lu\n",count);
	printf("Elapsed Time of lookup:%f\n",(double)(end-start)/CLOCKS_PER_SEC);
	// fprintf(f,"\nRandom set\nAccuracy positive:%lf, False positive %lf\n",(1.0-fp)*100.0,fp);
	// fprintf(f,"Millions insertion:%lf\n",(double)n/diff);
	// fprintf(f,"Elapsed Time of lookup:%f\n",(double)(end-start)/CLOCKS_PER_SEC);

	printf("Summary:\n");
	printf("TP: %lu\tTN:  %lu\n",TP,TN);
	// fprintf(f,"Summary:\n");
	// fprintf(f,"TP: %lu\tTN:  %lu\n",TP,TN);
	
	rbf.resetStat();
    
    rbf.printStructStat();

    fclose(f);
    return 0;
}