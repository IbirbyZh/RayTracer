//
//  Ray.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 17.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "Ray.hpp"
#include <utility>

Ray::Ray():
__startPoint(), __rail(){}
                       
Ray::Ray(const Point3D& _startPoint, const Point3D& _rail):
__startPoint(_startPoint), __rail(_rail){}
                       
Ray::Ray(Point3D&& _startPoint, Point3D&& _rail):
__startPoint(std::move(_startPoint)), __rail(std::move(_rail)){}

void Ray::startPoint(const Point3D& _startPoint){__startPoint = _startPoint;}
void Ray::rail(const Point3D& _rail){__rail = _rail;}

void Ray::startPoint(Point3D&& _startPoint){__startPoint = std::move(_startPoint);}
void Ray::rail(Point3D&& _rail){__rail = std::move(_rail);}

const Point3D& Ray::startPoint() const{return __startPoint;}
const Point3D& Ray::rail() const{return __rail;}