#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) {
	// Реализуйте эту функцию
	string str;
    char ch;
    while(true){
        ch = is.peek();
        if (ch != ' ' && ch != '\t')
        {
            break;
        }
        is.ignore(1);
    }
	getline(is,str);
	return str;
}

void TestAll();

int main() {
  //TestAll();

  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command; // записываем из строкового потока в строковую переменную значение команды

    if (command == "Add") {
      const auto date = ParseDate(is);   // дальше идет распарсинг даты (что нужно написать) 
      const auto event = ParseEvent(is); // здесь идет распарсинг события -- это уже написано 
      db.Add(date, event); // в базу данных добавляется дата и событие, полученные из строкового потока в результате распарсинга 
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is); // здесь идет распарсинг условия для команд Find и Del 
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      }; 
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}
/*
void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
}*/
