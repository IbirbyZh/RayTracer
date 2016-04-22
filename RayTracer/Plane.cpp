//
//  Plane.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 07.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "Plane.hpp"
#include <utility>
#include <cmath>

Plane::Plane():
    __A(), __B(), __C(), __D(){}

Plane::Plane(const double& _A, const double& _B, const double& _C, const double& _D):
    __A(_A), __B(_B), __C(_C), __D(_D)
{
    double coef = sqrt(__A * __A + __B * __B + __C * __C);
    __A /= coef;
    __B /= coef;
    __C /= coef;
    __D /= coef;
}

Plane::Plane(double&& _A, double&& _B, double&& _C, double&& _D):
    __A(std::move(_A)), __B(std::move(_B)), __C(std::move(_C)), __D(std::move(_D))
{
    double coef = sqrt(__A * __A + __B * __B + __C * __C);
    __A /= coef;
    __B /= coef;
    __C /= coef;
    __D /= coef;
}

Plane::Plane(Point3D && n, const Point3D& X)
{
    __A = std::move(n.x());
    __B = std::move(n.y());
    __C = std::move(n.z());
    __D = 0;
    __D = -put(X);
}

const double& Plane::A() const{return __A;}
const double& Plane::B() const{return __B;}
const double& Plane::C() const{return __C;}
const double& Plane::D() const{return __D;}

void Plane::A(const double& _A){__A = _A;}
void Plane::B(const double& _B){__B = _B;}
void Plane::C(const double& _C){__C = _C;}
void Plane::D(const double& _D){__D = _D;}

void Plane::A(double&& _A){__A = std::move(_A);}
void Plane::B(double&& _B){__B = std::move(_B);}
void Plane::C(double&& _C){__C = std::move(_C);}
void Plane::D(double&& _D){__D = std::move(_D);}

double Plane::put(const Point3D& p) const
{
    return __A * p.x() + __B * p.y() + __C * p.z() + __D;
}

bool Plane::crossing(const Ray& ray, Point3D &x) const
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

Point3D Plane::normal() const
{
    return Point3D(__A, __B, __C);
}
