//
//  XYZ.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 08.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef XYZ_hpp
#define XYZ_hpp

#include "Color.hpp"

static const Point3D MX = Point3D(0.4124564, 0.3575761, 0.1804375);
static const Point3D MY = Point3D(0.2126729, 0.7151522, 0.0721750);
static const Point3D MZ = Point3D(0.0193339, 0.1191920, 0.9503041);
static const double X = 0.9505;
static const double Y = 1.0000;
static const double Z = 1.0890;
static const double V = 0.04045;
static const double eps = 0.008856;
static const double k = 903.3;

class XYZ{
public:
    XYZ();
    XYZ(const double& _x, const double& _y, const double& _z);
    XYZ(double&& _x, double&& _y, double&& _z);
    XYZ(const XYZ& _color);
    XYZ(XYZ&& _color);
    XYZ(const RGB& _color);
    XYZ(const LAB& _color);
    
    XYZ& operator = (const XYZ& _color);
    XYZ& operator = (XYZ&& _color);
    
    const double& x() const;
    const double& y() const;
    const double& z() const;
    const Point3D& xyz() const;
    
    void x(const double& _x);
    void y(const double& _y);
    void z(const double& _z);
    void xyz(const Point3D& _xyz);
    void x(double&& _x);
    void y(double&& _y);
    void z(double&& _z);
    void xyz(Point3D&& _xyz);
    
private:
    Point3D __xyz;
    static void helperLAB(double& f);
    static void helperRGB(double& f);
};

#endif /* XYZ_hpp */
