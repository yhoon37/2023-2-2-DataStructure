#include <iostream>
#include <map>
#include <vector>
#include <stack>

using namespace std;

int n, k1, k2, performStatementNum=0;
stack<string> callstack;
map<string, vector<string>> functions;
vector<string> performStatement;

bool isFunction(string str) {
    if(str.length() == 1 && isupper(str.c_str()[0])){
        return true;
    }
    return false;
}

bool isinvalid() {
    if (callstack.size() > n) return true;
    return false;
}

void input() {
    string funcName, statement;
    cin >> n >> k1 >> k2;
    for(int i=0; i<n; i++) {
        vector<string> statements;
        cin >> funcName >> statement;

        while(statement != "$") {
            statements.push_back(statement);
            cin >> statement;
        }
        functions[funcName] = statements;
    }
}


void funcCall(string funcName) {
    auto statements = functions[funcName];
    for(auto statement : statements){
        if(isFunction(statement)){
            callstack.push(statement);
            if (isinvalid()) {
                cout << "DEADLOCK" << endl;
                exit(0);
            }

            funcCall(statement);
        }
        else{
            performStatement.push_back(funcName + "-" + statement);
            performStatementNum++;
        }
    }
    callstack.pop();
}

void printOut(int k) {
    if(abs(k) > performStatementNum) cout << "NONE" << endl;
    else{
        if(k>0){
            cout << performStatement[k-1] << endl;
        }
        else{
            cout << performStatement[performStatementNum+k] << endl;
        }
    }
}

int main() {
    input();
    callstack.push("M");
    funcCall("M");
    printOut(k1);
    printOut(k2);
}
