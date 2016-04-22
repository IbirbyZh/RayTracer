//
//  RGB.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 08.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "RGB.hpp"
#include <cmath>
#include <utility>

RGB::RGB():
    __rgb(){}

RGB::RGB(const double& _r, const double& _g, const double& _b):
    __rgb(_r, _g, _b){}

RGB::RGB(double&& _r, double&& _g, double&& _b):
    __rgb(std::move(_r), std::move(_g), std::move(_b)){}

RGB::RGB(const RGB& _color):
    __rgb(_color.__rgb){}

RGB::RGB(RGB&& _color):
    __rgb(std::move(_color.__rgb)){}

RGB::RGB(const XYZ& _color)
{
    const Point3D& xyz = _color.xyz();
    double fx, fy ,fz;
    fx = xyz * MR;
    fy = xyz * MG;
    fz = xyz * MB;
    helper(fx);
    helper(fy);
    helper(fz);
    __rgb = Point3D(std::move(fx), std::move(fy), std::move(fz));
}

RGB& RGB::operator = (const RGB& _color)
{
    __rgb = _color.__rgb;
    return *this;
}

RGB& RGB::operator = (RGB&& _color)
{
    __rgb = std::move(_color.__rgb);
    return *this;
}

const double& RGB::r() const{return __rgb.x();}
const double& RGB::g() const{return __rgb.y();}
const double& RGB::b() const{return __rgb.z();}
const Point3D& RGB::rgb() const{return __rgb;}

void RGB::r(const double& _r){__rgb.x(_r);}
void RGB::g(const double& _g){__rgb.y(_g);}
void RGB::b(const double& _b){__rgb.z(_b);}
void RGB::rgb(const Point3D& _rgb){__rgb = _rgb;}
void RGB::r(double&& _r){__rgb.x(std::move(_r));}
void RGB::g(double&& _g){__rgb.y(std::move(_g));}
void RGB::b(double&& _b){__rgb.z(std::move(_b));}
void RGB::rgb(Point3D&& _rgb){__rgb = std::move(_rgb);}

void RGB::adecvat()
{
    double x = __rgb.x();
    double y = __rgb.y();
    double z = __rgb.z();
    if (x >= 1 || x <= 0){
        x = fmax(fmin(x, 1), 0);
    }
    if (y >= 1 || y <= 0){
        y = fmax(fmin(y, 1), 0);
    }
    if (z >= 1 || z <= 0){
        z = fmax(fmin(z, 1), 0);
    }
    __rgb.x(x);
    __rgb.y(y);
    __rgb.z(z);
}

void RGB::helper(double &f)
{
    if (f <= SRGB){
        f *= 12.92;
    }else{
        f = pow(f, 1./2.4);
        f *= (1 + a);
        f -= a;
    }
}
