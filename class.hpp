#include <iostream>
#include <limits>
#include <time.h>

namespace datetime {
    int64_t constexpr operator "" sec(uint64_t sec) { if(sec>std::numeric_limits<int64_t>::max()) throw std::invalid_argument("Compile error. Too big numeric constant"); return sec; }
    int64_t constexpr operator "" min(uint64_t sec) { uint64_t d = sec*60; if(d>std::numeric_limits<int64_t>::max()) throw std::invalid_argument("Compile error. Too big numeric constant"); return d; }
    int64_t constexpr operator "" hour(uint64_t sec) { uint64_t d = sec*3600; if(d>std::numeric_limits<int64_t>::max()) throw std::invalid_argument("Compile error. Too big numeric constant"); return d; }
    int64_t constexpr operator "" day(uint64_t sec) { uint64_t d = sec*24*3600; if(d>std::numeric_limits<int64_t>::max()) throw std::invalid_argument("Compile error. Too big numeric constant"); return d; }
    enum class Month { Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };
    enum class Weekday { Sun=1, Mon, Tue, Wed, Thu, Fri, Sat };
    class Date {
        private:
            int32_t year, day, hour, min, sec;
            Month month;
            Weekday weekday;
            tm *time;
            void reflect(const Date& date);
        public:
            Date(const Date &date);
            Date(); /// creates a current day with a current time
            ~Date();
            Date(int32_t year, Month m, uint32_t day, uint32_t seconds); /// creates a date at a time given in seconds
            Date(int32_t year, Month m, uint32_t day); /// creates a day with 0h 0m 0s
            Date addYears(int32_t years);
            Date addMonths(int32_t months);
            Date addTime(int32_t seconds);
            std::string toString();
    };
}
