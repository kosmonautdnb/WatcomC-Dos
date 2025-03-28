#ifndef __POINT_HPP__
#define __POINT_HPP__

class Point {
public:
        Point() {x = 0; y = 0;}
        Point(int _x, int _y) {x = _x; y = _y;}
        int x,y;
};

Point operator+(const Point &a, const Point &b);
Point operator-(const Point &a, const Point &b);

#endif //__POINT_HPP__