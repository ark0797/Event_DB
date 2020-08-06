#pragma once
#include "date.h"
#include "token.h"
#include <memory>


enum class Comparison { // перечисляемый класс сравнений 
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation { // перечисляемый класс логических операций 
    And,
    Or,
   // Xor,
};

class Node { // родительский класс 
public:
    virtual bool Evaluate(const Date& date, const string& value) const = 0;// метод вычисления значения в узле (нужен ли здесь?)
};

// наследники (представляют собой узлы абстрактного синтаксического дерева, формируемого функцией ParseCondition)
class EmptyNode : public Node {
    bool Evaluate(const Date& date, const string& value) const override // метод вычисления значения в узле
    {
        return true;
    }
};

class LogicalOperationNode : public Node {
public:
    //LogicalOperationNode() {} // конструктор  по умолчанию

    LogicalOperationNode(const LogicalOperation& logical_operation,const shared_ptr<Node>& left,const shared_ptr<Node>& right); // конструктор с параметрами  // ParseExpression(current, end, current_precedence)
	bool Evaluate(const Date& date, const string& value) const override;
    
    LogicalOperation LogOp;
    shared_ptr<Node> l;
    shared_ptr<Node> r;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cmp, const  Date& date); //  конструктор с параметрами

    bool Evaluate(const Date& date, const string& value) const override; // метод вычисления значения в узле 
    Date l_date;
    Comparison l_cmp;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const string& value); //  конструктор с параметрами

    bool Evaluate(const Date& date, const string& value) const override; // метод вычисления значения в узле 
    string l_event;
    Comparison l_cmp;
};