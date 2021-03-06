//
//  IObject.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 07.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "IObject.hpp"
#include "Multiangle.hpp"
#include "Sphere.hpp"
#include <cstdarg>
#include <utility>

IObject* createObject(objectType type, ...)
{
    va_list ap;
    va_start(ap, type);
    IObject* ans = NULL;
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
        ans = new Multiangle(std::move(points));
    }
    if(type == sphere){
        double xS, yS, zS, radius;
        xS = va_arg(ap, double);
        yS = va_arg(ap, double);
        zS = va_arg(ap, double);
        radius = va_arg(ap, double);
        ans = new Sphere(Point3D(std::move(xS), std::move(yS), std::move(zS)),
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
        ans = new Multiangle(std::move(points));
    }
    va_end(ap);
    return ans;
}
