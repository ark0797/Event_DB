#pragma once
#include "date.h"
#include "token.h"
#include <memory>


enum class Comparison { // ������������� ����� ��������� 
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation { // ������������� ����� ���������� �������� 
    And,
    Or,
   // Xor,
};

class Node { // ������������ ����� 
public:
    virtual bool Evaluate(const Date& date, const string& value) const = 0;// ����� ���������� �������� � ���� (����� �� �����?)
};

// ���������� (������������ ����� ���� ������������ ��������������� ������, ������������ �������� ParseCondition)
class EmptyNode : public Node {
    bool Evaluate(const Date& date, const string& value) const override // ����� ���������� �������� � ����
    {
        return true;
    }
};

class LogicalOperationNode : public Node {
public:
    //LogicalOperationNode() {} // �����������  �� ���������

    LogicalOperationNode(const LogicalOperation& logical_operation,const shared_ptr<Node>& left,const shared_ptr<Node>& right); // ����������� � �����������  // ParseExpression(current, end, current_precedence)
	bool Evaluate(const Date& date, const string& value) const override;
    
    LogicalOperation LogOp;
    shared_ptr<Node> l;
    shared_ptr<Node> r;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cmp, const  Date& date); //  ����������� � �����������

    bool Evaluate(const Date& date, const string& value) const override; // ����� ���������� �������� � ���� 
    Date l_date;
    Comparison l_cmp;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const string& value); //  ����������� � �����������

    bool Evaluate(const Date& date, const string& value) const override; // ����� ���������� �������� � ���� 
    string l_event;
    Comparison l_cmp;
};