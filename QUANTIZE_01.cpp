//result:정답
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 987654321;
int N,S;
int arr[100];
int cache[100][11];
int getMin(int start,int end,int startIdx,int endIdx){
	int ret = INF;
	for(int i=start;i<=end;i++){
		int sum = 0;
		for(int j=startIdx;j<=endIdx;j++){
			sum += (i-arr[j])*(i-arr[j]);
		}
		ret = min(ret,sum);
	}
	return ret;
}
int solve(int start,int s){
	//cout << start <<  ' '<<s << endl;
	if(start >= N || s == 0){
		return INF;
	}
	int& ret = cache[start][s];
	if(ret != -1) return ret;
	ret = INF;
	int endVal = arr[start];
	for(int i = start+1;i<N;i++){
		if(arr[i] != endVal){
			//cout << getMin(arr[start],endVal,start,i-1) << endl;
			ret = min(ret,getMin(arr[start],endVal,start,i-1)+solve(i,s-1));
			endVal = arr[i];
		}
	}
	ret = min(ret,getMin(arr[start],arr[N-1],start,N-1));
	return ret;
}
int main(){
	cin.tie(NULL);
	cout.tie(NULL);
	std::ios::sync_with_stdio(false);
	int test_case;
	cin >> test_case;
	while(test_case--){
		memset(cache,-1,sizeof(cache));
		cin >> N >> S;
		for(int i=0;i<N;i++){
			cin >> arr[i];
		}
		sort(arr,arr+N);
		cout << solve(0,S) << '\n';
	}
}