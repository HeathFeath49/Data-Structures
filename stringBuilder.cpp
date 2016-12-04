#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int startPos;
	int endPos;
	int stringIndex;
	
	Node * next;
	
	// constructor
	Node(int start, int end, int index): startPos(start), endPos(end), 
	                                     stringIndex(index), next(nullptr)
	{ }
};

typedef Node * LinkedList;

//NOT TESTED
void insertAfter(Node * nodeInList, Node * nodeToInsert) {
	if(nodeInList->next == nullptr){
		nodeInList->next = nodeToInsert;
	}
	else{
		nodeToInsert->next = nodeInList;
		nodeInList->next = nodeToInsert;
	}
}

void deleteAfter(Node * nodeInList) {
	
}

//TESTED: PASSED
bool isEmpty(LinkedList lst) {
	return lst == nullptr;
}

class StringBuilder {
	public:
		StringBuilder(string str);
		~StringBuilder();
		
		int lengthOfLinkedList = 0;
		vector<string> stringParts;
		
		// accessor methods
		char charAt(int index) const;
		string substring(int start, int end) const;
		string substring(int start) const;
		string toString() const;
		int indexOf(const string &needle, int startPos) const;
		int lastIndexOf(const string &needle, int startPos) const;
		int length() const;
		
		// mutator methods
		void append(string str);
		void deleteChars(int start, int end);
		void deleteChars(int start);
		void insert(int offset, const string str);
		void replace(const string sub, const string replaceStr);
		void reverse();
	private:
		LinkedList positions;
		
		int len; // length of string
		
};

//TESTED: PASSED
StringBuilder::StringBuilder(string str) {
	// constructor: set positions to new LinkedList of one node,
	positions = new Node(0,str.length()-1,0);
	lengthOfLinkedList++;
	//add str to stringParts using vector's push_back method
	stringParts.push_back(str);
}


//TESTED: PASSED
char StringBuilder::charAt(int wantedIndex) const {
	//returns the character at index
	//Use nodes to find location of desired index
	//Start with first node;
	Node * curPtr = positions;
	int displacement = 0;
	bool foundNode = false;
	while (!foundNode){
		if(wantedIndex > curPtr->endPos+displacement){
			displacement += stringParts[curPtr->stringIndex].size();
			curPtr = curPtr->next;
			
		}
		else{
			foundNode = true;
		}
	}
	return stringParts[curPtr->stringIndex][wantedIndex-displacement];
}

//TESTED: PASSED
void StringBuilder::append(string str) {
	//add string to vector
	stringParts.push_back(str);
	
	//create new node
	Node *newNode =  new Node(0,str.length()-1,stringParts.size()-1);
	lengthOfLinkedList++;
	//Find last node in linked list
	Node *curPtr = positions;
	while(curPtr->next != nullptr){
		curPtr = curPtr->next;
	}
	//set the last node's 'next' pointer to point to new node 
	curPtr->next = newNode;
}

//TESTED: PASSED
string StringBuilder::substring(int wantedStartI, int wantedEndI) const {
	// returns the substring from start index start to end
	bool stringComplete = false;
	int displacement = 0;
	Node * curPtr = positions;
	string newString;
	
	while(!stringComplete){
		if((stringParts[curPtr->stringIndex].size()==0) || !(wantedStartI <= curPtr->endPos+displacement)){
			displacement += stringParts[curPtr->stringIndex].size();
			curPtr = curPtr->next;
			newString.append(" ");
		}
		else{
			newString.push_back(stringParts[curPtr->stringIndex][wantedStartI-displacement]);
			if(wantedStartI == wantedEndI){
				stringComplete = true;
				break;
			}
			else{
				wantedStartI++;
			}
		}

	}
	return newString;
}

//TESTED: PASSED (error in original substring function)
string StringBuilder::substring(int wantedStartI) const {
	// returns the substring from start index to the end of the string
	int len = length();
	cout<<len<<endl;
	string newString;
	newString = substring(wantedStartI,len-1);
	return newString;
}

