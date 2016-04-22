//
//  IObject.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 07.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "IObject.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "Quadrangle.hpp"
#include <cstdarg>
#include <utility>

IObject* createObject(objectType type, double r, double g, double b,
                      double reflect, double refract, ...)
{
    va_list ap;
    va_start(ap, refract);
    IObject* ans = NULL;
    if(type == triangle){
        double xA, yA, zA, xB, yB, zB, xC, yC, zC;
        xA = va_arg(ap, double);
        yA = va_arg(ap, double);
        zA = va_arg(ap, double);
        
        xB = va_arg(ap, double);
        yB = va_arg(ap, double);
        zB = va_arg(ap, double);
        
        xC = va_arg(ap, double);
        yC = va_arg(ap, double);
        zC = va_arg(ap, double);
        
        ans = new Triangle(Point3D(std::move(xA), std::move(yA), std::move(zA)),
                           Point3D(std::move(xB), std::move(yB), std::move(zB)),
                           Point3D(std::move(xC), std::move(yC), std::move(zC)),
                           RGB(std::move(r), std::move(g), std::move(b)),
                           std::move(reflect), std::move(refract));
    }
    if(type == sphere){
        double xS, yS, zS, radius;
        xS = va_arg(ap, double);
        yS = va_arg(ap, double);
        zS = va_arg(ap, double);
        radius = va_arg(ap, double);
        ans = new Sphere(Point3D(std::move(xS), std::move(yS), std::move(zS)),
                         std::move(radius),
                         RGB(std::move(r), std::move(g), std::move(b)),
                         std::move(reflect), std::move(refract));
    }
    if(type == quadrangle){
        double xA, yA, zA, xB, yB, zB, xC, yC, zC, xD, yD, zD;
        xA = va_arg(ap, double);
        yA = va_arg(ap, double);
        zA = va_arg(ap, double);
        
        xB = va_arg(ap, double);
        yB = va_arg(ap, double);
        zB = va_arg(ap, double);
        
        xC = va_arg(ap, double);
        yC = va_arg(ap, double);
        zC = va_arg(ap, double);
        
        xD = va_arg(ap, double);
        yD = va_arg(ap, double);
        zD = va_arg(ap, double);
        
        ans = new Quadrangle(Point3D(std::move(xA), std::move(yA), std::move(zA)),
                             Point3D(std::move(xB), std::move(yB), std::move(zB)),
                             Point3D(std::move(xC), std::move(yC), std::move(zC)),
                             Point3D(std::move(xD), std::move(yD), std::move(zD)),
                             RGB(std::move(r), std::move(g), std::move(b)),
                             std::move(reflect), std::move(refract));
    }
    va_end(ap);
    return ans;
}

const double& IObject::reflect() const{return __reflect;}
const double& IObject::refract() const{return __refract;}
const RGB& IObject::color() const{return __color;}

void IObject::reflect(const double& _reflect){__reflect = _reflect;}
void IObject::refract(const double& _refract){__refract = _refract;}
void IObject::color(const RGB& _color){__color = _color;}

void IObject::reflect(double&& _reflect){__reflect = std::move(_reflect);}
void IObject::refract(double&& _refract){__refract = std::move(_refract);}
void IObject::color(RGB&& _color){__color = std::move(_color);}
