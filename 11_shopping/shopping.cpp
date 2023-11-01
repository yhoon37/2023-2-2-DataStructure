#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
class Customer;
class Counter;

int N, k;   //N=고객 수, k=계산대 수
vector<Counter> counters;
queue<int> result;

class Customer{
public:
    int id;
    int itemNum;
    Customer(int id, int itemNum): id(id), itemNum(itemNum){}
};

class Counter{
public:
    int totalItems=0;
    queue<Customer> customers;
};

void input(){
    cin >> N >> k;
    for(int i=0; i<k; i++){
        counters.push_back(Counter());
    }
    for(int i=0; i<N; i++){
        int id, itemNum;
        cin >> id >> itemNum;
        auto  inCounter = min_element(counters.begin(), counters.end(), [](auto cnt1, auto cnt2){
            return cnt1.totalItems < cnt2.totalItems;
        });
        inCounter->customers.push(Customer(id, itemNum));
        inCounter->totalItems += itemNum;
    }

}

void allMinus(int n){
    for(auto& counter : counters) {
        if(!counter.customers.empty()) counter.customers.front().itemNum -= n;
    }
}

void calculate(){

    for(int i=0; i<N; i++) {
        auto firstOutLine = min_element(counters.rbegin(), counters.rend(), [](auto cnt1, auto cnt2){
            if(!cnt1.customers.empty() && !cnt2.customers.empty())
                return cnt1.customers.front().itemNum < cnt2.customers.front().itemNum;
            else return !cnt1.customers.empty();
        });
        int time = firstOutLine->customers.front().itemNum;
        int id = firstOutLine->customers.front().id;
        result.push(id);
        allMinus(time);
        firstOutLine->customers.pop();
    }
}

void print(){
    while(!result.empty()){
        cout << result.front() << endl;
        result.pop();
    }
}

int main() {
    input();
    calculate();
    print();
}
