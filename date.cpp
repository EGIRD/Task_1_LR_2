#include "date.h"
#include <cmath>

Date::Date(int m_day, int m_month, int m_year) {
    if(m_month < 1 || m_month > 12 || m_day < 1 || m_year < 1) {
        day = 1;
        month = 1;
        year = 1;
    } else {
        int maxDay = DayInMonth(m_month, m_year);
        if(m_day > maxDay) {
            day = maxDay;
        } else {
            day = m_day;
        }
        month = m_month;
        year = m_year;
    }
}

int Date::GetDay() const {
    return day;
}

int Date::GetMonth() const {
    return month;
}

int Date::GetYear() const {
    return year;
}

bool Date::IsLeap() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::DayInMonth(int month, int year) const
{
    if (month == 2) {
        return IsLeap() ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

Date Date::NextDay() const
{
    int d = day, m = month, y = year;
    if (d < DayInMonth(m,y)) {
        d++;
    } else {
        d = 1;
        if (m < 12) {
            m++;
        } else {
            m = 1;
            y++;
        }
    }
    return Date(d, m, y);
}

Date Date::PreviousDate() const
{
    int d = day, m = month, y = year;
    if (d > 1) {
        d--;
    } else {
        if (m > 1) {
            m--;
        } else {
            m = 12;
            y--;
        }
        d = DayInMonth(m,y);
    }
    return Date(d, m, y);
}

short Date::WeekNumber() const
{
    int dayOfYear = day;
    for (int i = 1; i < month; ++i) {
        Date tempMonth(1, i, year);
        dayOfYear += tempMonth.DayInMonth(i,year);
    }
    return (dayOfYear - 1) / 7 + 1;
}

int Date::DayToDays(const Date& date) const {
    int days = date.day;

    for (int i = 1; i < date.month; ++i) {
        days += DayInMonth(i, date.year);
    }

    days += 365 * (date.year - 1);

    for (int y = 1; y < date.year; ++y) {
        if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
            days++;
        }
    }

    return days;
}

int Date::DaysTillYourBirthday(const Date& birthdaydate) const
{
    Date currentDate(day, month, year);
    Date nextBirthday = birthdaydate;

    if (currentDate > nextBirthday) {
        nextBirthday.year += 1;
    }

    return Duration(nextBirthday);
}

int Date::Duration(const Date& date) const
{
    int days1 = DayToDays(*this);
    int days2 = DayToDays(date);
    return abs(days2 - days1);
}

std::string Date::toString() const {
    return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
}


bool Date::operator>(const Date& other) const
{
    if (year != other.year) {
        return year > other.year;
    }
    if (month != other.month) {
        return month > other.month;
    }
    return day > other.day;
}

bool Date::operator<(const Date& other) const {
    return !(*this > other) && !(*this == other);
}

bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}

