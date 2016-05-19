//
//  Scene.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 18.05.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "Scene.hpp"
#include <utility>

Scene::Scene():
__origin(), __topLeft(), __right(), __down(){}

Scene::Scene(const Point3D& _origin, const Point3D& _topLeft,
             const Point3D& _right, const Point3D& _down):
__origin(_origin), __topLeft(_topLeft), __right(_right), __down(_down){}

Scene::Scene(Point3D&& _origin, Point3D&& _topLeft,
             Point3D&& _right, Point3D&& _down):
__origin(std::move(_origin)), __topLeft(std::move(_topLeft)), __right(std::move(_right)), __down(std::move(_down)){}

void Scene::operator =(Scene&& s)
{
    __origin = (std::move(s.__origin));
    __topLeft = (std::move(s.__topLeft));
    __right = (std::move(s.__right));
    __down = (std::move(s.__down));
}

const Point3D& Scene::origin() const{return  __origin;}
const Point3D& Scene::topLeft() const{return __topLeft;}
const Point3D& Scene::right() const{return  __right;}
const Point3D& Scene::down() const{return __down;}

void Scene::toStart()
{
    i = -1;
}

bool Scene::next(Point3D &p)
{
    if(i + 1 < RIGHT_MAX * DOWN_MAX){
        ++i;
        Point3D s = __topLeft;
        Point3D x = __right;
        Point3D y = __down;
        x *= static_cast<double>(i % RIGHT_MAX) / RIGHT_MAX;
        y *= static_cast<double>(i / RIGHT_MAX) / DOWN_MAX;
        p = s + x + y;
        return  true;
    }else{
        return false;
    }
}
