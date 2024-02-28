#include <iostream>
#include <list>
#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include <iterator>

// Function to return a subvector from index a to index b
std::vector<std::string> getSubvector(const std::vector<std::string>& originalVector, size_t a, size_t b) {
    // Check if indices are valid
    if (a >= originalVector.size() || b >= originalVector.size() || a > b) {
        std::cerr << "Invalid indices\n";
        return {};  // Return an empty vector in case of invalid indices
    }

    // Create a new vector using iterators
    return std::vector<std::string>(originalVector.begin() + a, originalVector.begin() + b + 1);
}

// Function to merge two vectors of strings
std::vector<std::string> mergeVectors(const std::vector<std::string>& vector1, const std::vector<std::string>& vector2) {
    std::vector<std::string> mergedVector;

    // Insert elements from the first vector
    mergedVector.insert(mergedVector.end(), vector1.begin(), vector1.end());

    // Insert elements from the second vector
    mergedVector.insert(mergedVector.end(), vector2.begin(), vector2.end());

    return mergedVector;
}

// Function to shuffle a vector of strings and return a new one
std::vector<std::string> shuffleVector(const std::vector<std::string>& inputVector) {
    std::vector<std::string> shuffledVector = inputVector;

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffledVector.begin(), shuffledVector.end(), g);

    return shuffledVector;
}

// const char words_1[][100] = {"Apple","Banana","Chair","Dog","Elephant","Forest","Guitar","Hammer","Ice Cream","Jellyfish","Kite","Lighthouse","Mountain","Notebook","Orange","Penguin","Quilt","Rainbow","Sunflower","Train","Umbrella","Volcano","Watermelon","Xylophone","Yo-yo","Zebra","Astronaut","Backpack","Cloud","Dolphin","Easel","Firefly","Giraffe","Hiking","Igloo","Jigsaw","Koala","Lemonade","Moonlight","Narwhal","Ostrich","Parrot","Quasar","Rollercoaster","Seahorse","Telescope","Unicorn","Volleyball","Whistle","X-ray","Yacht","Zipline","Arcade","Bubblegum","Carousel","Daffodil","Echo","Ferris Wheel","Galaxy","Honeycomb","Iceberg","Jamboree","Kaleidoscope","Lagoon","Maze","Nebula","Otter","Pajamas","Quilt","Rocket","Seashell","Tangerine","Underground","Victory","Whisk","Xerox","Yardstick","Zenith","Atlas","Bliss","Cascade","Dazzle","Eclipse","Fandango","Glitter","Harmony","Illusion","Jamboree","Krypton","Lullaby","Memento","Nimbus","Opulent","Pristine","Quicksilver","Radiant","Serendipity","Tranquil","Utopia","Wondrous"};
// const char words_2[][100] = {"Aeroplane","Balloon","Cactus","Dolphin","Espresso","Feather","Gondola","Hula Hoop","Iguana","Jazz","Kaleidoscope","Lighthouse","Meteor","Nutmeg","Oregano","Puddle","Quasar","Rendezvous","Snorkel","Trampoline","Underwater","Velvet","Waffle","Xylograph","Yeti","Zenith","Albatross","Bonsai","Crumpet","Drizzle","Eucalyptus","Flamenco","Guacamole","Hologram","Indigo","Jigsaw","Kiwi","Lagoon","Mango","Nimbus","Octopus","Pajamas","Quokka","Radiance","Saffron","Tofu","Utopia","Vortex","Whimsy","Xenon","Yodel","Zephyr","Anemone","Bumblebee","Chai","Dappled","Ephemeral","Fandango","Gazebo","Harmony","Ineffable","Jamboree","Kite","Luminous","Melange","Nectar","Odyssey","Prismatic","Quandary","Ripple","Spectrum","Tranquil","Ultraviolet","Verve","Whirlpool","Xanadu","Yonder","Zephyr","Amethyst","Blissful","Cascade","Dazzle","Effervescent","Fractal","Gossamer","Hallowed","Incandescent","Jovial","Kismet","Lullaby","Mirage","Nebula","Opulent","Panorama","Quicksilver","Resplendent","Serendipity","Tantalizing","Unison","Wondrouse"};

const vector<string> words_3 = {"aahing","aaliis","abacas","abacus","abamps","abased","abaser","abases","abasia","abasic","abated","abater","abates","abatic","abatis","abator","abayas","abbacy","abbess","abbeys","abbots","abbrev","abduce","abduct","abeles","abelia","abhors","abided","abider","abides","abient","abject","abjure","ablare","ablate","ablaut","ablaze","ablest","abloom","ablush","abmhos","aboard","abodes","abohms","abolla","aboral","aborts","abound","aboves","abrade","abrash","abrazo","abrins","abroad","abrupt","abseil","absent","absorb","absurd","abulia","abulic","abunas","abused","abuser","abuses","abvolt","abwatt","abying","abysms","acacia","acajou","acarid","acarus","accede","accent","accept","access","accord","accost","accras","accrue","accuse","acedia","acetal","acetic","acetin","acetum","acetyl","achees","achene","achier","aching","achira","achkan","acidic","acidly","acinar","acinic","acinus","ackees","ackeys","ackton","acmite","acoasm","acorns","acquit","acrons","across","acting","actins","action","active","actons","actors","actual","acuate","acuity","aculei","acumen","acutes","adages","adagio","adapts","addend","adders","addict","adding","addled","addles","adduce","adduct","adeems","adepts","adhere","adient"};
const vector<string> words_4 = {"babble","babied","babies","babkas","baboon","baboos","babuls","baccae","baches","backed","backer","backup","bacnes","bacons","badder","baddie","badged","badger","badges","badman","baaing","badmen","baeest","baetyl","baffed","baffle","bagels","bagful","bagged","bagger","baghla","bagman","bagmen","bagnio","baguet","bagwig","bahuts","bailed","bailee","bailer","bailey","bailie","bailor","baires","bairns","baisas","baited","baiter","baizas","baized","baizes","bajada","bakers","bakery","baking","balaos","balata","balboa","balche","balded","baldie","baldly","baleen","balers","baling","balked","balker","ballad","ballas","balled","baller","ballet","ballon","ballot","ballsy","ballup","balons","balops","balsam","balsas","baltei","baluns","bamboo","bammed","banana","bancos","bandas","banded","bander","bandit","bandog","banged","banger","bangle","banian","banias","banish","baniya","banjos","banked","banker","bankit","banned","banner","banons","banses","bantam","banted","banter","banyan","banzai","baobab","baraka","barbas","barbed","barbel","barber","barbes","barbet","barbus","barbut","barded","bardee","bardes","bardic","bardos","barege","barely","barest","barfed","barfly","barged","bargee","barges","barhop"};
