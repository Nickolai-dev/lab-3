#include "class.hpp"
#include <malloc.h>
#include <string.h>

using namespace std;
using namespace datetime;

Date::Date() {
    time_t seconds = ::time(NULL);
    tm *t = gmtime(&seconds);
    year = 1900+t->tm_year;
    month = static_cast<Month>(1+t->tm_mon);
    day = t->tm_mday + 1;
    weekday = static_cast<Weekday>(1+t->tm_wday);
    hour = t->tm_hour;
    min = t->tm_min + (t->tm_sec==60?1:0);
    this->sec = (t->tm_sec < 60 ? t->tm_sec : 0);
    time = t;
}

Date::Date(int32_t year, Month m, uint32_t day) {
    this->year = year;
    this->month = m;
    this->day = day;
    this->weekday = Weekday::Sun;
    hour = min = sec = 0;
}

Date::Date(int32_t year, Month m, uint32_t day, uint32_t seconds) {
    sec = seconds%1min;
    min = seconds/1min;
    hour = seconds/1hour + min/60;
    min%=1hour;
    this->day = day + hour/24;
    hour%=24;
    int n = static_cast<typename std::underlying_type<Month>::type>(m);
    int c = 0;
    switch(m){ case Month::Jan: c = 31; break;
               case Month::Feb: c = 28; if( (!(year%4) && !!(year%100) ) ||!(year%400))c = 29; break;
               case Month::Mar: c = 31; break;
               case Month::Apr: c = 30; break;
               case Month::May: c = 31; break;
               case Month::Jun: c = 30; break;
               case Month::Jul: c = 31; break;
               case Month::Aug: c = 31; break;
               case Month::Sep: c = 30; break;
               case Month::Oct: c = 31; break;
               case Month::Nov: c = 30; break;
               case Month::Dec: c = 31; break; }
    n+=(this->day-1)/c;
    this->year = year + (n-1)/12;
    if (year < -1 || year > 9999) throw std::runtime_error("Year is out of range!");
    this->month = static_cast<Month>((n-1)%12+1);
}

Date::~Date() {
    if(time) free(time);
}

std::string Date::toString() {
    //char *msg = ::asctime(time); // do not free it!
    //string str(msg);
    //str[str.length()-1]=' ';
    //return str+"(UTC)\n";
    char msg[80] = {0};
    sprintf(msg, "%d %s%d %s%d, %s%dh %s%dm %s%ds",
            year, (static_cast<int>(month)<10?"0":""), static_cast<int>(month),
            (day<10?"0":""), day,
            hour<10?"0":"", hour,
            min<10?"0":"", min,
            sec<10?"0":"", sec );
    return string(msg);
}

Date::Date(const Date &date) {
    year = date.year;
    month = date.month;
    day = date.day;
    hour = date.hour;
    min = date.min;
    sec = date.sec;
    weekday = date.weekday;
    time = (tm*)malloc(sizeof(tm));
    memcpy(time, date.time, sizeof(tm));
}

Date Date::addYears(int32_t years) {
    Date d = *this;
    d.year+=years;
    if (d.year < -1 || d.year > 9999) throw std::runtime_error("Year is out of range!");
    reflect(d);
    return d;
}

Date Date::addMonths(int32_t months) {
    Date d = *this;
    int32_t m = static_cast<typename std::underlying_type<Month>::type>(d.month)+months;
    d.year+=(m-1)/12;
    if (d.year < -1 || d.year > 9999) throw std::runtime_error("Year is out of range!");
    d.month = static_cast<Month>((m-1)%12+1);
    reflect(d);
    return d;
}

Date Date::addTime(int32_t seconds) {
    Date d = *this;
    seconds+=d.sec;
    d.sec = seconds%60;
    d.min+= seconds/1min;
    d.hour+=d.min/60;
    d.min%=60;
    d.day+= d.hour/24;
    d.hour%=24;
    //int n = ;
    int c = 0, n;
    for(int i=0;i<2;i++){//hotfix
    switch(d.month){ case Month::Jan: c = 31; break;
               case Month::Feb: c = 28; if( (!(d.year%4) && !!(d.year%100) ) ||!(d.year%400))c = 29; break;
               case Month::Mar: c = 31; break;
               case Month::Apr: c = 30; break;
               case Month::May: c = 31; break;
               case Month::Jun: c = 30; break;
               case Month::Jul: c = 31; break;
               case Month::Aug: c = 31; break;
               case Month::Sep: c = 30; break;
               case Month::Oct: c = 31; break;
               case Month::Nov: c = 30; break;
               case Month::Dec: c = 31; break; }
    n =static_cast<typename std::underlying_type<Month>::type>(d.month)+(d.day-1)/c;
    n-=1;//hotfix
    d.month = static_cast<Month>((n-1)%12+1);}
    d.year+=(n-1)/12;
    if (d.year < -1 || d.year > 9999) throw std::runtime_error("Year is out of range!");
    // hotfix
    int fix=d.day/c;
    d.month = static_cast<Month>(static_cast<int>(d.month)+fix);
    d.day%=c;

    fix=static_cast<int>(d.month)/12;
    d.year+=fix;
    d.month=static_cast<Month>(static_cast<int>(d.month)%12==0?12:static_cast<int>(d.month)%12);
    // \hotfix
    reflect(d);
    return d;
}

inline void Date::reflect(const Date& date) {
    date.time->tm_year = date.year-1900;
    date.time->tm_mon = static_cast<typename std::underlying_type<Month>::type>(date.month)-1;
    date.time->tm_mday = date.day-1;
    date.time->tm_wday = static_cast<typename std::underlying_type<Month>::type>(date.weekday)-1;
    date.time->tm_hour = date.hour;
    date.time->tm_min = date.min;
    date.time->tm_sec = date.sec;
}
