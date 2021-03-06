//
//  Multiangle.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 07.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "Multiangle.hpp"
#include "Plane.hpp"
#include <utility>
#include <vector>
#include <algorithm>

Multiangle::Multiangle():
    __points(), n(){}

Multiangle::Multiangle(const std::vector<Point3D>& _points):
    __points(_points), n()
{
    initNorm();
}

Multiangle::Multiangle(std::vector<Point3D>&& _points):
    __points(std::move(_points)), n()
{
    initNorm();
}

void Multiangle::initNorm()
{
    if((__points[1] - __points[0]) * (__points[2] - __points[1]) < 0){
        n = ((__points[1] - __points[0]) % (__points[2] - __points[1])).normalize();
    }else{
        n = ((__points[2] - __points[1]) % (__points[3 % __points.size()] - __points[2])).normalize();
    }
}

Multiangle::~Multiangle(){}

bool Multiangle::crossing(const Ray& ray, Point3D& x) const
{
    Plane plane(normal(), __points[0]);
    if (!plane.crossing(ray, x)){
        return false;
    }
    bool ans = true;
    for(int i = 0; i < __points.size(); ++i){
        int next = (i + 1) % __points.size();
        ans = (((__points[next] - __points[i]) % (x - __points[next])) * n >= 0);
        if(!ans){
            return ans;
        }
    }
    return ans;
}

Point3D Multiangle::normal(const Point3D& x) const
{
    return n;
}

Box Multiangle::box() const
{
    
    double xMax, yMax, zMax, xMin, yMin, zMin;
    xMin = xMax = __points[0].x();
    yMin = yMax = __points[0].y();
    zMin = zMax = __points[0].z();
    for(int i = 1; i < __points.size(); ++i){
        xMin = std::min(xMin, __points[i].x());
        yMin = std::min(yMin, __points[i].y());
        zMin = std::min(zMin, __points[i].z());
        xMax = std::max(xMax, __points[i].x());
        yMax = std::max(yMax, __points[i].y());
        zMax = std::max(zMax, __points[i].z());
    }
    if(xMax - xMin < epsilon){
        xMax += epsilon;
        xMin -= epsilon;
    }
    if(yMax - yMin < epsilon){
        yMax += epsilon;
        yMin -= epsilon;
    }
    if(zMax - zMin < epsilon){
        zMax += epsilon;
        zMin -= epsilon;
    }
    return Box(Point3D(std::move(xMin), std::move(yMin), std::move(zMin)),
               Point3D(std::move(xMax), std::move(yMax), std::move(zMax)));
}

const std::vector<Point3D>& Multiangle::points() const{return __points;}
void Multiangle::points(const std::vector<Point3D>& _points){__points = _points;}
void Multiangle::points(std::vector<Point3D>&& _points){__points = std::move(_points);}
