#include "class.hpp"

using namespace std;

int main() {
    using namespace datetime;
    Date date;
    Date d = date.addYears(0).addMonths(0).addTime(5day+8hour+2min+4sec);
    cout << date.toString() << endl;
    cout << d.toString() << endl;
    //cout << date.day << " " << date.hour << "h " << date.min << "min " << date.sec << "sec " << endl;
    //cout << d.day << " " << d.hour << "h " << d.min << "min " << d.sec << "sec " << endl;
    //cout << d.toString() << endl;
    return 0;
}
