#include "CuckooFilter/cuckoofilter/src/cuckoofilter.h"
#include "Tests/string-test.h"

#include <assert.h>
#include <math.h>

#include <iostream>
#include <vector>

using namespace std;
using cuckoofilter::CuckooFilter;

// ? Test type toggle
#define STRINGS

// ? Test mode toggle
#define SAME
#define MIXED
#define RANDOM
#define DISJOINT

int main(int argc, char **argv) {
  // // Check non-existing items, a few false positives expected
  // size_t total_queries = 0;
  // size_t false_queries = 0;
  // for (size_t i = s_size; i < 2 * s_size; i++) {
  //   if (filter.Contain(i) == cuckoofilter::Ok) {
  //     false_queries++;
  //   }
  //   total_queries++;
  // }

char ch,buff[10240];
#ifdef STRINGS
	vector<string> words_3 = activateKeysGetter();
	vector<string> words_4 = activateDisjointGetter();
	
	unsigned long int s_size = words_3.size();
	unsigned long int q_size = words_4.size();
	vector<string> q_mixed;
	vector<string> q_random; 
	unsigned long int n = s_size;

  // Create a cuckoo filter where each item is of type size_t and
  // use 12 bits for each item:
  //    CuckooFilter<size_t, 12> filter(total_items);
  // To enable semi-sorting, define the storage of cuckoo filter to be
  // PackedTable, accepting keys of size_t type and making 13 bits
  // for each key:
  //   CuckooFilter<size_t, 13, cuckoofilter::PackedTable> filter(total_items);
cout<<"\n     Still alive here!       \n";
//   CuckooFilter<string, 8, cuckoofilter::SingleTable,cuckoofilter::HashUtil> filter(s_size);
  CuckooFilter<char*, 8> filter(s_size);
  // : For the size of each char = 8 bits
  // CuckooFilter<string, (size_t)(MAXLENGTH*8)> filter(s_size);
  
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
	clock_t start, end;
  
  start=clock();
  // Insert items to this cuckoo filter
#ifdef STRINGS
  size_t num_inserted = 0;
  for (size_t i = 0; i < s_size; i++, num_inserted++) {
		char* key_= (words_3[i]).data();
    if (filter.Add(key_) != cuckoofilter::Ok) {
      cout << "Error when inserting item " << i << endl;
      break;
    }
  }
#else
	for(i=0;i<n;i++)
	{
		sprintf(buff,"%lu",i);
		rbf.insert(buff);
	}
#endif
	end=clock();

  // Check if previously inserted items are in the filter, expected
  // true for all items
  for (size_t i = 0; i < num_inserted; i++) {
    assert(filter.Contain(words_3[i].data()) == cuckoofilter::Ok);
  }

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
  TP=0;TN=0;
	start=clock();
#ifdef STRINGS
	for (i=0; i< s_size; i++)
	{
		char* key_= (words_3[i]).data();
    if (filter.Contain(key_) == cuckoofilter::Ok) {
      TP++;
    }
    else {
      TN++;
    }
	}
#else
	for(i=0;i<n;i++)
	{
		sprintf(buff,"%lu",i);
		rbf.lookup(buff);
	}
#endif
	end=clock();

  fp=(TN)/(double)n;
	//fp=(double)(TP+TN+CTN)/(double)(TP+TN+CTN+FN+FP);
	diff=(double)(end-start)/CLOCKS_PER_SEC;
	
	printf("\nSame set\nAccuracy positive:%lf, False positive rate: %lf\n",(1.0-fp)*100,(fp));
	printf("Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	// fprintf(f,"\nSame set\nAccuracy positive:%lf, False positive rate: %lf\n",(1.0-fp)*100,(fp));
	// fprintf(f,"Millions insertion:%lf\n",(double)n/diff);
	// fprintf(f,"Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);

	printf("Summary:\n");
	printf("TP: %lu\tTN:  %lu\n",TP,TN);
	// fprintf(f,"Summary:\n");
	// fprintf(f,"TP: %lu\tTN:  %lu\n",TP,TN);

	#endif
	
	
	///////////////////////
	// ! Mixed set : Q1 in S, Q2 not in S; Q1 + Q2 = Q = 1.5 S
	///////////////////////
	#ifdef MIXED
	fp=0.0;
	i=0;
  TP=0;TN=0;
#ifdef STRINGS
	// taking q_mixed from 0.5 S - 2.0 S
	l=s_size;
	q_mixed = getSubvector(mergeVectors(words_4, words_3),
							s_size/2, s_size*2-1);
	start=clock();
	for (i=0; i< 1.5*s_size; i++)
	{
		char* key_= (q_mixed[i]).data();
    if (filter.Contain(key_) == cuckoofilter::Ok) {
      TP++;
    }
    else {
      TN++;
    }
	}
#else
	l=n/2;
	u=2*l+l; // u = 1.5*n
	start=clock();
	for(i=l;i<u;i++)
	{
		sprintf(buff,"%lu",i);
		rbf.lookup(buff);
	}
#endif
	end=clock();
    //fp=(double)(found-l)/(double)n;
	fp=(double)(TP-l)/(double)(n);
	diff=(double)(end-start)/CLOCKS_PER_SEC;
	printf("\nMixed set\nAccuracy positive:%lf, False positive rate: %lf\n",(1.0-fp)*100.0,fp);
	//printf("Found: %lu\tupper:%lu\tlower:%lu\n",found,u,l);
	printf("Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	// fprintf(f,"\nMixed set\nAccuracy positive:%lf, False positive rate: %lf\n",(1.0-fp)*100.0,fp);
	// fprintf(f,"Millions insertion:%lf\n",(double)n/diff);
    // fprintf(f,"Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);

	printf("Summary:\n");
	printf("TP: %lu\tTN:  %lu\n",TP,TN);
	// fprintf(f,"Summary:\n");
	// fprintf(f,"TP: %lu\tTN:  %lu\n",TP,TN);
	#endif

	///////////////////////
	// ! Disjoint set : Q not in S, Q = S+1
	///////////////////////
	#ifdef DISJOINT
	fp=0.0;
	i=0;
  TP=0;TN=0;
	start=clock();
#ifdef STRINGS
	for (i=0; i< s_size; i++)
	{
		char* key_= (words_4[i]).data();
		// printf("\n%s\n",key_);
    if (filter.Contain(key_) == cuckoofilter::Ok) {
      TP++;
    }
    else {
      TN++;
    }
	}
#else
	l=n+1;u=1000*n;
	for(i=1;i<=n;i++)
	{
		r=rand()%(u-l+1)+l;
		sprintf(buff,"%lu",r);
		rbf.lookup(buff);
	}
#endif
	end=clock();
    //fp=(double)(found)/(double)n;
	fp=(double)(TP)/(double)(n);
	diff=(double)(end-start)/CLOCKS_PER_SEC;
	printf("\nDisjoint set\nAccuracy positive:%lf, False positive rate: %lf\n",(1.0-fp)*100.0,fp);
	printf("Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	// fprintf(f,"\nDisjoint set\nAccuracy positive:%lf, False positive rate: %lf\n",(1.0-fp)*100.0,fp);
	// fprintf(f,"Millions insertion:%lf\n",(double)n/diff);
	// fprintf(f,"Elapsed Time of lookup:%f\n", (double)(end-start)/CLOCKS_PER_SEC);
	
	printf("Summary:\n");
	printf("TP: %lu\tTN:  %lu\n",TP,TN);
	// fprintf(f,"Summary:\n");
	// fprintf(f,"TP: %lu\tTN:  %lu\n",TP,TN);
	#endif

	///////////////////////
	// ! Random set : random Q; Q = S+1
	///////////////////////
#ifdef RANDOM
	i=0;fp=0.0;
  TP=0;TN=0;
#ifdef STRINGS
	start=clock();
	q_mixed = getSubvector( 
					shuffleVector( mergeVectors(words_3, words_4)),
					0, s_size);
	for (i=0; i<= s_size; i++)
	{
		char* key_= (q_mixed[i]).data();
		count = count + (int)isKeyChecker(key_);
		
    if (filter.Contain(key_) == cuckoofilter::Ok) {
      TP++;
    }
    else {
      TN++;
    }
	}
#else
	start=clock();
	for(i=1;i<=n;i++)
	{
		r=rand();
		if(r<=n)
			count++;
		// count = number of keys appears
		sprintf(buff,"%lu",r);
		rbf.lookup(buff);
	}
#endif
	end=clock();
    //fp=(double)(found-count)/(double)n;
	fp=(double)(TP-count)/(double)(n);
	diff=(double)(end-start)/CLOCKS_PER_SEC;
	
	printf("\nRandom set\nAccuracy positive:%lf, False positive rate: %lf\n",(1.0-fp)*100.0,fp);
	printf("Count:%lu\n",count);
	printf("Elapsed Time of lookup:%f\n",(double)(end-start)/CLOCKS_PER_SEC);
	// fprintf(f,"\nRandom set\nAccuracy positive:%lf, False positive rate: %lf\n",(1.0-fp)*100.0,fp);
	// fprintf(f,"Millions insertion:%lf\n",(double)n/diff);
	// fprintf(f,"Elapsed Time of lookup:%f\n",(double)(end-start)/CLOCKS_PER_SEC);

	printf("Summary:\n");
	printf("TP: %lu\tTN:  %lu\n",TP,TN);
	// fprintf(f,"Summary:\n");
	// fprintf(f,"TP: %lu\tTN:  %lu\n",TP,TN);
	
	#endif
  return 0;
}
