#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    vector<int> right;
    vector<int> down;
    int i=1;
    while(true) {
        int n;
        cin >> n;
        if(n == 0) break;
        if(i%2 == 1) {
            right.push_back(n);
        }
        else {
            down.push_back(n);
        }
        i++;
    }
    int height = accumulate(down.begin(), down.end(), 0);

    int x, y;
    while(cin >> x >> y) {
        int sum_r=0, sum_d=height;

        for(int j=0; j<right.size(); j++){
            sum_r += right[j];
            if(x < sum_r) {
                for(int k=0; k<j; k++){
                    sum_d -= down[k];
                }
                if(sum_d < y) cout << "out" << endl;
                else if(sum_d == y) cout << "on" << endl;
                else cout << "in" << endl;
                break;
            }
            else if(x == sum_r) {
                int k;
                for(k=0; k<j; k++){
                    sum_d -= down[k];
                }
                if(y > sum_d) cout << "out" << endl;
                else if(sum_d -down[k] > y)cout << "in" << endl;
                else cout << "on" << endl;
                break;
            }

        }
        if(sum_r < x) {cout << "out" << endl;}
    }
}