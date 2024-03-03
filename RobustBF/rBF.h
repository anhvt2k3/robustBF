#include "ultilities.h"

using namespace std;
class rBF {
    unsigned long int n;
    unsigned long int m;
    unsigned long int **kBF;
    unsigned long int TP,TN;
    int bits=61;
    int x;
    int y;
    double err;
    double fp;
    unsigned long int size=0;
    long int seed1,seed2,seed3,seed4,seed5;

protected:
    void free_keyBF(unsigned long int **b2)
    {
        _free_(b2);
    }
    void _free_(unsigned long int **a)
    {
        // free(a);
        // printf("\nMemory freed successfully...\n");
        
        for (int i = 0; i < x; ++i) {
            free(a[i]); // Free memory for each sub-array
        }

        free(a); // Free memory for the array of pointers
        printf("\nMemory freed successfully...\n");
    }
    void insert_keyBF(unsigned long int **b2, const char *buff, int i)
    {
        
        unsigned long int h1,h2,h3,h4,h5,h6,h7;

        h1=murmur2(buff,i,seed1);
        h2=murmur2(buff,i,seed2);
        h3=murmur2(buff,i,seed3);
        //h4=murmur2(buff,i,seed4);
        //h5=murmur2(buff,i,seed5);
        
        _set_(b2,h1);
        _set_(b2,h2);
        _set_(b2,h3);
        //_set_(b2,h4);
        //_set_(b2,h5);
        
    }
    int lookup_keyBF(unsigned long int **b2, const char *buff, int i)
    {
        unsigned long int h1,h2,h3,h4,h5,h6,h7;

        h1=murmur2(buff,i,seed1);
        h2=murmur2(buff,i,seed2);
        h3=murmur2(buff,i,seed3);
        //h4=murmur2(buff,i,seed4);
        //h5=murmur2(buff,i,seed5);	
        if(_test_(b2,h1)==1)
            if(_test_(b2,h2)==1)
                if(_test_(b2,h3)==1)
                    //if(_test_(b2,h4)==1)
                        //if(_test_(b2,h5)==1)
                            return 1;
        return 0;									
    }
    void _set_(unsigned long int **a,unsigned long int h)
    {
        int i,j,pos;
        i=h%x;
        j=h%y;
        pos=h%bits; 
        a[i][j]=a[i][j]|(1UL<<pos);
    }
    int _test_(unsigned long int **a,unsigned long int h)
    {
        int i,j,pos;
        int flag;
        i=h%x; 
        j=h%y;
        pos=h%bits;
        return ((a[i][j]&(1UL<<pos))>>pos);
    }
    void _del_(unsigned long int **a,unsigned long int h)
    {
        int i,j,pos;
        unsigned long int p;
        int flag;
        i=h%x; 
        j=h%y;
        pos=h%bits;
        p=(1UL<<pos);
        if(p==(a[i][j]&(1UL<<pos)))
            a[i][j]=a[i][j]^p;
    }
    void dim(int p, int q)
    {
        this->x=p;
        this->y=q;
    }
    void setDim(unsigned long int m)
    {
        unsigned long int k=m/(2*64); 
        int a,b,c,d,e,f;
        unsigned long int i;

        f=sqrt(k);
        i=selectPrime(f);
        //int j=(i/1.5);
        // printf("i=%d\n",i);
        a=prime[i/2+3];
        b=prime[i/2-3];
        //c=prime[i-3];
        //d=prime[i+3];
        //e=prime[i/3+3];
        //f=prime[i/3-3];
        dim(a,b);
        // simpy set a = x, y = b
        //dim1(c,d);
        //dim2(e,f);
        
        printf("2DBF dimensions: \n%d  %d\n",a,b);
        size+=(a*b)*64;
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
        printf("x=%d y=%d\n",x,y);
        // unsigned long int **a=(unsigned long int **)malloc(x*sizeof(unsigned long int *));
        unsigned long int **a=new unsigned long int *[x];
        if(a==NULL)
        {
            printf("Unable to allocate x-dim!\n");
            return NULL;
        }
        
        for(i=0;i<x;i++)
        {
            // a[i]=(unsigned long int *)malloc(y*sizeof(unsigned long int));
            a[i]=new unsigned long int[y];
            if(a[i]==NULL)
            {
                printf("Unable to allocate y-dim!\n");
                return NULL;
            }
        }
        for(i=0;i<x;i++)
            for(j=0;j<y;j++)
                a[i][j]=0;
        printf("\nAllocated and Initilized 2DBF Successfully...\n");
        return a;
    }
    void insertSmartBF(const char *key)
    {
        int i;
        for(i=0;key[i]!='\0';i++);
        insert_keyBF(kBF,key,i);
    }
    void lookupSmartBF(const char *key)
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
// ! public methods
public:
    rBF(unsigned long int nn, double error=0.001, double false_positive=0.0)
    {
        n = nn;
        err = error;
        fp = false_positive;
        initSeed();
        m = memory(nn, err);
        setDim(m);
        kBF = allocate();
        resetStat();
    };
    bool insert(const char *key)
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
    bool lookup(const char *key)
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
    unsigned long int getTP()
    {
        return TP;
    }
    unsigned long int getTN()
    {
        return TN;
    }
    void resetStat()
    {
        TP=0; TN=0;
    }
    void printStructStat()
    {
        double mb=8*1024*1024.0;
        //unsigned long int s=size;
        printf("\nRequired memory size in bits: %lu\n", size);
        printf("\nTotal memory size in MB: %lf\n", (double)(size)/mb);

        printf("\nRequired memory size in bits: %lu\n", m);
        printf("\nRequired memory size in MB: %lf\n", (double)(m)/mb);
    }
    ~rBF()
    {
        freeSmartBF();
    };
};