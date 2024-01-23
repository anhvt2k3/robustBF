#include "ultilities.h"
using namespace std;
class rBF {
    unsigned long int n;
    unsigned long int m;
    unsigned long int **kBF;
    unsigned long int TP=0, TN=0;
    double err;
    double fp;
public:
    rBF(unsigned long int nn)
    {
        n = nn;
        err = 0.001;
        fp = 0.0;
        m = memory(nn, err);
    };

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

    ~rBF();
};