#include <iostream>
#include <stack>

using namespace std;

int learn_stl_stack(void){
	
	cout<<"learn stack usage"<<endl;
	stack<int> ist;
	ist.push(5);
	ist.push(4);
	ist.pop();
	
	cout<<ist.empty()<<endl; 
	
	
	return 0;
}
