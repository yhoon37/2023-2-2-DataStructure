#include <iostream>
#include <vector>

using namespace std;
class Point;

int K, Time, Cop1Case=1, TotalDistance, DistanceBetweenCops1=0, DistanceBetweenCops2=0;
vector<Point> points;
vector<Point> pathCounterclockwise;

class Point{
public:
    Point(){}
    Point(int x, int y): x(x), y(y) {}
    int x;
    int y;
};

void input(){
    cin >> K;
    for(int i=0; i<K; i++){
        int x, y;
        cin >> x >> y;
        points.push_back(Point(x,y));
    }
    cin >> Time;
}

void setCondition(){
    int meetTimes=0, firstMeetTime=0, secondMeetTime=0;
    points.push_back(points[0]);
    for(int i=0; i<K/2; i++){
        DistanceBetweenCops1 += abs(points[i].x - points[i+1].x) + abs(points[i].y - points[i+1].y);
    }
    for(int i=K/2; i<K; i++){
        DistanceBetweenCops2 += abs(points[i].x - points[i+1].x) + abs(points[i].y - points[i+1].y);
    }

    TotalDistance = DistanceBetweenCops1 + DistanceBetweenCops2;

    Time = Time%TotalDistance;

    if(DistanceBetweenCops2 % 2 == 0) {
        firstMeetTime = DistanceBetweenCops2/2;
        meetTimes++;
    }
    if(DistanceBetweenCops1 % 2 == 0){
        if(firstMeetTime != 0) secondMeetTime = firstMeetTime + DistanceBetweenCops1;
        firstMeetTime = DistanceBetweenCops1/2;
        meetTimes++;
    }

    for(int i=0; i<K; i++) {
        if(i <= K/2-1){
            pathCounterclockwise.push_back(points[K/2-1-i]);
        }
        else{
            pathCounterclockwise.push_back(points[K-(i-K/2)-1]);
        }
    }

    pathCounterclockwise.push_back(pathCounterclockwise[0]);

    if(meetTimes == 2){
        if(firstMeetTime <= Time && Time < secondMeetTime){
            Cop1Case = 0;
        }
    }
    if(meetTimes == 1){
        if(Time >= firstMeetTime){
            Cop1Case = 0;
        }
    }
}

Point go(int time, vector<Point> path){
    int nextIndex=1;
    Point result = path[0];

    while(time>0) {
        Point next = path[nextIndex];

        if(result.x == next.x) {
            if(result.y < next.y) {
                result.y++;
            }
            else{
                result.y--;
            }
        }
        else{
            if(result.x < next.x) {
                result.x++;
            }
            else{
                result.x--;
            }
        }

        if(result.x == next.x && result.y == next.y) {
            nextIndex++;
        }
        time--;
    }
    return result;
}

void print(){
    Point cop1, cop2;
    if(Cop1Case){
        cop1 = go(Time, points);
        cop2 = go(Time, pathCounterclockwise);
    }
    else{
        cop1 = go(Time, pathCounterclockwise);
        cop2 = go(Time, points);
    }
    cout << cop1.x << " " << cop1.y << endl << cop2.x << " "<<cop2.y << endl;
}

int main() {
    input();
    setCondition();
    print();
}
