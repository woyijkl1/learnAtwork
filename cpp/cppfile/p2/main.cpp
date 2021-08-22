#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
int main(int argc, char** argv) {
    string s1 = "abcdsjkl";
    string s2 = "bedgl";
    int dp[s1.size()+1][s2.size()+1];
    for (int i=0; i<s1.size()+1; i++){
    	dp[i][0] = 0;
	}
	for (int i = 0; i<s2.size()+1; i++ ){
		dp[0][i] = 0;
	}
	int m = 0;
	for (int i=1; i<s1.size()+1; i++){
		for (int j=1; j<s2.size()+1;j++){
			if (s1[i] == s2[j]){
				dp[i][j] = dp[i-1][j-1]+1;
			}
			else{
				dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
			}
			m  = max(m,dp[i][j]);
		}
	}
	cout<<m<<endl;
	return 0;
}
