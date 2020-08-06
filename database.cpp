#include <algorithm>
#include "database.h"

void Database::Add(const Date& date, const string& event)
{
    int k = m[date].size();
	m[date].insert(event);
    if(k+1 == m[date].size())
        m[date].L_events.push_back(event);
}

void Database::Print(ostream& os) const
{
    for (const auto& item : m) {
        for (const string& event : item.second.L_events) {
            os << item.first << " " << event << endl;
        }
    }

}

int Database::RemoveIf(function<bool(const  Date&, const string&)> f)
{
    int count = 0;  
    int lcnt = 0;
    vector<Date> erD;
    for (auto& item : m) {
        auto &x = item.first;
        set<string> &y = item.second;
        auto It = y.begin();
        lcnt = 0;
        for (It = y.begin(); It != y.end(); ++It) {
            if (f(x, *It)) {  ++lcnt;  }
        }
        if (lcnt > 0)
        {
            count += lcnt;
            if (lcnt < y.size())
            {
                vector<string> z;
                for (It = y.begin(); It != y.end(); ++It) {
                    if (!f(x, *It))
                    {
                        z.push_back(*It);
                    }
                }
                y.clear();
                y = set<string>(z.begin(), z.end());
                z.clear();
                vector<string>& l = item.second.L_events;
                for (auto It1 = l.begin(); It1 != l.end(); ++It1) {
                    if (!f(x, *It1))
                    {
                        z.push_back(*It1);
                    }
                }
                l.clear();
                l.swap(z);
            }
            else
            {
                y.clear();
                item.second.L_events.clear();
                erD.push_back(x);
            }
        }
    }
    for (auto& d : erD)
    {
        m.erase(d);
    }
    return count;
}
vector<Notes> Database::FindIf(function<bool(const  Date&, const string&)> f) const
{
    vector<Notes> ntss;
    Notes nts;
    for (auto& item : m) {
        auto& x = item.first;
        const vector<string>& y = item.second.L_events;
        auto It = y.begin();
        for (It = y.begin(); It != y.end(); ++It) {
            if (f(x, *It))
            {
                nts.date = x;
                nts.evnt = *It;
                ntss.push_back(nts);
            }
        }
    }
    return ntss;
}

Notes Database::Last(const Date& date) const
{
    Notes nts;
    auto It = m.upper_bound(date);
    if (It != m.begin())
    {
        --It;
        nts.date = It->first;
        nts.evnt = It->second.L_events.back();
    }
    else
    {
        nts.date.SetYear() = 0;
        nts.date.SetMonth() = 0;
        nts.date.SetDay() = -1;
    }
    return nts;
}