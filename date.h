#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
public:
    Date(int m_day = 1, int m_month = 1, int m_year = 1);

    Date NextDay() const;
    Date PreviousDate() const;
    bool IsLeap() const;
    bool operator>(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;
    std::string toString() const;
    short WeekNumber() const;
    int GetDay() const;
    int GetMonth() const;
    int GetYear() const;
    int DayInMonth() const;
    int DayToDays(const Date& date) const;
    int Duration(const Date& date) const;
    int DaysTillYourBirthday(const Date& birthdaydate) const;

private:
    int day;
    int month;
    int year;
};

#endif // DATE_H