//TESTED:PASSED;
int StringBuilder::indexOf(const string &needle, int startPos) const {
	// returns the index of the first occurrence of needle in the string,
	// starting with index startPos if it exists, -1 otherwise
	int len = length();
	int j = 0;
	int lenOfNeedle = needle.size()-1;
	for(int i=startPos;i<len;i++){
	  if(charAt(i)==needle[j]){
	    //cout<<"found a match";
	    if(j == lenOfNeedle){
	      //cout<<"match complete"<<endl;
	      return (i-j);
	    }
	    j++;
	  }
	  else{
	    j=0;
	  }
	}
	return -1;
}

//TESTED: PASSED
int StringBuilder::lastIndexOf(const string &needle, int startPos) const {
	// returns the index of the last occurrence of needle in the string, 
	// starting with index startPos if it exists, -1 otherwise
	int latestIndex = -1;
	string b = needle;
	cout<<b;
	int index = indexOf(needle,startPos);
	
	while(index > -1){
	  latestIndex = index;
	  index = indexOf(needle,index+needle.size());
	}
	return latestIndex;
}

//TESTED: PASSED
int StringBuilder::length() const {
	// returns length of represented string
	int lengthOfString = 0;
	for(int i=0;i<stringParts.size();i++){
		lengthOfString+=stringParts[i].size();
	}
	return lengthOfString;
}
//TESTED: PASSED
string StringBuilder::toString() const {
	// forms and returns a string from the list of Nodes, concatenating the strings
	// that each Node represent in order from the beginning to the end
	
	return substring(0);
}

//UNDER CONSTRUCTION   !!DOES NOT CURRENTLY DELETE EMPTY NODE!!
void StringBuilder::deleteChars(int wantedStartI, int wantedEndI) {
	// removes the characters from start to end from this string, inclusively
	int numToDel = wantedEndI - wantedStartI + 1;
	int numDelSoFar = 0;
	int displacement = 0;
	Node * curPtr = positions;
	while(numToDel != 0){
		/*if(stringParts[curPtr->stringIndex].size()==0){
			//cout<<"node empty!"<<endl;
			curPtr->endPos = 0;
		}*/
	
		if(wantedStartI+numDelSoFar <= curPtr->endPos+displacement){
			//delete char at wantedStartI
			cout<<"got to if"<<endl;
			//Instead of erasing, just change data in linked list?
			cout<<"string index: "<<curPtr->stringIndex<<endl;
			cout<<stringParts[curPtr->stringIndex]<<endl;
			stringParts[curPtr->stringIndex].erase(wantedStartI-displacement,1);
			numDelSoFar++;
			numToDel--;
		}
		
		else{
			cout<<"got to else"<<endl;
			curPtr->endPos = stringParts[curPtr->stringIndex].size()-1;
			/*displacement += curPtr->endPos+1;*/
			displacement += (curPtr->endPos+numDelSoFar-1);
			
			cout<<"displacement: "<<displacement<<endl;
			curPtr = curPtr->next;
		
		}
	}
}

//UNDER CONSTRUCTION
void StringBuilder::deleteChars(int start) {
	// removes the characters from start to the end of this string
	int len = length();
	deleteChars(start,len); 
}

//NOT IMPLEMENTED
void StringBuilder::insert(int offset, const string str) {
	// inserts str after offset characters
}

//NOT IMPLEMENTED
void StringBuilder::reverse() {
	// reverses the string that this represents
}

//NOT IMPLEMENTED
void StringBuilder::replace(const string sub, const string replaceStr) {
	// replaces all occurrence of sub in string with replaceStr
}

//NOT IMPLEMENTED
StringBuilder::~StringBuilder() {
	// destructor
	// cleanup: need to remove all nodes in linked list (be careful with the order)
}

int main() {
  StringBuilder * s = new StringBuilder("Blue");
  s->append("Hair");
  s->append("Is");
  s->append("Blue");
  //s->deleteChars(0,5);
  cout<<s->stringParts[0]<<endl;
  cout<<s->stringParts[1]<<endl;
  cout<<s->stringParts[2]<<endl;
  cout<<s->stringParts[3]<<endl;
  cout<<s->toString()<<endl;
  cout<<s->substring(0,13);
  //int b = s->lastIndexOf("Blue",0);
  //b = s->indexOf("Blue",0);
  //cout<<b;
  

  return 0;
}