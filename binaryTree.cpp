#include <iostream>
using namespace std;

struct TreeNode
{
    string info;
    TreeNode * left, * right;
    TreeNode(const string& s, TreeNode * lptr, TreeNode * rptr)
       : info(s), left(lptr), right(rptr)
    { }
};

typedef TreeNode * Tree;

TreeNode * createTree() {
	TreeNode * jaguar = new TreeNode("jaguar",   new TreeNode("hippo", 0, 0),
	                                             new TreeNode("leopard", 0, 0));
	TreeNode * giraffe = new TreeNode("giraffe", new TreeNode("elephant", 0, 0),
	                                             jaguar);
	TreeNode * monkey = new TreeNode("monkey", 0, new TreeNode("pig", 0, 0));
	TreeNode * tiger = new TreeNode("tiger", monkey, 0);
    TreeNode * root = new TreeNode("llama", giraffe, tiger);
    
    return root;
}

//TESTED: PASSED
void printAlphabetical(TreeNode * BSTRoot)
{
     //precondition: BSTRoot is pointer to root of Binary Search Tree
     //postcondition: prints values in order
     //precondition: BSTRoot is pointer to root of Binary Search Tree
     if(BSTRoot != 0){
     	printAlphabetical(BSTRoot->left);
     	cout<<BSTRoot->info<<endl;
     	printAlphabetical(BSTRoot->right);
     }
}

//TESTED: PASSED 
int sumOfLengths(TreeNode * root) {
 	// precondition: root is a pointer to root of tree of strings
 	// postcondition: returns sum of the lengths of all strings in tree
 	if(root != 0){
     	return root->info.size() + sumOfLengths(root->left) + sumOfLengths(root->right);
    }
}
 
//TESTED: PASSED 
int maxOfLengths(TreeNode * root) {
 	// precondition: root is a pointer to root of tree of strings
 	// postcondition: returns max of the lengths of all strings in tree
 	if(root == 0){
 		return 0; 
 	}
 	//left side
 	int leftMax = maxOfLengths(root->left);
 	int rightMax = maxOfLengths(root->right);

 	if(root->info.size()>leftMax){
 		leftMax = root->info.size(); 
 	}
 	if(root->info.size()>rightMax){
 		rightMax = root->info.size();
 	}
 	if(leftMax < rightMax){
 		return rightMax;
 	}
 	else{
 		return leftMax;
 	}
 	
}
 
//TESTED: PASSED 
int treeHeight(TreeNode * root) {
    // precondition: root is a pointer to root of tree of strings
 	// postcondition: returns number of levels
 	if(root == 0){
 		return 0;
 	}
 	int leftHeight = treeHeight(root->left);
 	int rightHeight = treeHeight(root->right);
 	
 	if(leftHeight > rightHeight){
 		return leftHeight + 1;
 	}
 	else{
 		return rightHeight + 1;
 	}
}

//TESTED: PASSED 
int sumOfLengthsOnLevel(TreeNode * root, int level) {
 	// precondition: root is a pointer to root of tree of strings
 	// postcondition: returns sum of lengths of all strings in tree on level level
 	if(root != 0){
 	  //int leftSum = 0;
 	  //int rightSum = 0;
 	  if(level>0){
 	    int leftSum = sumOfLengthsOnLevel(root->left,level-1);
 	    int rightSum = sumOfLengthsOnLevel(root->right,level-1);
 	    return leftSum+rightSum;
 	  }
 	  return root->info.size();
 	}
 	return 0;
}
 
//TESTED: PASSED 
int numOfLeaves(TreeNode * root) {
 	// precondition: root is a pointer to root of tree
 	// postcondition: returns number of leaves in tree
 	if(root == 0){
 		return 0;
 	}
 	else if(root->left == 0 and root->right == 0){
 		return 1;
 	}
 	else{
 		return numOfLeaves(root->left) + numOfLeaves(root->right);
 	}
}

//TESTED: "pag" bug -> losing reference to "pig" node 
//        alphabetic bug -> "lion", "lyon" etc
void insert(TreeNode * BSTRoot, const string& str)
{
     //precondition: BSTRoot is pointer to root of Binary Search Tree;
     //str is a string
     //postcondition: inserts str in proper place in binary search tree
     int i = 0;
     if(BSTRoot->left!=0 && BSTRoot->right!=0){
     	//if letter in string comes before letter in root
     	
     	while(str[i] == BSTRoot->info[i]){
     	  cout<<"got to while loop"<<endl;
     	  i++;
     	}
     	cout<<BSTRoot->info[i]<<endl;
     	if(str[i]<BSTRoot->info[i]){
     		insert(BSTRoot->left,str);
     	}
     	else if(str[i]>BSTRoot->info[i]){
     		insert(BSTRoot->right,str);
     	}
     }
     else{
       //cout<<BSTRoot->info;
     	//create a new node and "append" it to the end of the binary tree
     	TreeNode * newNode = new TreeNode(str,0,0);
     	while(str[i] == BSTRoot->info[i]){
     	  i++;
     	  cout<<"got here";
     	}
     	if(str[i]<BSTRoot->info[i]){
     	  BSTRoot->left = newNode;
     	}
     	else{
     	  BSTRoot->right = newNode;
     	}
     	
     }
}

//TESTED: PASSED 
int numOfNodes(TreeNode * root) {
 	// precondition: root is a pointer to root of tree
 	// postcondition: returns number of nodes in tree
 	if(root != 0){
 		return 1+numOfNodes(root->left)+numOfNodes(root->right);
 	}
}

//NOT YET IMPLEMENTED  
void find(TreeNode * BSTRoot, const string& str)
{
     //precondition: BSTRoot is pointer to root of Binary Search Tree of strings; 
     //              str is a string
     //postcondition: returns index of str in tree (e.g., 0 for 1st alphabetical, 1 for second, etc.) or -1 if it's not found
}

//TESTED: PASSED 
void destroyTree(TreeNode * root) {
 	// precondition: root is a pointer to root of tree
 	// postcondition: destroys all nodes in tree
 	if(root != 0){
 		destroyTree(root->left);
 		destroyTree(root->right);
 		delete root;
 	}
 	
}
//NEEDS TO BE TESTED 
bool isBalanced(TreeNode * root) {
 	// precondition: root is a pointer to root of tree
 	// postcondition: returns true exactly when tree is height-balanced
 	//(i.e., left and right subtrees are height-balanced and
 	//their heights differ by at most 1)
 	if(root!=0){
 	  int leftHeight = treeHeight(root->left);
 	  int rightHeight = treeHeight(root->right);
 	  if(leftHeight == rightHeight){
 	    return true;
 	  }
 	  else{
 	    return false;
 	  }
 	}
}

int main() {
	TreeNode * root = createTree();
	//printAlphabetical(root);
	//int b = maxOfLengths(root);
	
	//printAlphabetical(root);
	//destroyTree(root->left);
	//insert(root,"bat");
	//insert(root,"lyon");
	printAlphabetical(root);
	//cout<<b;
	//int b = sumOfLengthsOnLevel(root,3);
	//cout<<b;
}