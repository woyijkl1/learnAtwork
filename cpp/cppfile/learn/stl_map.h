#include <iostream>
#include <map>
using namespace std;

int learn_stl_map(void){
	
	cout<<"learn map usage"<<endl;
	
	map<string,int> simap;
	
	//insert
	simap["hello"] = 1;
	simap["world"] = 1;


	//iter
	for (auto iter:simap){
		cout<<iter.first<<':'<<iter.second<<endl;
	} 
	
	for (auto iter = simap.begin();iter!=simap.end();iter++){
		cout<<iter->first<<":"<<iter->second<<endl;
	}
	
	//look up
	cout<<"map look up "<<(simap.find("hello")!=simap.end())<<endl;
	
	//del
	simap.erase("hello");
	cout<<simap.size()<<endl;
	
	return 0;
}
