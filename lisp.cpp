#include <iostream>
#include <vector>
#include <cctype>
#include <stack>
//#include <stdlib.h>
#include <sstream>
using namespace std;
/*struct Node {
  int startPos;
  int endPos;
  int stringIndex;
  
  Node * next;
  
  // constructor
  Node(int start, int end, int index): startPos(start), endPos(end), 
                                       stringIndex(index), next(nullptr)
  { }
}; */
//struct for lisp data
struct DataObj {
  stack<int> nums;
  stack<char> operators;
  int openParenth=0;
  int closeParenth=0;
};

//function to handle calculations
//TESTED::PASSED
int calculate(char op,int num1,int num2){
  if(op == '+'){
    return num1 + num2;
  }
  else if(op == '-'){
    return num1-num2;
  }
  else if(op == '*'){
    return num1 * num2;
  }
  else if(op == '/'){
    //doesn't return doubles
    return num1 / num2;
  }
};

bool isOperator(char c){
  vector<char> validOperators = {'+','-','*','/'};
  for(int i=0;i<validOperators.size();i++){
    if(c == validOperators[i]){
      return true;
    }
  }
  return false;
};

void processExpression(DataObj * data,string expr){
  string onGoNum = "";
  int i = 0;
  while(i<expr.length()){
    char c = expr[i];
    //cout<<expr[i]<<endl;
    if(isdigit(c)){
      //get entire num
      onGoNum += c;
      bool numNotFinished = true;
      while(numNotFinished){
        //i++;
        c=expr[i+1];
        //cout<<"c: "<<c<<endl;
        if(isdigit(c)){
          cout<<"num to be added: "<<expr[i+1]<<endl;
          onGoNum+=expr[i+i];
          i++;
        }
        else{
          numNotFinished = false;
        }
      }
      //cout<<"got here";
      int n;
      cout<<onGoNum<<endl;
      stringstream(onGoNum)>>n;
      data->nums.push(n);
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
    }
    i++;
  }
}

int lisp(string expression){
  DataObj * d = new DataObj();
  processExpression(d,expression);
  cout<<d->nums.top()<<endl;
  cout<<d->closeParenth<<endl;
  cout<<d->openParenth<<endl;
  
};

int main() {
   string input;
   cout<<"Input lisp expression"<<endl;
   getline(cin,input);
   lisp(input);
  
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