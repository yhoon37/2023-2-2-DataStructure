#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int yardSize;
int maxIndex, minIndex, maxSize, minSize;
vector<stack<int>> yard;

void input(){
    cin >> yardSize;
    for(int i=0; i<yardSize; i++) {
        int ton, amount;

        stack<int> y;
        cin >> amount;
        for(int j=0; j<amount; j++){
            cin >> ton;
            y.push(ton);
        }
        yard.push_back(y);
    }
}

void set(){
    maxIndex = 0; minIndex = 0;
    maxSize = yard[0].size(), minSize = yard[0].size();
    for(int i=1; i<yardSize; i++){
        if(maxSize < yard[i].size()) {
            maxIndex = i;
            maxSize = yard[i].size();
        }
        if(maxSize == yard[i].size() && maxSize != 0) {
            if(yard[maxIndex].top() < yard[i].top()) maxIndex = i;
        }
        if(minSize > yard[i].size()){
            minIndex = i;
            minSize = yard[i].size();
        }
    }
}

void move() {
    while((maxSize-minSize) > 1) {

        yard[minIndex].push(yard[maxIndex].top());
        yard[maxIndex].pop();
        set();
    }
}

void printOut(){
    for(auto y : yard) {
        if(!y.empty()) {
            vector<int> printList;
            int size = y.size();
            for(int i=0; i<size; i++){

                printList.push_back(y.top());
                y.pop();
            }
            reverse(printList.begin(), printList.end());
            for(auto n : printList) {
                cout << n << " ";
            }
        }
        else{
            cout << "0";
        }
        cout << endl;
    }
}



int main() {

    input();
    set();

    move();
    printOut();

    return 0;
}
