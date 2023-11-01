#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int goods, coupon, sum=0;
vector<int> prices;
stack<int> result;

void input() {
    int price;
    cin >> goods >> coupon;
    for(int i=0; i<goods; i++) {
        cin >> price;
        prices.push_back(price);
    }
}

void sort(){
    int temp;
    for(int i= prices.size()-1; i>0; i--){
        for(int j=0; j<i; j++){
            if(prices[j] < prices[j+1]) {
                temp = prices[j];
                prices[j] = prices[j+1];
                prices[j+1] = temp;
            }
        }
    }
}

void find(vector<int>::iterator start) {
    for(auto it = start; it != prices.end(); it++) {
        result.push(*it);
        sum += *it;

        if(sum < coupon) find(it+1);
        if(sum == coupon) return;
        sum -= *it;
        result.pop();
    }
}

void printOut(){
    if(result.size() == 0) cout << "0" << endl;
    else{
        while(result.size()>0){
            cout << result.top() << endl;
            result.pop();
        }
    }
}

int main() {
    input();
    sort();
    find(prices.begin());
    printOut();
}
