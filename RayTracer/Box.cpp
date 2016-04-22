//
//  Box.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 17.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "Box.hpp"

#include <utility>

Box::Box():
    __A(), __B(){}

Box::Box(const Point3D& _A, const Point3D& _B):
    __A(_A), __B(_B){}

Box::Box(Point3D&& _A, Point3D&& _B):
    __A(std::move(_A)), __B(std::move(_B)){}

Box::~Box(){}

bool Box::crossing(const Point3D& x0, const Point3D& a, Point3D& x) const
{
    return true;
}

const Point3D& Box::A() const{return __A;}
const Point3D& Box::B() const{return __B;}
void Box::A(const Point3D& _A){__A = _A;}
void Box::B(const Point3D& _B){__B = _B;}
void Box::A(Point3D&& _A){__A = std::move(_A);}
void Box::B(Point3D&& _B){__B = std::move(_B);}
