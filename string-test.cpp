#include "string-test.h"

using namespace std;

string KEYFILE = "keys.txt";
string DISJOINTFILE = "disjoint.txt";

vector<string> activateKeysGetter() {
    return readCombinationsFromFile(KEYFILE);
}

vector<string> activateDisjointGetter() {
    return readCombinationsFromFile(DISJOINTFILE);
}

vector<string> activateKeysGenerator() {
    activateGenerator(lst_x, KEYFILE, 7);
}

vector<string> activateDisjointGenerator() {
    activateGenerator(lst_z, DISJOINTFILE, 7);
}

int main()
{
    activateKeysGenerator();
    activateDisjointGenerator();
}