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
  //int num1;
  //int num2;
  int numForOperator = 0;
  int i = 0;
  while(i<expr.length()){
    char c = expr[i];
    //cout<<expr[i]<<endl;
    //cout<<isspace(expr[i])<<endl;
    /*if(!isdigit(c)){
      cout<<"found space"<<endl;
    }*/
    if(isdigit(c)){
      //get entire num
      onGoNum += c;
      bool numNotFinished = true;
      while(numNotFinished){
        //i++;
        c=expr[i+1];
        //cout<<"c: "<<c<<endl;
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
      //cout<<c<<" is an operator"<<endl;
      data->operators.push(c);
    }
    else if(c == '('){
      data->openParenth++;
    }
    else if(c==')'){
      data->closeParenth++;
      data->operators.pop();
    }
    
    //keep track of when to operate
    if(numForOperator > 1){
      int b = runCalc(data);
      //cout<<b<<endl;
      data->nums.push(b);
      numForOperator--;
    }
    if(data->openParenth == data->closeParenth){
      numForOperator=0;
      if(data->nums.size()>1){
        cout<<"got here"<<endl;
        runCalc(data);
      }
      return data->nums.top();
    }
    
    i++;
  }
  
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

//CHECK CONTENTS OF STACKS
/*while(!nums.empty()){
  int n = nums.top();
  cout<<n<<endl;
  nums.pop();
}
while(!operators.empty()){
  char o = operators.top();
  cout<<o<<endl;
  operators.pop();
}*/
