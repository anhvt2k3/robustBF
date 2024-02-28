#include <iostream>
#include <list>
#include <algorithm>
#include <random>
#include <cstring>
#include <stdio.h>
#include <string.h>

// Function to merge two arrays of strings
char** mergeArrays(const char** arr1, int size1, const char** arr2, int size2) {
    int mergedSize = size1 + size2;
    char** mergedArray = new char*[mergedSize];

    // Copy elements from the first array
    for (int i = 0; i < size1; ++i) {
        mergedArray[i] = new char[strlen(arr1[i]) + 1];
        strcpy(mergedArray[i], arr1[i]);
    }

    // Copy elements from the second array
    for (int i = 0; i < size2; ++i) {
        mergedArray[size1 + i] = new char[strlen(arr2[i]) + 1];
        strcpy(mergedArray[size1 + i], arr2[i]);
    }

    return mergedArray;
}

// Function to print an array of strings
void printArray(const char** arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

// int main() {
//     // Sample arrays of strings
//     const char* array1[] = {"apple", "banana", "cherry"};
//     const int size1 = sizeof(array1) / sizeof(array1[0]);

//     const char* array2[] = {"orange", "grape", "kiwi"};
//     const int size2 = sizeof(array2) / sizeof(array2[0]);

//     // Merge the arrays
//     char** mergedArray = mergeArrays(array1, size1, array2, size2);

//     // Print the merged array
//     std::cout << "Merged Array:\n";
//     printArray(mergedArray, size1 + size2);

//     // Don't forget to free memory
//     for (int i = 0; i < size1 + size2; ++i) {
//         delete[] mergedArray[i];
//     }
//     delete[] mergedArray;

//     return 0;
// }


// Function to shuffle two lists of strings
std::list<std::string> mergeAndShuffle(const std::list<std::string>& list1, const std::list<std::string>& list2) {
    // Merge the two lists
    std::list<std::string> mergedList = list1;
    mergedList.insert(mergedList.end(), list2.begin(), list2.end());

    // Shuffle the merged list
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(mergedList.begin(), mergedList.end(), g);

    return mergedList;
}

// int main() {
//     // Sample lists of strings
//     std::list<std::string> list1 = {"apple", "banana", "cherry"};
//     std::list<std::string> list2 = {"orange", "grape", "kiwi"};

//     // Merge and shuffle the lists
//     std::list<std::string> mergedAndShuffled = mergeAndShuffle(list1, list2);

//     // Print the result
//     std::cout << "Merged and Shuffled List:\n";
//     for (const auto& str : mergedAndShuffled) {
//         std::cout << str << " ";
//     }
//     std::cout << "\n";

//     return 0;
// }

// const char words_1[][100] = {"Apple","Banana","Chair","Dog","Elephant","Forest","Guitar","Hammer","Ice Cream","Jellyfish","Kite","Lighthouse","Mountain","Notebook","Orange","Penguin","Quilt","Rainbow","Sunflower","Train","Umbrella","Volcano","Watermelon","Xylophone","Yo-yo","Zebra","Astronaut","Backpack","Cloud","Dolphin","Easel","Firefly","Giraffe","Hiking","Igloo","Jigsaw","Koala","Lemonade","Moonlight","Narwhal","Ostrich","Parrot","Quasar","Rollercoaster","Seahorse","Telescope","Unicorn","Volleyball","Whistle","X-ray","Yacht","Zipline","Arcade","Bubblegum","Carousel","Daffodil","Echo","Ferris Wheel","Galaxy","Honeycomb","Iceberg","Jamboree","Kaleidoscope","Lagoon","Maze","Nebula","Otter","Pajamas","Quilt","Rocket","Seashell","Tangerine","Underground","Victory","Whisk","Xerox","Yardstick","Zenith","Atlas","Bliss","Cascade","Dazzle","Eclipse","Fandango","Glitter","Harmony","Illusion","Jamboree","Krypton","Lullaby","Memento","Nimbus","Opulent","Pristine","Quicksilver","Radiant","Serendipity","Tranquil","Utopia","Wondrous"};
// const char words_2[][100] = {"Aeroplane","Balloon","Cactus","Dolphin","Espresso","Feather","Gondola","Hula Hoop","Iguana","Jazz","Kaleidoscope","Lighthouse","Meteor","Nutmeg","Oregano","Puddle","Quasar","Rendezvous","Snorkel","Trampoline","Underwater","Velvet","Waffle","Xylograph","Yeti","Zenith","Albatross","Bonsai","Crumpet","Drizzle","Eucalyptus","Flamenco","Guacamole","Hologram","Indigo","Jigsaw","Kiwi","Lagoon","Mango","Nimbus","Octopus","Pajamas","Quokka","Radiance","Saffron","Tofu","Utopia","Vortex","Whimsy","Xenon","Yodel","Zephyr","Anemone","Bumblebee","Chai","Dappled","Ephemeral","Fandango","Gazebo","Harmony","Ineffable","Jamboree","Kite","Luminous","Melange","Nectar","Odyssey","Prismatic","Quandary","Ripple","Spectrum","Tranquil","Ultraviolet","Verve","Whirlpool","Xanadu","Yonder","Zephyr","Amethyst","Blissful","Cascade","Dazzle","Effervescent","Fractal","Gossamer","Hallowed","Incandescent","Jovial","Kismet","Lullaby","Mirage","Nebula","Opulent","Panorama","Quicksilver","Resplendent","Serendipity","Tantalizing","Unison","Wondrouse"};

const char words_3[][10] = {"aahing","aaliis","abacas","abacus","abamps","abased","abaser","abases","abasia","abasic","abated","abater","abates","abatic","abatis","abator","abayas","abbacy","abbess","abbeys","abbots","abbrev","abduce","abduct","abeles","abelia","abhors","abided","abider","abides","abient","abject","abjure","ablare","ablate","ablaut","ablaze","ablest","abloom","ablush","abmhos","aboard","abodes","abohms","abolla","aboral","aborts","abound","aboves","abrade","abrash","abrazo","abrins","abroad","abrupt","abseil","absent","absorb","absurd","abulia","abulic","abunas","abused","abuser","abuses","abvolt","abwatt","abying","abysms","acacia","acajou","acarid","acarus","accede","accent","accept","access","accord","accost","accras","accrue","accuse","acedia","acetal","acetic","acetin","acetum","acetyl","achees","achene","achier","aching","achira","achkan","acidic","acidly","acinar","acinic","acinus","ackees","ackeys","ackton","acmite","acoasm","acorns","acquit","acrons","across","acting","actins","action","active","actons","actors","actual","acuate","acuity","aculei","acumen","acutes","adages","adagio","adapts","addend","adders","addict","adding","addled","addles","adduce","adduct","adeems","adepts","adhere","adient"};
const char words_4[][10] = {"babble","babied","babies","babkas","baboon","baboos","babuls","baccae","baches","backed","backer","backup","bacnes","bacons","badder","baddie","badged","badger","badges","badman","baaing","badmen","baeest","baetyl","baffed","baffle","bagels","bagful","bagged","bagger","baghla","bagman","bagmen","bagnio","baguet","bagwig","bahuts","bailed","bailee","bailer","bailey","bailie","bailor","baires","bairns","baisas","baited","baiter","baizas","baized","baizes","bajada","bakers","bakery","baking","balaos","balata","balboa","balche","balded","baldie","baldly","baleen","balers","baling","balked","balker","ballad","ballas","balled","baller","ballet","ballon","ballot","ballsy","ballup","balons","balops","balsam","balsas","baltei","baluns","bamboo","bammed","banana","bancos","bandas","banded","bander","bandit","bandog","banged","banger","bangle","banian","banias","banish","baniya","banjos","banked","banker","bankit","banned","banner","banons","banses","bantam","banted","banter","banyan","banzai","baobab","baraka","barbas","barbed","barbel","barber","barbes","barbet","barbus","barbut","barded","bardee","bardes","bardic","bardos","barege","barely","barest","barfed","barfly","barged","bargee","barges","barhop"};
