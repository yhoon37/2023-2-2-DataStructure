#include <iostream>

using namespace std;

class Point {
public:
    Point(int x, int y) : x(x), y(y) {}
    int x;
    int y;

    bool operator ==(Point other){
        if(other.x == x && other.y == y) return true;
        else return false;
    }

private:
};

ostream& operator <<(ostream& os, Point p){
    os << p.x << " " << p.y;
    return os;
}

class Node {
public:
    Point data;
    Node* next = nullptr;
    Node* previous = nullptr;

    Node(Point data): data(data){}

private:
};

class CircleList {
public:
    Node* head = nullptr;
    int size=0;

    CircleList(){}//default

    void push_back(Node* new_node) {
        Node* current = head;
        if(current == nullptr) {
            head = new_node;
        }
        else {
            for(int i=0; i<size-1; i++) {
                current = current->next;
            }
            current->next = new_node;
            new_node->previous = current;
            new_node->next = head;
            head->previous = new_node;
        }
        size++;
    }

private:
};

class Cop {
public:
    Node* start;
    Node* next;

    Point position;
    bool direction;

    Cop(bool direction, Node* start) :
            direction(direction), start(start), position(start->data){next = start->next;}

    void go(){
        if(direction) {
            next = start->next;
        }
        else {
            next = start->previous;
        }

        if(next->data.x == position.x) {
            if(position.y < next->data.y){
                position.y++;
            }
            else {
                position.y--;
            }
        }
        else {
            if(position.x < next->data.x) {
                position.x++;
            }
            else {
                position.x--;
            }
        }
        if(next->data == position) {start = next;}
    }

    void change_direction() {direction =! direction;}

private:
};

int main() {
    int k, x, y, time;
    CircleList points;

    cin >> k;

    for(int i=0; i<k; i++) {
        cin >> x >> y;
        Point new_point = Point(x,y);
        points.push_back(new Node(new_point));
    }

    Node* cop2_start = points.head;
    for(int i=0; i < k/2 - 1; i++) cop2_start = cop2_start->next;

    Cop cop1(true, points.head);
    Cop cop2(false, cop2_start);

    cin >> time;

    while(time > 0) {
        cop1.go();
        cop2.go();

        if(cop1.position == cop2.position) {
            cop1.change_direction();
            cop2.change_direction();
            cop1.start = cop1.next;
            cop2.start = cop2.next;
        }

        time--;
    }
    cout << cop1.position << endl;
    cout << cop2.position << endl;


}
