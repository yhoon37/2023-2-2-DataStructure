#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

bool cmp(pair<int, string> a, pair<int, string> b){
    return a.first > b.first;
}


int main() {
    vector<pair<int,string>> inputs;
    map<int, bool> valid;
    int n;
    cin >> n;
    for(int i=0; i<n; i++) {
        string name;
        int price;
        cin >> name >> price;
        if(valid.find(price) != valid.end()){
            valid[price] = false;
        }
        else{
            valid.insert({price, true});
        }
        inputs.push_back({price, name});
    }
    sort(inputs.begin(), inputs.end(), cmp);

    auto result = find_if(inputs.begin(), inputs.end(), [valid](auto a){return valid.at(a.first)==true;});
    if(result != inputs.end()){
        cout << result->second;
    }
    else{
        cout << "NONE";
    }
}