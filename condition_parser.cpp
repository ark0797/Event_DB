#include "condition_parser.h"
#include "token.h"
#include "node.h"

#include <map>
using namespace std;

template <class It> 
shared_ptr<Node> ParseComparison(It& current, It end) { 
  if (current == end) {  // обработка исключительной ситуации 
    throw logic_error("Expected column name: date or event");
  }

  Token& column = *current;
  if (column.type != TokenType::COLUMN) { // если после '(' не идет слово date/event, то выбрасываем исключение 
    throw logic_error("Expected column name: date or event");
  }
  ++current;
  // после типа токена COLUMN ожидается логический оператор 

  if (current == end) { // выброс исключения 
    throw logic_error("Expected comparison operation");
  }

  Token& op = *current; // разыменовывание 
  if (op.type != TokenType::COMPARE_OP) {
    throw logic_error("Expected comparison operation");
  }
  ++current;

  if (current == end) { // выброс исключения 
    throw logic_error("Expected right value of comparison");
  }

  Comparison cmp;                 // в эту переменную записывается значение операции сравнения 
  if (op.value == "<") {
    cmp = Comparison::Less;
  } else if (op.value == "<=") {
    cmp = Comparison::LessOrEqual;
  } else if (op.value == ">") {
    cmp = Comparison::Greater;
  } else if (op.value == ">=") {
    cmp = Comparison::GreaterOrEqual;
  } else if (op.value == "==") {
    cmp = Comparison::Equal;
  } else if (op.value == "!=") {
    cmp = Comparison::NotEqual;
  } else {
    throw logic_error("Unknown comparison token: " + op.value);
  }

  const string& value = current->value; // теперь смотрим значение этого токена 
  ++current;

  if (column.value == "date") { // 
    istringstream is(value);
    return make_shared<DateComparisonNode>(cmp, ParseDate(is)); // сравнение дат 
  } 

  else {
    return make_shared<EventComparisonNode>(cmp, value); 
  }
}



template <class It> // в эту ф  передаются итераторы начала и конца вектора из токенов 
shared_ptr<Node> ParseExpression(It& current, It end, unsigned precedence) { // precedence - старшинство, приоритет, первоочерёдность  
  if (current == end) { // вектор этих токенов является пустым 
    return shared_ptr<Node>();
  }

  shared_ptr<Node> left; // обозвали left, то что будем возвращать из ф
  
  // сначала проходим все открывающиеся скобки
  if (current->type == TokenType::PAREN_LEFT) { // если указатель токена указывает на его тип и он равен (
    ++current; // поглотили '(' -- то есть увеличили итератор на 1  (переход к следующему токену, то есть к следующей информационной единице в записи исходной строки)

    left = ParseExpression(current, end, 0u); // эта ф является рекурсивной -- здесь мы ее снова вызываем 
    if (current == end || current->type != TokenType::PAREN_RIGHT) {
      throw logic_error("Missing right paren");
    }
    ++current; // consume ')'
  } 
  else { // если скобок нет, то сразу переход к анализу сравнения
    left = ParseComparison(current, end); // здесь вызывается ф очередного распарсивания 
  }

  const map<LogicalOperation, unsigned> precedences = {
      {LogicalOperation::Or, 1}, {LogicalOperation::And, 2}
  };

  while (current != end && current->type != TokenType::PAREN_RIGHT) {
    if (current->type != TokenType::LOGICAL_OP) {
      throw logic_error("Expected logic operation");
    }

    const auto logical_operation = current->value == "AND" ? LogicalOperation::And
                                                           : LogicalOperation::Or;
    const auto current_precedence = precedences.at(logical_operation);
    if (current_precedence <= precedence) {
      break;
    }

    ++current; // consume op

    left = make_shared<LogicalOperationNode>(
        logical_operation, left, ParseExpression(current, end, current_precedence)
    );
  }

  return left;
}


// здесь идет распарсинг условия для команд Find and Del 
shared_ptr<Node> ParseCondition(istream& is) { 
  auto tokens = Tokenize(is); // эта функция возвращает вектор из токенов 
  auto current = tokens.begin();
  auto top_node = ParseExpression(current, tokens.end(), 0u); // теперь вызываем функцию распарсинга выражения 

  if (!top_node) {
    top_node = make_shared<EmptyNode>();
  }

  if (current != tokens.end()) {
    throw logic_error("Unexpected tokens after condition");
  }
  return top_node;
}
