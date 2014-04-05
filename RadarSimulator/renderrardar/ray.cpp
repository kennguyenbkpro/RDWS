#include "ray.h"

Ray::Ray()
{
}

Ray::Ray(float alpha, int p[]){
    this->alpha = alpha;
    this->p = p;
}

int Ray::getPoint(int i){
    int r = this->p[i];
    return r;
}

Ray::~Ray(){
    delete [] p;
}
