#include <bits/stdc++.h>

using namespace std;

int main()
{
    int x,y;
    cin >> x >> y;

    int besta=y,bestb=y,bestc=y;

    int turns = 0;
    while(true){
        //check the current
        if(besta>=x && bestb>=x && bestc>=x){
            cout << turns << endl;
            break;
        }
        turns++;
        if(turns%3==1){
            //update a
            besta = bestb+bestc-1;
        }
        if(turns%3==2){
            //update b
            bestb = besta+bestc-1;
        }
        if(turns%3==0){
            //update c
            bestc = besta+bestb-1;
        }
    }
    return 0;
}