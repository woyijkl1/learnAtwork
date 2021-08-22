#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int lean_stl_vector() {
	cout<<"learn vector usage"<<endl;
	
	// declear
	vector<int> vec;
	for (int i=0;i<10;i++){
		vec.push_back(i);
	}
	
	// insert
	vec.insert(vec.begin()+2,100);
	cout<<vec.size()<<endl;
	
	
	// del
	vec.erase(vec.begin()+1);
	vec.pop_back();
	cout<<vec.size()<<endl;
	
	
	//find
	cout<<"find"<<endl;
	cout<<(find(vec.begin(),vec.end(),100) != vec.end() ) <<endl;
		
	// loop  
	for (int i=0;i<vec.size();i++){
		cout<<vec[i]<<" ";
	} 
	cout<<endl;
	
	for ( auto i : vec){
		cout<<i<<" ";
	}
	cout<<endl;
	
	return 0;
}
