/****************************************************************/
/*                  RPN Calculator Driver File                  */
/****************************************************************/
/*      TODO: Implement driver as described in the writeup      */
/****************************************************************/

#include "RPNCalculator.hpp"
#include <iostream>
#include <string>
#include <iomanip>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-") return false;
    else if(s.size() > 1 && s[0] == '-') s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++)
    {
      if(!isdigit(s[i]) && s[i] != '.') return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

RPNCalculator::RPNCalculator(){
  stackHead = nullptr;
}

RPNCalculator::~RPNCalculator(){
 while(!isEmpty()){
   pop();
 }
}

bool RPNCalculator::isEmpty(){
  return (stackHead==nullptr);
}

void RPNCalculator::push(float num){
  Operand *number = new Operand;
  number->number = num;
  number->next = stackHead;
  stackHead = number;
}

void RPNCalculator::pop(){
  if(isEmpty()){
    cout << "Stack empty, cannot pop an item." << endl;
    return;
  }
  else{
    Operand *temp = stackHead;
    stackHead = stackHead->next;
    delete temp;
  }
}

Operand* RPNCalculator::peek(){
  if(isEmpty()){
    cout << "Stack empty, cannot peek." << endl;
  }
    return stackHead;
}

bool RPNCalculator::compute(string symbol){
  if(symbol != "+" && symbol != "*" && symbol != "="){
    cout << "err: invalid operation" << endl;
    return false;
  }
  if(isEmpty()){
    cout << "err: not enough operands" << endl;
    return false;
  }
  float topVal = stackHead->number;
  pop();
  if(isEmpty()){
    cout << "err: not enough operands" << endl;
    push(topVal);
    return false;
  }
  float bottomVal = stackHead->number;
  pop();
  float newVal;
  if(symbol == "+"){
    newVal = topVal + bottomVal;
  }
  else{
    newVal = topVal * bottomVal;
  }
  push(newVal);
  return true;
}


int main()
{
  RPNCalculator calc;
  cout << "Enter the operators and operands ('+', '*') in a postfix format" << endl;
  string input = "";
  while(input != "=")
  {
    cout << "#> ";
    getline(cin,input);
    if(isNumber(input)){
      calc.push(stof(input));
    }
    else if(input != "="){
      calc.compute(input);
    }
  }
  if(calc.isEmpty()){
    cout << "No operands: Nothing to evaluate" << endl;
    return 0;
  }
  float finalVal = calc.peek()->number;
  calc.pop();
  if(!calc.isEmpty()){
    cout << "Invalid expression" << endl;
    return 0;
  }
  cout << "final value is " << setprecision(4) << finalVal << endl;
  calc.~RPNCalculator();
  return 0;
}
