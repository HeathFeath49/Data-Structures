#include <iostream>
#include <vector>
#include <cctype>
#include <stack>
//#include <stdlib.h>
#include <sstream>
using namespace std;

//struct for lisp data
struct DataObj {
  stack<int> nums;
  stack<char> operators;
  int openParenth=0;
  int closeParenth=0;
};

//function to handle calculations
//TESTED::PASSED
int calculate(char op,int numL,int numR){
  if(op == '+'){
    return numL + numR;
  }
  else if(op == '-'){
    return numL-numR;
  }
  else if(op == '*'){
    return numL * numR;
  }
  else if(op == '/'){
    //doesn't return doubles
    return numL / numR;
  }
};

int runCalc(DataObj * d){
  char op = d->operators.top();
  int numR = d->nums.top();
  d->nums.pop();
  int numL = d->nums.top();
  d->nums.pop();
  
  return calculate(op,numL,numR);
}

bool isOperator(char c){
  vector<char> validOperators = {'+','-','*','/'};
  for(int i=0;i<validOperators.size();i++){
    if(c == validOperators[i]){
      return true;
    }
  }
  return false;
};

int processExpression(DataObj * data,string expr){
  string onGoNum = "";
  int numForOperator = 0;
  int i = 0;
  while(i<expr.length()){
    char c = expr[i];
    if(isdigit(c)){
      //get entire num
      onGoNum += c;
      bool numNotFinished = true;
      while(numNotFinished){
        c=expr[i+1];
        if(isdigit(c)){
          onGoNum+=c;
          i++;
        }
        else{
          numNotFinished = false;
        }
      }
      int n;
      stringstream(onGoNum)>>n;
      data->nums.push(n);
      onGoNum = ' ';
      numForOperator++;
    }
    else if(isOperator(c)){
      data->operators.push(c);
    }
    else if(c == '('){
      data->openParenth++;
      numForOperator = 0;
    }
    else if(c==')'){
      data->closeParenth++;
      if(data->openParenth == data->closeParenth){
        numForOperator=0;
        
        if(data->nums.size()>1){
          data->nums.push(runCalc(data));
        }
      }
      else{
        data->operators.pop();  
      }
      
    }
    //keep track of when to operate
    if(numForOperator > 1){
      data->nums.push(runCalc(data));
      numForOperator--;
    }
    i++;
  }
  return data->nums.top();
}

int lisp(string expression){
  DataObj * d = new DataObj();
  return processExpression(d,expression);
};

int main() {
   string input;
   cout<<"Input lisp expression"<<endl;
   getline(cin,input);
   cout<<lisp(input);
}
