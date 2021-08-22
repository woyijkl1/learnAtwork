#include <math.h>
#include <algorithm>
#include <vector>
#include <memory.h>

struct struct_a{
	int a;
	int b;
	struct_a(int x, int y){
		a = x;
		b = y;
	}
};



void learn_function_use(){
	cout<<"learn function use"<<endl;
	//pow function
	cout<<pow(10,0)<<endl;
	
	//single char to string
	string temp_s(1,'a');
	cout<<temp_s<<endl;
	
	//string delete
	string s = "abcd";
	s.erase(s.begin());
	cout<<s<<endl;
	
	
	//memset
	int a[10];
	for (auto i:a){
		cout<<i<<" ";
	} 
	cout<<endl;
	memset(a,0,sizeof(a));
	int b[100][100];
	memset(b,0,sizeof(int)*100*100);
	for (auto i: a){
		cout<<i<<" ";
	}
	cout<<endl;


	//min
	int t[5] = {5,4,3,2,1};
	cout<<" min is:"<<*min_element(t,t+4)<<endl;
	
	//vector find 
	vector<int> vec = {1,2,7,3,4,5};
	cout<<"find? "<<(find(vec.begin(),vec.end(),3) != vec.end() )<<endl;
	
	//max 
	cout<<max(1,2)<<endl;
	cout<<*max_element(vec.begin(),vec.end())<<endl;
	
	//sort
	sort(vec.begin(),vec.end());
	for (auto i:vec){
		cout<<i<<" ";
	}
	cout<<endl;
	
	cout<<"learn struct init"<<endl;
	//结构体初始化
	struct_a sa1 = {1,2};
	// 栈里面就是 st.push({1,2}) 
	cout<<sa1.a<<endl;
	
	
	
}
