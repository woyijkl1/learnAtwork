#include <iostream>
using namespace std;
struct struct_example{
	int a;
};

struct struct_fun{
	int a;
	struct_fun(int x){
		a = x;
	}
};


struct struct_tree{
	struct_tree* pre,*next;
	int val;
	struct_tree(int x){
		val = x;
		pre = NULL;
		next = NULL;
	}
};




int learn_struct(){
	cout<<"learn struct use"<<endl;
	struct_example st;
	struct_fun st_fun(5);
	struct_tree tree(5);
	cout<<tree.val<<endl;
	cout<<st_fun.a<<endl;
	cout<<st.a<<endl;
} 
