//
//  Sphere.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 09.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "Sphere.hpp"
#include <utility>
#include <cmath>

Sphere::Sphere():
    __S(), __radius(){}

Sphere::Sphere(const Point3D& _S, const double& _radius,
               const RGB& _color,
               const double& _reflect, const double& _refract):
    __S(_S), __radius(_radius)
{
    __color = _color;
    __reflect = _reflect;
    __refract = _refract;
}

Sphere::Sphere(Point3D&& _S, double&& _radius,
               RGB&& _color,
               double&& _reflect, double&& _refract):
    __S(std::move(_S)), __radius(std::move(_radius))
{
    __color = std::move(_color);
    __reflect = std::move(_reflect);
    __refract = std::move(_refract);
}

Sphere::~Sphere(){}

bool Sphere::crossing(const Ray& ray, Point3D& x) const
{
    Point3D r(__S - ray.startPoint());
    double b = (__S - ray.startPoint()).length();
    double cos = r.normalize() * ray.rail();
    double D = __radius * __radius - (1 - cos * cos) * b * b;
    if (D < 0){
        return false;
    }
    D = sqrt(D);
    double len = b * cos;
    if(b >= __radius){
        D *= -1;
    }
    len += D;
    if (len < 0){
        return  false;
    }
    x = ray.rail();
    x *= len;
    x += ray.startPoint();
    return true;
}

Point3D Sphere::normal(const Point3D& x) const
{
    return (x - __S).normalize();
}

Box Sphere::box() const
{
    Point3D add(__radius, __radius, __radius);
    return Box(__S - add, __S + add);
}

const Point3D& Sphere::S() const{return __S;}
const double& Sphere::radius() const{return __radius;}

void Sphere::S(const Point3D& _S){__S = _S;}
void Sphere::radius(const double& _radius){__radius = _radius;}

void Sphere::S(Point3D&& _S){__S = std::move(_S);}
void Sphere::radius(double&& _radius){__radius = std::move(_radius);}

