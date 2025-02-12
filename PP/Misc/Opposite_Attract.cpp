#include <bits/stdc++.h>
#include <string.h>
using namespace std;

int main() {
	// your code goes here
    int tc = 0;
    cin>>tc;

    for(int i = 0; i < tc; i++){
        int len = 0;
        string str ;
        cin>>len;
        cin>>str;
        for(int j = 0; j < str.length(); j++){
            if(str[j] == '0'){
                str[j] = '1';
            }else{
                str[j] = '0';
            }
        }
        cout<<str<<endl;
        
    }

}