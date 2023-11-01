#include <iostream>
#include <vector>

using namespace std;

class Point;

vector<Point> points;
int k, x, y;

class Point {
public:
    Point(int x, int y) : x(x), y(y) {}
    Point(){}
    int x;
    int y;

    bool operator ==(Point other){
        if(other.x == x && other.y == y) return true;
        else return false;
    }
};

ostream& operator <<(ostream& os, Point p){
    os << p.x << " " << p.y;
    return os;
}


class Cop {
public:
    Point position;
    int direction;
    int next_point_index;

    Cop(Point position, int direction, int next_point_index) :
            position(position), direction(direction), next_point_index(next_point_index) {}

    void go(){
        if(points[next_point_index].x > position.x) {
            position.x++;
        }
        else if(points[next_point_index].x < position.x){
            position.x--;
        }

        if(points[next_point_index].y > position.y){
            position.y++;
        }
        else if(points[next_point_index].y < position.y) {
            position.y--;
        }
    }

    void change_direction() {direction *= -1;}

    void change_next() {
        next_point_index += direction;
        if(next_point_index == -1) next_point_index = k-1;
        if(next_point_index == k) next_point_index = 0;
    }
};


int main() {
    int time, total_distance = 0;

    cin >> k;

    for(int i=0; i<k; i++) {
        cin >> x >> y;
        Point new_point = Point(x,y);
        points.push_back(new_point);
    }


    for(int i=0; i<k-1; i++){
        total_distance += abs(points[i].x - points[i+1].x) + abs(points[i].y - points[i+1].y);
    }
    total_distance += abs(points[0].x - points[k-1].x) + abs(points[0].y - points[k-1].y);
    cout << "total_d: " << total_distance << endl;

    Cop cop1(points[0], 1, 1);
    Cop cop2(points[k/2-1], -1, k/2-2);

    cin >> time;

    time = time%total_distance;

    while(time > 0) {
        cop1.go();
        cop2.go();

        int CI1 = cop1.next_point_index;
        int CI2 = cop2.next_point_index;
        if( (cop1.position == cop2.position) && (CI1 == CI2 || abs(CI1-CI2) == 1||(CI1==0 && CI2 == k-1) || (CI1 == k-1 && CI2 == 0)) ) {
            cop1.change_direction();
            cop2.change_direction();
            cop1.change_next();
            cop2.change_next();
            //time--;
            //continue;
        }
        if(cop1.position == points[cop1.next_point_index]){
            cop1.change_next();

        }
        if(cop2.position == points[cop2.next_point_index]){
            cop2.change_next();

        }
        time--;
    }

    cout << cop1.position << endl;
    cout << cop2.position << endl;


}
