//
//  XYZ.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 08.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "XYZ.hpp"
#include <utility>
#include <cmath>

XYZ::XYZ():
    __xyz(){}

XYZ::XYZ(const double& _x, const double& _y, const double& _z):
    __xyz(_x, _y, _z){}

XYZ::XYZ(double&& _x, double&& _y, double&& _z):
    __xyz(std::move(_x), std::move(_y), std::move(_z)){}

XYZ::XYZ(const XYZ& _color):
    __xyz(_color.__xyz){}

XYZ::XYZ(XYZ&& _color):
    __xyz(std::move(_color.__xyz)){}

XYZ::XYZ(const RGB& _color)
{
    double r = _color.r();
    double g = _color.g();
    double b = _color.b();
    helperRGB(r);
    helperRGB(g);
    helperRGB(b);
    Point3D rgb(r, g, b);
    __xyz = Point3D(rgb * MX, rgb * MY, rgb * MZ);
}

XYZ::XYZ(const LAB& _color)
{
    double fx, fy ,fz;
    fy = (_color.l() + 16) / 116;
    fz = fy -_color.b() / 200;
    fx = _color.a() / 500 + fy;
    helperLAB(fx);
    helperLAB(fy);
    helperLAB(fz);
    __xyz = Point3D(fx * X, fy * Y, fz * Z);
}

XYZ& XYZ::operator = (const XYZ& _color)
{
    __xyz = _color.__xyz;
    return *this;
}

XYZ& XYZ::operator = (XYZ&& _color)
{
    __xyz = std::move(_color.__xyz);
    return *this;
}

const double& XYZ::x() const{return __xyz.x();}
const double& XYZ::y() const{return __xyz.y();}
const double& XYZ::z() const{return __xyz.z();}
const Point3D& XYZ::xyz() const{return __xyz;}

void XYZ::x(const double& _x){__xyz.x(_x);}
void XYZ::y(const double& _y){__xyz.y(_y);}
void XYZ::z(const double& _z){__xyz.z(_z);}
void XYZ::xyz(const Point3D& _xyz){__xyz = _xyz;}
void XYZ::x(double&& _x){__xyz.x(std::move(_x));}
void XYZ::y(double&& _y){__xyz.y(std::move(_y));}
void XYZ::z(double&& _z){__xyz.z(std::move(_z));}
void XYZ::xyz(Point3D&& _xyz){__xyz = std::move(_xyz);}

void XYZ::helperLAB(double& f)
{
    if(f * f * f > eps){
        f *= f * f;
    }else{
        f = (116 * f - 16) / k;
    }
}

void XYZ::helperRGB(double& f)
{
    if(f <= V){
        f /= 12.92;
    }else{
        f = pow((f + 0.055)/1.055 ,2.4);
    }
}
