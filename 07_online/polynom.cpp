#include <iostream>
#include <vector>

using namespace std;

int n, t, c, e;
vector<int> sum(1001);
vector<pair<int, int>> result;

void input() {
    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> t;
        for(int j=0; j<t; j++) {
            cin >> c >> e;
            sum[e] += c;
        }
    }
}

void setResult(){
    for(int i=1000; i >= 0; i--) {
        if(sum[i] != 0) {
            result.push_back({sum[i], i});
        }
    }
}

void printOut() {
    if(result.size() == 0) {
        cout << "0 0";
    }
    else {
        cout << result.size() << endl;
        for(auto x : result) {
            cout << x.first << " " << x.second << endl;
        }
    }
}

int main() {

    input();

    setResult();

    printOut();
}
