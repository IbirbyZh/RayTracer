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
#include <cmath>
#include <iostream>

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
    /*double dist = MAX_DISTANCE, dist2 = MAX_DISTANCE;
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
    return static_cast<int>(dist + 1 < MAX_DISTANCE) + static_cast<int>(dist2 + 1 < MAX_DISTANCE);*/
    double t[3][2];
    const Point3D& startPoint = ray.startPoint();
    Point3D rail = ray.rail();
    findT(__A.x(), __B.x(), startPoint.x(), rail.x(), t[0][0], t[0][1]);
    findT(__A.y(), __B.y(), startPoint.y(), rail.y(), t[1][0], t[1][1]);
    findT(__A.z(), __B.z(), startPoint.z(), rail.z(), t[2][0], t[2][1]);
    double tans[2];
    tans[0] = -MAX_DISTANCE;
    tans[1] = MAX_DISTANCE;
    for(int i = 0; i < 3; ++i){
        tans[0] = fmax(tans[0], t[i][0]);
        tans[1] = fmin(tans[1], t[i][1]);
    }
    if(tans[0] >= tans[1] || tans[1] < 0){
        return 0;
    }
    if (tans[0] < 0){
        rail *= tans[1];
        x = startPoint + rail;
        return 1;
    }
    rail *= tans[0];
    x = startPoint + rail;
    rail *= tans[1] / tans[0];
    y = startPoint + rail;
    //std::cout << tans[0] << ' ' <<tans[1] <<'\n';
    return 2;
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
    bool inX, inY, inZ;
    /*
    inX = __A.x() - epsilon <= S.x() && __B.x() + epsilon >= S.x();
    inY = __A.y() - epsilon <= S.y() && __B.y() + epsilon >= S.y();
    inZ = __A.z() - epsilon <= S.z() && __B.z() + epsilon >= S.z();
    */
    inX = __A.x() <= S.x() && __B.x() >= S.x();
    inY = __A.y() <= S.y() && __B.y() >= S.y();
    inZ = __A.z() <= S.z() && __B.z() >= S.z();
    
    
    return inX && inY && inZ;
}

void Box::findT(const double& l, const double& r, const double& x,
                const double& a, double& t1, double& t2)
{
    if (a == 0){
        if(l <= x && r >= x){
            t1 = -MAX_DISTANCE;
            t2 = MAX_DISTANCE;
        }else{
            t1 = 1;
            t2 = -1;
        }
    }else{
        t1 = (l - x) / a;
        t2 = (r - x) / a;
        if(t1 > t2){
            std::swap(t1, t2);
        }
    }
}
