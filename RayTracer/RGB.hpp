//
//  RGB.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 08.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef RGB_hpp
#define RGB_hpp

#include "Color.hpp"

static const Point3D MR = Point3D(3.2404542, -1.5371385, -0.4985314);
static const Point3D MG = Point3D(-0.9692660, 1.8760108, 0.0415560);
static const Point3D MB = Point3D(0.0556434, -0.2040259, 1.0572252);
static const double a = 0.055;
static const double SRGB = 0.0031308;

class RGB{
public:
    RGB();
    RGB(const double& _r, const double& _g, const double& _b);
    RGB(double&& _r, double&& _g, double&& _b);
    RGB(const RGB& _color);
    RGB(RGB&& _color);
    RGB(const XYZ& _color);
    
    RGB& operator = (const RGB& _color);
    RGB& operator = (RGB&& _color);
    
    const double& r() const;
    const double& g() const;
    const double& b() const;
    const Point3D& rgb() const;
    
    void r(const double& _r);
    void g(const double& _g);
    void b(const double& _b);
    void rgb(const Point3D& _rgb);
    void r(double&& _r);
    void g(double&& _g);
    void b(double&& _b);
    void rgb(Point3D&& _rgb);
    
    void adecvat();
    
private:
    Point3D __rgb;
    static void helper(double& f);
};

#endif /* RGB_hpp */
