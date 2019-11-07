#include <iostream>

namespace datetime {
    int operator "" mins(uint64_t sec) { return sec*60; }
    int operator "" hours(uint64_t sec) { return sec*3600; }
    int operator "" days(uint64_t sec) { return sec*24*3600; }
    int operator "" weeks(uint64_t sec) { return sec*7*24*3600; }
}

using namespace std;

int main()
{
    using namespace datetime;
    cout << 5days << endl;
    return 0;
}
