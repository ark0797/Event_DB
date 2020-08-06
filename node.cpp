#include "node.h"



LogicalOperationNode::LogicalOperationNode(const  LogicalOperation& logical_operation, const shared_ptr<Node>& left, const shared_ptr<Node>& right)
{
	LogOp	= logical_operation;
	l = left;
	r = right;
}

bool DateComparisonNode::Evaluate(const Date& date, const string& value) const
{
	bool ch;
	switch (l_cmp)
	{
	case Comparison::Less:
		ch = date < l_date;
		break;
	case Comparison::LessOrEqual:
		ch = date <= l_date;
		break;
	case Comparison::Greater:
		ch = date > l_date;
		break;
	case Comparison::GreaterOrEqual:
		ch = date >= l_date;
		break;
	case Comparison::Equal:
		ch = date == l_date;
		break;
	case Comparison::NotEqual:
		ch = date != l_date;
		break;
	default: // до этого места доходить не должно
		ch = 0;
		break;
	}
	return ch;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const  Date& date) //  конструктор с параметрами
{
	l_date = date;
	l_cmp  = cmp;
}

bool EventComparisonNode::Evaluate(const Date& date, const string& value) const
{
	bool ch;
	switch ( l_cmp)
	{
	case Comparison::Less:
		ch = value < l_event;
		break;
	case Comparison::LessOrEqual:
		ch = value <= l_event;
		break;
	case Comparison::Greater:
		ch = value > l_event;
		break;
	case Comparison::GreaterOrEqual:
		ch = value >= l_event;
		break;
	case Comparison::Equal:
		ch = value == l_event;
		break;
	case Comparison::NotEqual:
		ch = value != l_event;
		break;
	default: // до этого места доходить не должно
		ch = 0;
		break;
	}
	return ch;
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& value) //  конструктор с параметрами
{
	l_event = value;
	l_cmp = cmp;
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& value) const
{
	bool chl, chr,ch;
	chl = l->Evaluate(date, value);
	chr = r->Evaluate(date, value);
	switch (LogOp)
	{
	case  LogicalOperation::And:
		ch = chl && chr;
		break;
	case  LogicalOperation::Or:
		ch = chl || chr;
		break;
	/*case LogicalOperation::Xor:
		ch = ;
		break;*/
	default:
		ch = 0;
		break;
	}/**/
	//ch = (LogOp == LogicalOperation::And) ? chl && chr : chl || chr;
	return ch;
}