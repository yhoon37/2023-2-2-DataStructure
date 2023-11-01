#include <iostream>
#include <map>
#include <vector>

using namespace std;

int n, k1, k2, performStatementNum=0;
string mainFunc;
map<string, vector<string>> functions;
map<string, vector<string>> forbidFunctions;
vector<string> performStatement;

bool isFunction(string str) {
    if(str.length() == 1 && isupper(str.c_str()[0])){
        return true;
    }
    return false;
}

bool isinvalid(string callFunc, string calledFunc) {
    for(auto funcName : forbidFunctions[callFunc]){
        if(funcName == calledFunc) return true;
    }
    return false;
}

void input() {
    string funcName, statement;
    cin >> n >> k1 >> k2;
    for(int i=0; i<n; i++) {
        vector<string> statements;
        cin >> funcName >> statement;
        if(i==0) mainFunc = funcName;
        while(statement != "$") {
            statements.push_back(statement);
            if(isFunction(statement)) {
                forbidFunctions[statement].push_back(funcName);
            }
            cin >> statement;
        }
        functions[funcName] = statements;
    }
}


void analyze(string funcName) {
    auto statements = functions[funcName];
    for(auto statement : statements){
        if(isFunction(statement)){
            if (isinvalid(funcName, statement)) {
                cout << "DEADLOCK" << endl;
                exit(0);
            }
            analyze(statement);
        }
        else{
            performStatement.push_back(funcName + "-" + statement);
            performStatementNum++;
        }
    }

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
    analyze(mainFunc);
    printOut(k1);
    printOut(k2);
}
