//
//  Polygon.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 22.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "Polygon.hpp"
#include "Multiangle.hpp"
#include "Sphere.hpp"
#include <cstdarg>
#include <vector>
Polygon::~Polygon()
{}

Polygon::Polygon(RGB&& _rgb, double&& _reflect, double&& _refract,
                 objectType type, ...):
__color(std::move(_rgb)), __reflect(std::move(_reflect)), __refract(std::move(_refract))
{
    va_list ap;
    va_start(ap, type);
    object = NULL;
    if(type == triangle){
        double xA, yA, zA;
        std::vector<Point3D> points(3);
        xA = va_arg(ap, double);
        yA = va_arg(ap, double);
        zA = va_arg(ap, double);
        points[0] = Point3D(std::move(xA), std::move(yA), std::move(zA));
        xA = va_arg(ap, double);
        yA = va_arg(ap, double);
        zA = va_arg(ap, double);
        points[1] = Point3D(std::move(xA), std::move(yA), std::move(zA));
        xA = va_arg(ap, double);
        yA = va_arg(ap, double);
        zA = va_arg(ap, double);
        points[2] = Point3D(std::move(xA), std::move(yA), std::move(zA));
        object = new Multiangle(std::move(points));
    }
    if(type == sphere){
        double xS, yS, zS, radius;
        xS = va_arg(ap, double);
        yS = va_arg(ap, double);
        zS = va_arg(ap, double);
        radius = va_arg(ap, double);
        object = new Sphere(Point3D(std::move(xS), std::move(yS), std::move(zS)),
                         std::move(radius));
    }
    if(type == quadrangle){
        double xA, yA, zA;
        std::vector<Point3D> points(4);
        xA = va_arg(ap, double);
        yA = va_arg(ap, double);
        zA = va_arg(ap, double);
        points[0] = Point3D(std::move(xA), std::move(yA), std::move(zA));
        xA = va_arg(ap, double);
        yA = va_arg(ap, double);
        zA = va_arg(ap, double);
        points[1] = Point3D(std::move(xA), std::move(yA), std::move(zA));
        xA = va_arg(ap, double);
        yA = va_arg(ap, double);
        zA = va_arg(ap, double);
        points[2] = Point3D(std::move(xA), std::move(yA), std::move(zA));
        xA = va_arg(ap, double);
        yA = va_arg(ap, double);
        zA = va_arg(ap, double);
        points[3] = Point3D(std::move(xA), std::move(yA), std::move(zA));
        object = new Multiangle(std::move(points));
    }
    va_end(ap);
}

Polygon::Polygon(const Polygon& polygon):
    __color(polygon.__color),
    __refract(polygon.__refract),
    __reflect(polygon.__reflect),
    object(polygon.object){}

Polygon::Polygon(Polygon&& polygon):
    __color(std::move(polygon.__color)),
    __refract(std::move(polygon.__refract)),
    __reflect(std::move(polygon.__reflect)),
    object(std::move(polygon.object)){}

Polygon::Polygon():
    object(NULL), __color(), __reflect(), __refract(){}

bool Polygon::crossing(const Ray& ray, Point3D& x) const
{
    return object->crossing(ray, x);
}

Point3D Polygon::normal(const Point3D& x) const
{
    return object->normal(x);
}

Box Polygon::box() const
{
    return object->box();
}

void Polygon::free() const
{
    delete object;
}

const RGB& Polygon::color()const{return __color;}
const double& Polygon::reflect() const{return __reflect;}
const double& Polygon::refract() const{return __refract;}
void Polygon::color(const RGB& _color){__color = _color;}
void Polygon::reflect(const double& _reflect){__reflect = _reflect;}
void Polygon::refract(const double& _refract){__refract = _refract;}
void Polygon::color(RGB&& _color){__color = std::move(_color);}
void Polygon::reflect(double&& _reflect){__reflect = std::move(_reflect);}
void Polygon::refract(double&& _refract){__refract = std::move(_refract);}
