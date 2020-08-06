#include "token.h"

#include <stdexcept> // подключены исключени€ 
using namespace std;


// вроде разобралась с этой функцией (возвращает вектор из токенов!)

vector<Token> Tokenize(istream& cl) { // токенизируем поступающее выражение, то есть определаем, что из входной строки к какому токену относитс€ 
  vector<Token> tokens;
  // на вход в функцию подан входной поток сl
  char c;
  while (cl >> c) {   // реализуем посимвольное отделение от входного потока элементов 

    if (isdigit(c)) { // если отдел€емый символ цифра, то все основани€ полагать, что это дата! 
      string date(1, c); // создаем строку дата, ктр состоит из этого 1 символа 
      for (int i = 0; i < 3; ++i) {
        while (isdigit(cl.peek())) { // пока проверка на цифру дает true
          date += cl.get();  // к дате добавлетс€ след символ-цифра 
        }
        if (i < 2) {
          date += cl.get(); // потребл€ет дефис, так как дата разделена дефисами 
        }
      }
      tokens.push_back({date, TokenType::DATE}); // в итоге, добавл€ем наш токен со значением date (ex: 2017-12-25) и типом DATE в вектор токенов 
    } 
    
    else if (c == '"') { // если считываемый символ есть кавычки, то это пользователь вводит какое-то событие 
      string event; 
      getline(cl, event, '"'); // и в эту объ€вленную строку записываетс€ само событие (без кавычек)
      tokens.push_back({event, TokenType::EVENT});
    } 
    
    else if (c == 'd') {
      if (cl.get() == 'a' && cl.get() == 't' && cl.get() == 'e') { // поглощаем поочередно символы, ктр должны складыватьс€ в date 
        tokens.push_back({"date", TokenType::COLUMN});
      } else {
        throw logic_error("Unknown token");   // уже обработан неправильный запрос 
      }
    } 
    
    else if (c == 'e') {
      if (cl.get() == 'v' && cl.get() == 'e' && cl.get() == 'n' &&   // поглощаем поочередно символы, ктр должны складыватьс€ в event 
          cl.get() == 't') {
        tokens.push_back({"event", TokenType::COLUMN});
      } else {
        throw logic_error("Unknown token");   // уже обработан неправильный запрос 
      }
    } 
    // тут обрабатываютс€ логические операнды AND и OR
    else if (c == 'A') {
      if (cl.get() == 'N' && cl.get() == 'D') {
        tokens.push_back({"AND", TokenType::LOGICAL_OP});
      } else {
        throw logic_error("Unknown token");
      }
    } 
    
    else if (c == 'O') {
      if (cl.get() == 'R') {
        tokens.push_back({"OR", TokenType::LOGICAL_OP});
      } else {
        throw logic_error("Unknown token");
      }
    } 
    // далее 2 скобки 
    else if (c == '(') {
      tokens.push_back({"(", TokenType::PAREN_LEFT});
    } 
    
    else if (c == ')') {
      tokens.push_back({")", TokenType::PAREN_RIGHT});
    } 
    
    else if (c == '<') {
      if (cl.peek() == '=') {
        cl.get();
        tokens.push_back({"<=", TokenType::COMPARE_OP});
      } else {
        tokens.push_back({"<", TokenType::COMPARE_OP});
      }
    } 
    
    else if (c == '>') {
      if (cl.peek() == '=') {
        cl.get();
        tokens.push_back({">=", TokenType::COMPARE_OP});
      } else {
        tokens.push_back({">", TokenType::COMPARE_OP});
      }
    } 
    
    else if (c == '=') {
      if (cl.get() == '=') {
        tokens.push_back({"==", TokenType::COMPARE_OP});
      } else {
        throw logic_error("Unknown token");
      }
    } 
    
    else if (c == '!') {
      if (cl.get() == '=') {
        tokens.push_back({"!=", TokenType::COMPARE_OP});
      } else {
        throw logic_error("Unknown token");
      }
    }
  }

  return tokens;
}
