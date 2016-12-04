#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Code copied with adaptations/edits/removals by Anonymous 10/31/16 from:
// Owen Astrachan 11/8/95
// revised 3/30/00, key must be a string, value can be anything

template<class Value>
class HMap
{
  public:
  	 HMap(int size); // size of Hashmap
  	//~HMap();
  	
  	virtual bool contains(const string & key) const;        // is key in map?
  	
  	virtual Value& get(const string& key);
  	
  	virtual void remove(const string & key);
  	virtual void insert(const pair<string,Value> & pair);
  	virtual void insert(const string & key, const Value & value);
  	
  private:
    struct Node
    {
	  pair<string, Value> info;
	  Node * next;
	  Node (const string& s,
	        const Value& v,
	        Node * ptr)
	      : info(s,v), next(ptr)
	  {
		
	  }
    };

    virtual unsigned int hash(const string &key) const;
    
    vector<Node *> myList;                  // vector of nodes
    int myNumElts;                          // # elements stored
};

//IMPLEMENTED::Org Code
template<class Value>
HMap<Value>::HMap(int size): myList(size,nullptr), myNumElts(0) {
	// fill myList with nullptrs
}

//IMPLEMENTED::TESTED::PASSED
template <class Value>
bool HMap<Value>::contains(const string & key) const
// postcondition: returns true if key in map, otherwise returns false
{
  for(int i=0;i<myList.size();i++){
    Node * curPtr = myList[i];
    
    while(curPtr != 0){
      if(curPtr->info.first == key){
        return true;
      }
      curPtr = curPtr->next;
    }
  }return false;
  /*int b = hash(key)%myList.size();
  Node * curPtr = myList[b];
  while(curPtr != 0){
    if(curPtr->info.first == key){
      return true;
    }
    curPtr = curPtr->next;
  }
  return false;*/
}

//IMPLEMENTED::TESTED::PASSED
template <class Value>
Value & HMap<Value>::get(const string & key)
// postcondition: returns value associated with key in map
// exception: if key not in map, error printed, program halted
{
  for(int i=0;i<myList.size();i++){
    Node * curPtr = myList[i];
    while(curPtr != 0){
      if(curPtr->info.first == key){
        return curPtr->info.second;
      }
      curPtr = curPtr->next;
    }
  }
  cout<<"ERROR!";
}

//IMPLEMENTED::Org Code
template <class Value>
unsigned int HMap<Value>::hash(const string & key) const
{
	
    unsigned int hval = 0;
    int k;
    int len = key.length();
    for(k=0; k < len; k++)
    {
        hval = (hval << 5) ^ hval ^ key[k]; // ^ is XOR
    }
    return abs(hval);
    
}

//NOT IMPLEMENTED
template <class Value>
void HMap<Value>::remove(const string & key) 
// postcondition: returns index of key in private vector (pointer)
//                returns 0 if key NOT in vector
{
  
}

//UNDER CONSTRUCTION::'exiting with non-zero status from else statement'
template <class Value>
void HMap<Value>::insert(const pair<string,Value> & pair)
// precondition: pair.first key NOT stored in map
// postcondition: pair is added to map (maps pair.first -> pair.second)
{
  int a = hash(pair.first);
  int b = myList.size();
  int i = abs(a%b);
  
  if(myList[i] == nullptr){
    myList[i] = new Node(pair.first,pair.second,0);

  }
  else{
    myList[i]= new Node(pair.first,pair.second,myList[i]);
  }
}

//IMPLEMENTED::Org Code
template <class Value>
void HMap<Value>::insert(const string & key, const Value & val)
{
    insert(pair<string,Value>(key,val));
}

int main() {
    HMap<int> map(10);
    map.insert("elephant",1);
    map.insert("giraffe",2);
    map.insert("hippo",3);
    map.insert("jaguar",4);
    map.insert("leopard",5);
    map.insert("llama",6);
    map.insert("monkey",7);
    map.insert("pig",8);
    map.insert("tiger",9);
    //cout<<map.contains("tiger");
    //cout<<map.get("bat");
}