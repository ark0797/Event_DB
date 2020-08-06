#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <map>
//#include <cmath>
#include <vector>
#include <set>
#include <iomanip>
#include <functional>
#include "date.h"
using namespace std;

class myset : public set<string>
{
public:
    vector <string> L_events;
};

class Database { //класс БАЗА ДАННЫХ 
public:
   /* map<Date, set<string>>& GetDB() {
        return m;
    }*/

   /* void AddEvent(const Date& date, const string& event) { //Set и так не добавит, если будет повтор события 
        m[date].push_back(event);
    }
    bool DeleteEvent(const Date& date, const string& event) {
        for (auto item : m[date]) {
            if (item == event) {
                m[date].erase(event);
                cout << "Deleted successfully" << endl;
                if (m[date].size() == 0) m.erase(date);
                return true;
            }
        }
        cout << "Event not found" << endl;
        return false;
    }
    int  DeleteDate(const Date& date) {
        int R = m[date].size();
        m[date].clear();
        m.erase(date);
        cout << "Deleted " << R << " events" << endl;
        return R;
    }

    set<string> FindSet(const Date& date) const {
        for (auto item : m) {
            if (item.first == date) return item.second;
        }
        return vector<string>();
    }

    void Find(const Date& date) const {
        set<string> str = FindSet(date);
        for (auto s : str) {
            cout << s << "\n";
        }
    }

    void Find4P(const Date& date) const {
        set<string> str = FindSet(date);
        for (auto s : str) {
            cout << date << " " << s << "\n";
        }
    }

    void Print() const {
        for (auto item : m) {
            //if (item.first.GetYear() >= 0) { // выводить все года, даже отрицаетльные
                Find4P(item.first);
            //}
            //cout << endl;
        }
    }*/
	void Add(const Date& date, const string& event);
	void Print(ostream & os) const;
    int RemoveIf(function<bool(const  Date&, const string&)> f);
    vector<Notes> FindIf(function<bool(const  Date&, const string&)> f) const;
    Notes Last(const Date& date) const;

private:
    map<Date, myset> m;
};
