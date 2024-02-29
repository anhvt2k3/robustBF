#include "string-test.h"

using namespace std;

void activateKeysGenerator() {
    activateGenerator(lst_x, KEYFILE, MAXLENGTH);
}

void activateDisjointGenerator() {
    activateGenerator(lst_z, DISJOINTFILE, MAXLENGTH);
}

int main()
{
    activateKeysGenerator();
    activateDisjointGenerator();
}