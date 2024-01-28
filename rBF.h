#include "ultilities.h"
using namespace std;
class rBF {
    unsigned long int n;
    unsigned long int m;
    unsigned long int **kBF;
    unsigned long int TP=0, TN=0;
    int x;
    int y;
    double err;
    double fp;
    unsigned long int size=0;
    long int seed1,seed2,seed3,seed4,seed5;

protected:
    void setDimension()
    {
        int* a = new int;
        int* b = new int;
        setDim(a,b,m);
        x = *a;
        y = *b;
        delete a;
        delete b;
    }
    void initSeed()
    {
        seed1=7689571;
        seed2=15485863;
        seed3=98899;
        seed4=71287;
        seed5=101653;
        /*seed6=7523;
        seed7=10007;
        seed8=prime[2701];
        seed9=prime[1901];
        seed10=prime[9901];
        seed11=prime[6601];
        seed12=prime[7721];
        seed13=prime[1101];
        seed14=prime[1001];
        seed15=prime[6501];
        seed16=prime[7501];
        seed17=prime[8801];
        seed18=prime[1701];
        seed19=prime[1801];
        seed20=prime[5901];*/
    }
    unsigned long int **allocate()
    {
        int i,j,k;
        unsigned long int **a=(unsigned long int **)malloc(x*sizeof(unsigned long int *));
        if(a==NULL)
        {
            printf("Unable to allocate!\n");
            return NULL;
        }
        
        for(i=0;i<x;i++)
        {
            a[i]=(unsigned long int *)malloc(y*sizeof(unsigned long int));
            if(a[i]==NULL)
            {
                printf("Unable to allocate!\n");
                return NULL;
            }
        }
        for(i=0;i<x;i++)
            for(j=0;j<y;j++)
                a[i][j]=0;
        printf("\nAllocated and Initilized 2DBF Successfully...\n");
        return a;
    }
    void insertSmartBF(char *key)
    {
        int i;
        for(i=0;key[i]!='\0';i++);
        insert_keyBF(kBF,key,i);
    }
    void lookupSmartBF(char *key)
    {
        int i;
        for(i=0;key[i]!='\0';i++);
        if(lookup_keyBF(kBF,key,i))
        {
            TP++;
            return;
        }

        TN++;
        return;
        
    }
    void freeSmartBF()
    {
        free_keyBF(kBF);
    }

public:
    rBF(unsigned long int nn, double error=0.001, double false_positive=0.0)
    {
        n = nn;
        err = error;
        fp = false_positive;
        initSeed();
        m = memory(nn, err);
        setDimension();
        kBF = allocate();
    };
    bool insert(char *key)
    {
        try
        {
            insertSmartBF(key);
            return true;    
        }
        catch (const char* msg)
        {
            return false;
        }
    }
    bool lookup(char *key)
    {
        try
        {
            lookupSmartBF(key);
            return true;    
        }
        catch (const char* msg)
        {
            return false;
        }
    }
    void print()
    {
        printf("True Positives: %ld\n",TP);
        printf("True Negatives: %ld\n",TN);
    }
    ~rBF()
    {
        freeSmartBF();
    };
};