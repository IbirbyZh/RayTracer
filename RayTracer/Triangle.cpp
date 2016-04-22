//
//  Triangle.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 07.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "Triangle.hpp"
#include "Plane.hpp"
#include <utility>
#include <algorithm>

Triangle::Triangle():
    __A(), __B(), __C(){}

Triangle::Triangle(const Point3D& _A, const Point3D& _B, const Point3D& _C,
                   const RGB& _color,
                   const double& _reflect, const double& _refract):
    __A(_A), __B(_B), __C(_C)
{
    __color = _color;
    __reflect = _reflect;
    __refract = _refract;
}

Triangle::Triangle(Point3D&& _A, Point3D&& _B, Point3D&& _C,
         RGB&& _color,
         double&& _reflect, double&& _refract):
__A(std::move(_A)), __B(std::move(_B)), __C(std::move(_C))
{
    __color = std::move(_color);
    __reflect = std::move(_reflect);
    __refract = std::move(_refract);
}

Triangle::~Triangle(){}

bool Triangle::crossing(const Ray& ray, Point3D& x) const
{
    Plane plane(normal(), __A);
    if (!plane.crossing(ray, x)){
        return false;
    }
    Point3D n = normal();
    return (((__B - __A) % (x - __B)) * (n) >= 0 &&
            ((__C - __B) % (x - __C)) * (n) >= 0 &&
            ((__A - __C) % (x - __A)) * (n) >= 0);
}

Point3D Triangle::normal(const Point3D& x) const
{
    return ((__B - __A) % (__C - __B)).normalize();
}

Box Triangle::box() const
{
    double xMax(std::max(__A.x(), std::max(__B.x(), __C.x())));
    double yMax(std::max(__A.y(), std::max(__B.y(), __C.y())));
    double zMax(std::max(__A.z(), std::max(__B.z(), __C.z())));
    double xMin(std::min(__A.x(), std::min(__B.x(), __C.x())));
    double yMin(std::min(__A.y(), std::min(__B.y(), __C.y())));
    double zMin(std::min(__A.z(), std::min(__B.z(), __C.z())));
    return Box(Point3D(std::move(xMin), std::move(yMin), std::move(zMin)),
               Point3D(std::move(xMax), std::move(yMax), std::move(zMax)));
}

const Point3D& Triangle::A() const{return __A;}
const Point3D& Triangle::B() const{return __B;}
const Point3D& Triangle::C() const{return __C;}
void Triangle::A(const Point3D& _A){__A = _A;}
void Triangle::B(const Point3D& _B){__B = _B;}
void Triangle::C(const Point3D& _C){__C = _C;}
void Triangle::A(Point3D&& _A){__A = std::move(_A);}
void Triangle::B(Point3D&& _B){__B = std::move(_B);}
void Triangle::C(Point3D&& _C){__C = std::move(_C);}
