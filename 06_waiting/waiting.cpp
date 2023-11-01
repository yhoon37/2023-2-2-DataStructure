#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k, waitingNum;
    char inOut;

    vector<vector<int>> waitings;

    cin >> n >> k;

    for(int i=0; i<n; i++) {
        cin >> inOut >> waitingNum;

        if(inOut == '+') {
            if(waitings.size() == 0){
                waitings.push_back({waitingNum});
                continue;
            }

            for(auto current = waitings.rbegin(); current != waitings.rend(); current++) {

                auto findIt = find_if(current->rbegin(), current->rend(), [waitingNum](int num){
                    return waitingNum > num;
                });

                if(findIt != current->rend()){

                    current->insert(findIt.base(), waitingNum);
                    if(current->size() == 2*k){

                        vector<int> half(current->begin()+k, current->end());
                        //current는 reverse iterator인데 erase와 insert는 reverse iterator를 인자로 받지 않기때문에
                        //.base() 를 써줘야 한다

                        current->erase(current->begin()+k, current->end());
                        waitings.insert(current.base(), half);

                    }
                    break;
                }
                if(findIt == current->rend() && current == waitings.rend()-1){

                    current->insert(findIt.base(), waitingNum);
                    if(current->size() == 2*k){
                        vector<int> half(current->begin()+k, current->end());

                        current->erase(current->begin()+k, current->end());
                        waitings.insert(current.base(), half);
                    }
                    break;
                }
            }
        }
        else {
            for(auto current = waitings.begin(); current != waitings.end(); current++) {
                auto findIt = find_if(current->begin(), current->end(), [waitingNum](int num){
                    return waitingNum == num;
                });
                if(findIt != current->end()){
                    current->erase(findIt);
                    if(current->size() == 0) {
                        waitings.erase(current);
                    }
                    break;
                }
            }
        }
//
    }

    for(auto line: waitings) {
        cout << line[0] << endl;
    }

    return 0;
}
