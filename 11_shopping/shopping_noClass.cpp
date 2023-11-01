#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N, k;   //N=고객 수, k=계산대 수
queue<pair<int, int>> customers;
vector<pair<queue<pair<int, int>>, int>> counters;
queue<int> result;

void input(){
    cin >> N >> k;
    for(int i=0; i<N; i++){
        int id, itemsNum;
        cin >> id >> itemsNum;
        customers.push({id, itemsNum});
    }
    for(int i=0; i<k; i++){
        counters.push_back({{},0});
    }
}

void allMinus(int n){
    for(auto& counter : counters) {
        if(!counter.first.empty()) counter.first.front().second -= n;
    }
}

void calculate(){
    while(!customers.empty()){
        int id = customers.front().first;
        int itemsNum = customers.front().second;
        auto  inCounter = min_element(counters.begin(), counters.end(), [](auto cnt1, auto cnt2){
            return cnt1.second < cnt2.second;
        });
        inCounter->first.push({id, itemsNum});
        inCounter->second += itemsNum;
        customers.pop();
    }
    for(int i=0; i<N; i++) {
        auto firstOutLine = min_element(counters.rbegin(), counters.rend(), [](auto cnt1, auto cnt2){
            if(!cnt1.first.empty() && !cnt2.first.empty())
                return cnt1.first.front().second < cnt2.first.front().second;
            else return !cnt1.first.empty();
        });
        int time = firstOutLine->first.front().second;
        int id = firstOutLine->first.front().first;
        result.push(id);
        allMinus(time);
        firstOutLine->first.pop();

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
