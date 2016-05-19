//
//  Point3D.cpp
//  RayTraser
//
//  Created by Шишкин Евгений on 07.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "Point3D.hpp"
#include <utility>
#include <cmath>

Point3D::Point3D():
    __x(), __y(), __z(){}

Point3D::Point3D(const point_t& _x, const point_t& _y, const point_t& _z):
    __x(_x), __y(_y), __z(_z){}

Point3D::Point3D(point_t&& _x, point_t&& _y, point_t&& _z):
    __x(std::move(_x)), __y(std::move(_y)), __z(std::move(_z)){}

Point3D::Point3D(const Point3D& p):
    __x(p.__x), __y(p.__y), __z(p.__z){}

Point3D::Point3D(Point3D&& p):
    __x(std::move(p.__x)), __y(std::move(p.__y)), __z(std::move(p.__z)){}

const Point3D& Point3D::operator = (const Point3D& p)
{
    __x = p.__x;
    __y = p.__y;
    __z = p.__z;
    return (*this);
}

const Point3D& Point3D::operator = (Point3D&& p)
{
    __x = std::move(p.__x);
    __y = std::move(p.__y);
    __z = std::move(p.__z);
    return (*this);
}

const Point3D::point_t& Point3D::x() const{return __x;}
const Point3D::point_t& Point3D::y() const{return __y;}
const Point3D::point_t& Point3D::z() const{return __z;}

void Point3D::x(const point_t& _x){__x = _x;}
void Point3D::x(point_t&& _x){__x = std::move(_x);}
void Point3D::y(const point_t& _y){__y = _y;}
void Point3D::y(point_t&& _y){__y = std::move(_y);}
void Point3D::z(const point_t& _z){__z = _z;}
void Point3D::z(point_t&& _z){__z = std::move(_z);}

const Point3D& Point3D::operator += (const Point3D& p)
{
    __x += p.__x;
    __y += p.__y;
    __z += p.__z;
    return (*this);
}

const Point3D& Point3D::operator -= (const Point3D& p)
{
    __x -= p.__x;
    __y -= p.__y;
    __z -= p.__z;
    return (*this);
}

const Point3D& Point3D::operator *= (const point_t& m)
{
    __x *= m;
    __y *= m;
    __z *= m;
    return (*this);
}

const Point3D& Point3D::operator /= (const point_t& m)
{
    __x /= m;
    __y /= m;
    __z /= m;
    return (*this);
}

Point3D Point3D::operator + (const Point3D& p) const
{return Point3D(__x + p.__x, __y + p.__y, __z + p.__z);}

Point3D& Point3D::operator + (Point3D&& p) const
{
    p.__x += __x;
    p.__y += __y;
    p.__z += __z;
    return p;
}

Point3D Point3D::operator - (const Point3D& p) const
{return Point3D(__x - p.__x, __y - p.__y, __z - p.__z);}

Point3D& Point3D::operator - (Point3D&& p) const
{
    p *= -1;
    p.__x += __x;
    p.__y += __y;
    p.__z += __z;
    return p;
}

Point3D::point_t Point3D::operator *(const Point3D& p) const
{
    return __x * p.__x + __y * p.__y + __z * p.__z;
}
Point3D::point_t Point3D::operator *(Point3D&& p) const
{
    return __x * p.__x + __y * p.__y + __z * p.__z;
}

Point3D Point3D::operator %(const Point3D& p) const
{
    return Point3D(__y * p.__z - __z * p.__y,
                   __z * p.__x - __x * p.__z,
                   __x * p.__y - __y * p.__x);
}
Point3D& Point3D::operator %(Point3D&& p) const
{
    point_t px(std::move(p.__x)), py(std::move(p.__y)), pz(std::move(p.__z));
    p.__x = __y * pz - __z * py;
    p.__y = __z * px - __x * pz;
    p.__z = __x * py - __y * px;
    return p;
}

Point3D::point_t Point3D::length2() const
{
    return __x * __x + __y * __y + __z * __z;
}

Point3D::point_t Point3D::length() const
{
    return sqrt(__x * __x + __y * __y + __z * __z);
}

const Point3D& Point3D::normalize()
{
    point_t len = sqrt(length2());
    (*this) /= len;
    return (*this);
}
