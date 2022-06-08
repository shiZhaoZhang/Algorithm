#include "string"
#include "iostream"
using namespace std;
void GetNext(string T, int* next) {
    next[0] = -1;
    int i = 0, k = -1, L = T.length();
    while(i < L - 1){
        if(k == -1 || T[i] == T[k]) {
            ++k;
            ++i;
            //如果T[i]与S[i]不匹配，会回溯到T[k]，但是如果T[i]==T[k]，那T[i]本来就和S[i]不匹配，T[k]自然也不匹配，还不如直接回溯
            if(T[i] != T[k]){
                next[i] = k;
            } else {
                next[i] = next[k];
            }
        } else {
           
            k = next[k];
        }
    }
    //不对next[0]修改
    //next[0] = 0;
} 


int KMP(string S, string T) {
    int Ls = S.length(), Lt = T.length();
    int *next = new int[Lt];
    GetNext(T, next);
   
    int i = 0, j = 0;
    while(i < Ls && j < Lt){
        //添加j == -1，因为只要j到了第一位，相同，i也是要前进一位；不同，i也是要前进一位
        if(j == -1 || T[j] == S[i]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }
    delete []next;

    if (j == Lt){
        return i - j;
    } else {
        return -1;
    }
}

int main(){
    string T = "z", S = "aaaacaaaad";
    int i = KMP(S, T);
    cout << i << endl;
    return 0;
}