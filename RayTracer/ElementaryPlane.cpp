//
//  ElementaryPlane.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 22.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "ElementaryPlane.hpp"
#include <utility>
#include <cmath>

ElementaryPlane::ElementaryPlane():
    __type(xType), __value(){}

ElementaryPlane::ElementaryPlane(const PlaneType& _type, const double& _value):
    __type(_type), __value(_value){}

ElementaryPlane::ElementaryPlane(PlaneType&& _type, double&& _value):
    __type(std::move(_type)), __value(std::move(_value)){}

double ElementaryPlane::put(const Point3D& p) const
{
    if(__type == xType){
        return p.x() - __value;
    }
    if(__type == yType){
        return p.y() - __value;
    }
    if(__type == zType){
        return p.z() - __value;
    }
    return 0;
}

bool ElementaryPlane::crossing(const Ray& ray, Point3D& x) const
{
    double dist = put(ray.startPoint());
    int coef = (dist > 0) - (dist < 0);
    Point3D n = normal();
    if(ray.rail() * n * coef >= 0){
        return false;
    }
    x = ray.rail();
    x *= fabs(dist/(x * n));
    x += ray.startPoint();
    return true;
}

Point3D ElementaryPlane::normal() const
{
    if(__type == xType){
        return Point3D(1, 0, 0);
    }
    if(__type == yType){
        return Point3D(0, 1, 0);
    }
    if(__type == zType){
        return Point3D(0, 0, 1);
    }
    return Point3D(0, 0, 0);
}

const PlaneType& ElementaryPlane::type() const{return __type;}
const double& ElementaryPlane::value() const{return __value;}
void ElementaryPlane::type(const PlaneType& _type){__type = _type;}
void ElementaryPlane::value(const double& _value){__value = _value;}
void ElementaryPlane::type(PlaneType&& _type){__type = std::move(_type);}
void ElementaryPlane::value(double&& _value){__value = std::move(_value);}