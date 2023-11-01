#include <iostream>
#include <list>

class Point {
public:
    Point(int x, int y) : x(x), y(y) {}
    int x;
    int y;

private:
};

class Cop {
public:
    Point position;
    bool direction;

    Cop(Point point, bool direction): position(point), direction(direction){}

    void go(Point destination){
        if(destination.x == position.x) {
            if(position.y < destination.y){
                position.y++;
            }
            else {
                position.y--;
            }
        }
        else {
            if(position.x < destination.x) {
                position.++;
            }
            else {
                position.x--;
            }
        }
    }

    void change_direction() {direction = !direction;}
    Point get_position() {return position;}

private:
};

int main() {
    int k, x, y, time;
    list<Point> points;
    auto cop1_next, cop2_next;

    cin >> k;

    for(int i=0; i<k; i++) {
        cin >> x >> y;
        Point new_point = Point(x,y);
        points.push_back(new_point);
    }

    cop1_next = points.begin() + 1;
    cop2_next = points.begin+ k/2 + 1;

    Cop cop1(points.front(), true);
    Cop cop2(*(points.begin() + k/2) , false);

    cin >> time;

    while(time > 0) {
        cop1.go(*cop1_next);
        cop2.go(*cop2_next);

        if(cop1.position == cop2.position) {
            cop1.change_direction();
            cop2.change_direction();
        }

        if(cop1.position == *cop1_next) {
                if(cop1.direction){
                    cop1_next++;
                }
                else{
                    cop1_next--;
                }
        }
        if(cop2.position == *cop2_next) {
            if(cop2.direction) {
                cop2_next++;
            }
            else {
                cop2_next--;
            }
        }
        time--;
    }
    cout << cop1.position << endl;
    cout << cop2.position << endl;
}
