#pragma once
#include "date.h"


bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            if (lhs.GetDay() < rhs.GetDay()) return true;
            else return false;
        }
        else {
            if (lhs.GetMonth() < rhs.GetMonth()) return true;
        }
        return false;
    }
    else {
        if (lhs.GetYear() < rhs.GetYear()) return true;
    }
    return false;
}

bool operator<=(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            if (lhs.GetDay() <= rhs.GetDay()) return true;
            else return false;
        }
        else {
            if (lhs.GetMonth() <= rhs.GetMonth()) return true;
        }
        return false;
    }
    else {
        if (lhs.GetYear() <= rhs.GetYear()) return true;
    }
    return false;
}

bool operator>(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            if (lhs.GetDay() > rhs.GetDay()) return true;
            else return false;
        }
        else {
            if (lhs.GetMonth() > rhs.GetMonth()) return true;
        }
        return false;
    }
    else {
        if (lhs.GetYear() > rhs.GetYear()) return true;
    }
    return false;
}

bool operator>=(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            if (lhs.GetDay() >= rhs.GetDay()) return true;
            else return false;
        }
        else {
            if (lhs.GetMonth() >= rhs.GetMonth()) return true;
        }
        return false;
    }
    else {
        if (lhs.GetYear() >= rhs.GetYear()) return true;
    }
    return false;
}

bool operator==(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) 
        if (lhs.GetMonth() == rhs.GetMonth()) 
            if (lhs.GetDay() == rhs.GetDay()) return true;
  return false;
}

bool operator!=(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear())
        if (lhs.GetMonth() == rhs.GetMonth())
            if (lhs.GetDay() == rhs.GetDay()) return false;
    return true;
}
ostream& operator<< (ostream& stream, const Date& date) { //перешгрузка оператора вывода для даты 
    stream << setfill('0');
    stream << setw(4) << date.GetYear() << '-' << setw(2) << date.GetMonth() << '-' << setw(2) << date.GetDay();
    return stream;
}

istream& operator>> (istream& stream, Date& date) { //должен игнорироваться только дефис (число мб как +, так и -) 
    stream >> date.SetYear();
    stream.ignore(1);
    stream >> date.SetMonth();
    stream.ignore(1);
    stream >> date.SetDay();
    return stream;
}

Date ParseDate(istringstream& is)
{
	int year;
	is >> year;
	is.ignore(1);
	int m;
	is >> m;
	is.ignore(1);
	int d;
	is >> d;
	is.ignore(1);
	Date date;
	date.SetYear() = year;
	date.SetMonth() = m;
	date.SetDay() = d;

	return date;
}

Date ParseDate(istream& is)
{
    int year;
    is >> year;
    is.ignore(1);
    int m;
    is >> m;
    is.ignore(1);
    int d;
    is >> d;
    is.ignore(1);
    Date date;
    date.SetYear() = year;
    date.SetMonth() = m;
    date.SetDay() = d;

    return date;
}

ostream& operator<< (ostream& stream, const Notes& note)
{
    if (note.date.GetDay() != -1 && note.date.GetMonth() != 0 && note.date.GetYear() != 0)
        stream << note.date << ' ' << note.evnt;
    else  stream << "No entries";
    return stream;
}