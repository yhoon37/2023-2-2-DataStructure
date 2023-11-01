#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <numeric>
using namespace std;

struct Point {
	int x;
	int y;
};

int SIZE;                // 입력 point의 개수
int CHECKTIME;           // 로봇 위치를 확인할 시간
vector<Point> points1;   // 꼭짓점 point (robot1)
vector<Point> points2;   // 꼭짓점 point (robot2)
vector<int> distances1;  // 각 꼭짓점 사이의 거리 (robot1)
vector<int> distances2;  // 각 꼭짓점 사이의 거리 (robot2)
Point robot1, robot2;    // 로봇의 위치
int total, halfRobot;    // 전체 둘레, 로봇 사이의 거리 / 2

void get() {

	cin >> SIZE;

	for (int i = 0; i < SIZE; i++) {
		Point point;
		cin >> point.x >> point.y;
		points1.push_back(point);
	}

	cin >> CHECKTIME;
}

void set() {

	int halfSize = (SIZE / 2);

	points1.push_back(points1[0]);
	points2 = { points1.begin(), points1.end() };
	reverse(points2.begin(), points2.end());
	rotate(points2.begin(), points2.begin() + halfSize + 1, points2.end());
	points2.erase(points2.begin() + halfSize);

	for (int i = 0; i < SIZE; i++) {
		distances1.push_back(abs(points1[i + 1].x - points1[i].x) + abs(points1[i + 1].y - points1[i].y));
	}

	distances2 = { distances1.begin(), distances1.end() };
	reverse(distances2.begin(), distances2.end());
	rotate(distances2.begin(), distances2.begin() + halfSize + 1, distances2.end());

	total = accumulate(distances1.begin(), distances1.end(), 0);
	halfRobot = accumulate(distances1.begin(), distances1.begin() + halfSize - 1, 0) / 2;

}

void moveRobot(Point& robot, const vector<int>& distances, const vector<Point>& points) {

	CHECKTIME %= total;
	int leftTime = CHECKTIME;
	int i = 0;
	while (leftTime > distances[i]) {
		leftTime -= distances[i];
		i++;
	}
	robot = points[i];
	if (robot.x == points[i + 1].x) { robot.y += (robot.y < points[i + 1].y) ? leftTime : -leftTime; }
	else { robot.x += (robot.x < points[i + 1].x) ? leftTime : -leftTime; }

}

int getMeetTime() {
	int meet;
	if (CHECKTIME < halfRobot) { meet = 0; }
	else if (CHECKTIME < halfRobot + total / 2) { meet = 1; }
	else { meet = 2; }
	return meet;
}

void changeRobot() {
	Point tmp = robot1;
	robot1 = robot2;
	robot2 = tmp;
}

void printRobot() {
	cout << robot1.x << " " << robot1.y << endl;
	cout << robot2.x << " " << robot2.y << endl;
}

int main() {
	get();
	set();
	moveRobot(robot1, distances1, points1); // 시계
	moveRobot(robot2, distances2, points2); // 반시계

	if (getMeetTime() % 2 == 0) {
        printRobot();
    }
	else {
		changeRobot();
		printRobot();
	}

}