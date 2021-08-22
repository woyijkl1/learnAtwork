#include <string>

void learn_string(void){
	cout<<"learn string function"<<endl;
	string s = "hello world!";
	cout<<s.substr(6,s.size()-1-6)<<endl;
	
	cout<<"stoi"<<stoi("2")<<endl; 
} 
