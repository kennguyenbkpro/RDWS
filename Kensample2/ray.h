#ifndef RAY_H
#define RAY_H
#include <flightpoint.h>

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
};

#endif // RAY_H
