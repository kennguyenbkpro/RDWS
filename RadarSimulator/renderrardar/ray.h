#ifndef RAY_H
#define RAY_H
#include <renderrardar/flightpoint.h>

class Ray
{
public:
    Ray();
    Ray(float alpha, int p[]);
    ~Ray();

public:
    float alpha;
    int  *p;
    int getPoint(int i);
    int size;
};

#endif // RAY_H
