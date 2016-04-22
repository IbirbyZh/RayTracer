//
//  LAB.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 08.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "LAB.hpp"
#include <utility>
#include <cmath>
#include <iostream>

LAB::LAB():
    __lab(){}

LAB::LAB(const double& _l, const double& _a, const double& _b):
    __lab(_l, _a, _b){}

LAB::LAB(double&& _l, double&& _a, double&& _b):
    __lab(std::move(_l), std::move(_a), std::move(_b)){}

LAB::LAB(const LAB& _color):
    __lab(_color.__lab){}

LAB::LAB(LAB&& _color):
    __lab(std::move(_color.__lab)){}

LAB::LAB(const XYZ& _color)
{
    double fx, fy, fz;
    fx = _color.x() / X;
    fy = _color.y() / Y;
    fz = _color.z() / Z;
    helper(fx);
    helper(fy);
    helper(fz);
    __lab = Point3D(116 * fy - 16, 500 * (fx - fy), 200 * (fy - fz));
}

LAB& LAB::operator = (const LAB& _color)
{
    __lab = _color.__lab;
    return *this;
}

LAB& LAB::operator = (LAB&& _color)
{
    __lab = std::move(_color.__lab);
    return *this;
}

const double& LAB::l() const{return __lab.x();}
const double& LAB::a() const{return __lab.y();}
const double& LAB::b() const{return __lab.z();}
const Point3D& LAB::lab() const{return __lab;}

void LAB::l(const double& _l){__lab.x(_l);}
void LAB::a(const double& _a){__lab.y(_a);}
void LAB::b(const double& _b){__lab.z(_b);}
void LAB::lab(const Point3D &_lab){__lab = _lab;}
void LAB::l(double&& _l){__lab.x(std::move(_l));}
void LAB::a(double&& _a){__lab.y(std::move(_a));}
void LAB::b(double&& _b){__lab.z(std::move(_b));}
void LAB::lab(Point3D &&_lab){__lab = std::move(_lab);}

void LAB::increaseLight(const double& intensity)
{
    double _intensity = std::fmin(100, intensity);
    double ___l = __lab.x();
    __lab.x(___l + (90 - ___l) / 100 * _intensity);
}

void LAB::helper(double& f)
{
    if(f > eps){
        f = pow(f, 1./3);
    }else{
        f = (f * k + 16) / 116;
    }
}
