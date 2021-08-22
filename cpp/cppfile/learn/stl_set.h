#include <iostream>
#include <set>
using namespace std;

int learn_stl_set(void){
	
	cout<<"learn set usage"<<endl;
	set<string> sset;
	string st1 = "hello";
	string st2 = "world";
	
	// add 
	sset.insert(st1);
	sset.insert(st2);
	
	cout<<sset.size()<<endl;
	
	// del
	sset.erase(st1);
	cout<<sset.size()<<endl;
	
	//loop
	for (auto iter:sset){
		cout<<iter<<" ";
	}
	cout<<endl;
	
	// find
	cout<<"find"<<endl;
	cout<<(sset.find("hello") != sset.end())<<endl;
	cout<<(sset.find("world") != sset.end())<<endl;
	
	
	return 0;
}
