#include <iostream>
#include <array>

// Day of week function requires months to start from 3.
enum Month {
    Mar = 3, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec, Jan, Feb
};

struct Date
{
    int day;
    Month month;
    int year;
};

// This doesn't handle the case of the day of the month being in a higher range
// than the following month allows, e.g. if we increment 31/08/2019 by a month
// then we get 31/09/2019 which is not a valid date.  Since we are only dealing
// with the first of every month we dont' deal with this case.
static constexpr Date incrementMonth(Date date) noexcept
{
    date.month = static_cast<Month>(static_cast<int>(date.month) + 1);
    if (date.month == Month::Jan)
        ++date.year;
    
    if (static_cast<int>(date.month) > 14)
        date.month = Month::Mar;

    return date;
}

// Day of week function requires days to start (0-based) from Saturday.
enum Day {
    Sat = 0, Sun, Mon, Tue, Wed, Thu, Fri
};

// This is an implementation of Zeller's Congruence.
static constexpr Day correspondingWeekday(const Date date) noexcept
{
    const int century = date.year / 100;   // 0-based
    const int yearOfCentury = date.year % 100;

    return static_cast<Day>((date.day + (13 * (date.month + 1)) / 5 +
        yearOfCentury + yearOfCentury / 4 + century / 4 + 5 * century) % 7);
}

static constexpr int countSundaysOnFirstOfMonth() noexcept
{
    int sundaysOnFirstOfMonth = 0;
    for (Date date = { 1, Month::Jan, 1901 }; date.year < 2001; date = incrementMonth(date))
        if (correspondingWeekday(date) == Day::Sun)
            ++sundaysOnFirstOfMonth;

    return sundaysOnFirstOfMonth;
}

int main()
{
    constexpr int sundays = countSundaysOnFirstOfMonth();
    std::cout << sundays << std::endl;

    return sundays;
}
