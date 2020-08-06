#pragma once
#include <iomanip>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

class Date {
public:
    Date() { //конструктор по умолчанию
        year = 1;
        month = 1;
        day = 1;
    }
    int GetYear() const {    return year; }
    int GetMonth() const {   return month;}
    int GetDay() const {     return day;  }
    int& SetYear() {       return year;   }
    int& SetMonth() {      return month;  }
    int& SetDay() {        return day;    }
private:
    int year;
    int month;
    int day;
};

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

ostream& operator<< (ostream& stream, const Date& date);
istream& operator>> (istream& stream, Date& date);

Date ParseDate(istringstream& is);
Date ParseDate(istream& is);


struct Notes
{
	Date date;
	string evnt;
};

ostream& operator<< (ostream& stream, const Notes& note);