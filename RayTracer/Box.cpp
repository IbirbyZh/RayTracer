//
//  Box.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 17.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "Box.hpp"
#include "ElementaryPlane.hpp"
#include <utility>

Box::Box():
    __A(), __B(){}

Box::Box(const Point3D& _A, const Point3D& _B):
    __A(_A), __B(_B){}

Box::Box(Point3D&& _A, Point3D&& _B):
    __A(std::move(_A)), __B(std::move(_B)){}

Box::~Box(){}

bool Box::crossing(const Ray& ray, Point3D& x) const
{
    double dist = MAX_DISTANCE;
    Point3D ans;
    if(ElementaryPlane(xType, __A.x()).crossing(ray, ans)){
        if(isInTube(ans, __A, __B, xType)){
            if((ans - ray.startPoint()).length2() < dist){
                x = std::move(ans);
                dist = (x - ray.startPoint()).length2();
            }
        }
    }
    if(ElementaryPlane(xType, __B.x()).crossing(ray, ans)){
        if(isInTube(ans, __A, __B, xType)){
            if((ans - ray.startPoint()).length2() < dist){
                x = std::move(ans);
                dist = (x - ray.startPoint()).length2();
            }
        }
    }
    if(ElementaryPlane(yType, __A.y()).crossing(ray, ans)){
        if(isInTube(ans, __A, __B, yType)){
            if((ans - ray.startPoint()).length2() < dist){
                x = std::move(ans);
                dist = (x - ray.startPoint()).length2();
            }
        }
    }
    if(ElementaryPlane(yType, __B.y()).crossing(ray, ans)){
        if(isInTube(ans, __A, __B, yType)){
            if((ans - ray.startPoint()).length2() < dist){
                x = std::move(ans);
                dist = (x - ray.startPoint()).length2();
            }
        }
    }
    if(ElementaryPlane(zType, __A.z()).crossing(ray, ans)){
        if(isInTube(ans, __A, __B, zType)){
            if((ans - ray.startPoint()).length2() < dist){
                x = std::move(ans);
                dist = (x - ray.startPoint()).length2();
            }
        }
    }
    if(ElementaryPlane(zType, __B.z()).crossing(ray, ans)){
        if(isInTube(ans, __A, __B, zType)){
            if((ans - ray.startPoint()).length2() < dist){
                x = std::move(ans);
                dist = (x - ray.startPoint()).length2();
            }
        }
    }
    return dist + 1 < MAX_DISTANCE;
}

int Box::doubleCrossing(const Ray& ray, Point3D& x, Point3D& y) const
{
    double dist = MAX_DISTANCE, dist2 = MAX_DISTANCE;
    Point3D ans;
    if(ElementaryPlane(xType, __A.x()).crossing(ray, ans)){
        if(isInTube(ans, __A, __B, xType)){
            if((ans - ray.startPoint()).length2() < dist){
                y = std::move(x);
                dist2 = dist;
                x = std::move(ans);
                dist = (x - ray.startPoint()).length2();
            }else{
                if((ans - ray.startPoint()).length2() < dist2){
                    y = std::move(ans);
                    dist2 = (y - ray.startPoint()).length2();
                }
            }
        }
    }
    if(ElementaryPlane(xType, __B.x()).crossing(ray, ans)){
        if(isInTube(ans, __A, __B, xType)){
            if((ans - ray.startPoint()).length2() < dist){
                y = std::move(x);
                dist2 = dist;
                x = std::move(ans);
                dist = (x - ray.startPoint()).length2();
            }else{
                if((ans - ray.startPoint()).length2() < dist2){
                    y = std::move(ans);
                    dist2 = (y - ray.startPoint()).length2();
                }
            }
        }
    }
    if(ElementaryPlane(yType, __A.y()).crossing(ray, ans)){
        if(isInTube(ans, __A, __B, yType)){
            if((ans - ray.startPoint()).length2() < dist){
                y = std::move(x);
                dist2 = dist;
                x = std::move(ans);
                dist = (x - ray.startPoint()).length2();
            }else{
                if((ans - ray.startPoint()).length2() < dist2){
                    y = std::move(ans);
                    dist2 = (y - ray.startPoint()).length2();
                }
            }
        }
    }
    if(ElementaryPlane(yType, __B.y()).crossing(ray, ans)){
        if(isInTube(ans, __A, __B, yType)){
            if((ans - ray.startPoint()).length2() < dist){
                y = std::move(x);
                dist2 = dist;
                x = std::move(ans);
                dist = (x - ray.startPoint()).length2();
            }else{
                if((ans - ray.startPoint()).length2() < dist2){
                    y = std::move(ans);
                    dist2 = (y - ray.startPoint()).length2();
                }
            }
        }
    }
    if(ElementaryPlane(zType, __A.z()).crossing(ray, ans)){
        if(isInTube(ans, __A, __B, zType)){
            if((ans - ray.startPoint()).length2() < dist){
                y = std::move(x);
                dist2 = dist;
                x = std::move(ans);
                dist = (x - ray.startPoint()).length2();
            }else{
                if((ans - ray.startPoint()).length2() < dist2){
                    y = std::move(ans);
                    dist2 = (y - ray.startPoint()).length2();
                }
            }
        }
    }
    if(ElementaryPlane(zType, __B.z()).crossing(ray, ans)){
        if(isInTube(ans, __A, __B, zType)){
            if((ans - ray.startPoint()).length2() < dist){
                y = std::move(x);
                dist2 = dist;
                x = std::move(ans);
                dist = (x - ray.startPoint()).length2();
            }else{
                if((ans - ray.startPoint()).length2() < dist2){
                    y = std::move(ans);
                    dist2 = (y - ray.startPoint()).length2();
                }
            }
        }
    }
    return static_cast<int>(dist + 1 < MAX_DISTANCE) + static_cast<int>(dist2 + 1 < MAX_DISTANCE);
}

const Point3D& Box::A() const{return __A;}
const Point3D& Box::B() const{return __B;}
void Box::A(const Point3D& _A){__A = _A;}
void Box::B(const Point3D& _B){__B = _B;}
void Box::A(Point3D&& _A){__A = std::move(_A);}
void Box::B(Point3D&& _B){__B = std::move(_B);}

bool Box::isInTube(const Point3D& S, const Point3D& Min, const Point3D& Max, PlaneType type)
{
    if (type == xType){
        return (Min.y() <= S.y() && Max.y() >= S.y() && Min.z() <= S.z() && Max.z() >= S.z());
    }
    if (type == yType){
        return (Min.x() <= S.x() && Max.x() >= S.x() && Min.z() <= S.z() && Max.z() >= S.z());
    }
    if (type == zType){
        return (Min.y() <= S.y() && Max.y() >= S.y() && Min.x() <= S.x() && Max.x() >= S.x());
    }
    return false;
}

bool Box::isIn(const Point3D& S) const
{
    return (__A.x() <= S.x() && __B.x() >= S.x() &&
            __A.y() <= S.y() && __B.y() >= S.y() &&
            __A.z() <= S.z() && __B.z() >= S.z());
}

