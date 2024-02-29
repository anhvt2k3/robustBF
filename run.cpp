#include "rBF.h"
#include "string-test.h"
#include <time.h>

// ? Test type toggle
#define STRINGS

// ? Test mode toggle
#define SAME
#define MIXED
#define RANDOM
#define DISJOINT

using namespace std;

int main() 
{
	printf("         Still alive here!     \n");
    char ch,buff[10240];
#ifdef STRINGS
	const vector<string> words_3 = activateKeysGetter();
	const vector<string> words_4 = activateDisjointGetter();
	
	unsigned long int s_size = words_3.size();
	unsigned long int q_size = words_4.size();
	vector<string> q_mixed;
	vector<string> q_random; 
	// unsigned long int n = s_size;
	// BF wont be created for n = 135 | 1350
	unsigned long int n = s_size;
#else
    unsigned long int n = 10000000;
#endif
	unsigned long int l,u;
	unsigned long int i,r;
	unsigned long int TP,TN;
	unsigned long int count=0;
    double fp=0.0;

	printf("n=%lu\n",n);
    
	//////////////////////
	// ! Insertion process
	//////////////////////

    rBF rbf(n,0.01,0.0);
	FILE *f=fopen("10M_r.txt","w");
	clock_t start, end;
    start=clock();
#ifdef STRINGS
	for (i=0; i< s_size; i++)
	{
		const char* key_= (words_3[i]).c_str();
		rbf.insert(key_);
	}
#else
	for(i=0;i<n;i++)
	{
		sprintf(buff,"%lu",i);
		rbf.insert(buff);
	}
#endif

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
	// ! Same set : Q = S
	///////////////////////
	#ifdef SAME
	i=0;
	fp=0.0;
	start=clock();
#ifdef STRINGS
	for (i=0; i< s_size; i++)
	{
		const char* key_= (words_3[i]).c_str();
		rbf.lookup(key_);
	}
#else
	for(i=0;i<n;i++)
	{
		sprintf(buff,"%lu",i);
		rbf.lookup(buff);
	}
#endif
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
	#endif
	
	
	///////////////////////
	// ! Mixed set : Q1 in S, Q2 not in S; Q1 + Q2 = Q = 1.5 S
	///////////////////////
	#ifdef MIXED
	l=n/2;
	u=2*l+l; // u = 1.5*n
	fp=0.0;
	i=0;
#ifdef STRINGS
	// taking q_mixed from 0.5 S - 2.0 S
	q_mixed = getSubvector(mergeVectors(words_3, words_4),
							s_size/2, s_size*2-1);
	start=clock();
	for (i=0; i< 1.5*s_size; i++)
	{
		const char* key_= (q_mixed[i]).c_str();
		rbf.lookup(key_);
	}
#else
	start=clock();
	for(i=l;i<u;i++)
	{
		sprintf(buff,"%lu",i);
		rbf.lookup(buff);
	}
#endif
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
	#endif

	///////////////////////
	// ! Disjoint set : Q not in S, Q = S+1
	///////////////////////
	#ifdef DISJOINT
	l=n+1;u=1000*n;fp=0.0;
	i=0;
	start=clock();
#ifdef STRINGS
	for (i=0; i<< s_size; i++)
	{
		const char* key_= (words_4[i]).c_str();
		// printf("\n%s\n",key_);
		rbf.lookup(key_);
	}
#else
	for(i=1;i<=n;i++)
	{
		r=rand()%(u-l+1)+l;
		sprintf(buff,"%lu",r);
		rbf.lookup(buff);
	}
#endif
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
	#endif

	///////////////////////
	// ! Random set : random Q; Q = S+1
	///////////////////////
	#ifdef RANDOM
	i=0;fp=0.0;
#ifdef STRINGS
	start=clock();
	q_mixed = getSubvector( 
					shuffleVector( mergeVectors(words_3, words_4)),
					0, s_size);
	for (i=0; i<= s_size; i++)
	{
		const char* key_= (q_mixed[i]).c_str();
		rbf.lookup(key_);
	}
#else
	start=clock();
	for(i=1;i<=n;i++)
	{
		r=rand();
		if(r<=n)
			count++;
		sprintf(buff,"%lu",r);
		rbf.lookup(buff);
	}
#endif
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
	#endif
    
    rbf.printStructStat();

    fclose(f);
    return 0;
}