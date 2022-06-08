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
            next[i] = k;
        } else {
           
            k = next[k];
        }
    }
    next[0] = 0;
} 


int KMP(string S, string T) {
    int Ls = S.length(), Lt = T.length();
    int *next = new int[Lt];
    GetNext(T, next);
   
    int i = 0, j = 0;
    while(i < Ls && j < Lt){
        if(T[j] == S[i]) {
            ++i;
            ++j;
        } else if(j == 0){
            ++i;
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
    string T = "abc", S = "abeabc";
    int i = KMP(S, T);
    cout << i << endl;
    return 0;
}