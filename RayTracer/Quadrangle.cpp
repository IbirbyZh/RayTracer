//
//  Quadrangle.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 11.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "Quadrangle.hpp"
#include "Triangle.hpp"
#include "Plane.hpp"
#include <utility>
#include <algorithm>

Quadrangle::Quadrangle():
    __A(), __B(), __C(), __D(){}

Quadrangle::Quadrangle(const Point3D& _A, const Point3D& _B,
                       const Point3D& _C, const Point3D& _D,
                       const RGB& _color,
                       const double& _reflect, const double& _refract):
    __A(_A), __B(_B), __C(_C), __D(_D)
{
    __color = _color;
    __reflect = _reflect;
    __refract = _refract;
}

Quadrangle::Quadrangle(Point3D&& _A, Point3D&& _B,
                       Point3D&& _C, Point3D&& _D,
                       RGB&& _color,
                       double&& _reflect, double&& _refract):
__A(std::move(_A)), __B(std::move(_B)), __C(std::move(_C)), __D(std::move(_D))
{
    __color = std::move(_color);
    __reflect = std::move(_reflect);
    __refract = std::move(_refract);
}

Quadrangle::~Quadrangle(){}

bool Quadrangle::crossing(const Ray& ray, Point3D& x) const
{
    Plane plane(normal(), __A);
    if (!plane.crossing(ray, x)){
        return false;
    }
    Point3D n = normal();
    return (((__B - __A) % (x - __B)) * (n) >= 0 &&
            ((__C - __B) % (x - __C)) * (n) >= 0 &&
            ((__D - __C) % (x - __D)) * (n) >= 0 &&
            ((__A - __D) % (x - __A)) * (n) >= 0);
}

Point3D Quadrangle::normal(const Point3D& x) const
{
    return ((__B - __A) % (__C - __B)).normalize();
}

Box Quadrangle::box() const
{
    double xMax(std::max(__A.x(), std::max(__B.x(), std::max(__C.x(), __D.x()))));
    double yMax(std::max(__A.y(), std::max(__B.y(), std::max(__C.y(), __D.y()))));
    double zMax(std::max(__A.z(), std::max(__B.z(), std::max(__C.z(), __D.z()))));
    double xMin(std::min(__A.x(), std::min(__B.x(), std::min(__C.x(), __D.x()))));
    double yMin(std::min(__A.y(), std::min(__B.y(), std::min(__C.y(), __D.y()))));
    double zMin(std::min(__A.z(), std::min(__B.z(), std::min(__C.z(), __D.z()))));
    return Box(Point3D(std::move(xMin), std::move(yMin), std::move(zMin)),
               Point3D(std::move(xMax), std::move(yMax), std::move(zMax)));
}

const Point3D& Quadrangle::A() const{return __A;}
const Point3D& Quadrangle::B() const{return __B;}
const Point3D& Quadrangle::C() const{return __C;}
const Point3D& Quadrangle::D() const{return __D;}
void Quadrangle::A(const Point3D& _A){__A = _A;}
void Quadrangle::B(const Point3D& _B){__B = _B;}
void Quadrangle::C(const Point3D& _C){__C = _C;}
void Quadrangle::D(const Point3D& _D){__D = _D;}
void Quadrangle::A(Point3D&& _A){__A = std::move(_A);}
void Quadrangle::B(Point3D&& _B){__B = std::move(_B);}
void Quadrangle::C(Point3D&& _C){__C = std::move(_C);}
void Quadrangle::D(Point3D&& _D){__D = std::move(_D);}

