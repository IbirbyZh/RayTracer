//
//  Polygon.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 22.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef Polygon_hpp
#define Polygon_hpp

#include "IObject.hpp"

class Polygon{
public:
    Polygon();
    Polygon(RGB&& _rgb, double&& _reflect, double&& _refract, objectType type, ...);
    Polygon(const Polygon& polygon);
    Polygon(Polygon&& polygon);
    ~Polygon();
    bool crossing(const Ray& ray, Point3D& x) const;
    Point3D normal(const Point3D& x) const;
    Box box() const;
    void free() const;
    
    const RGB& color()const;
    const double& reflect() const;
    const double& refract() const;
    void color(const RGB& _color);
    void reflect(const double& _reflect);
    void refract(const double& _refract);
    void color(RGB&& _color);
    void reflect(double&& _reflect);
    void refract(double&& _refract);
    
private:
    IObject* object;
    RGB __color;
    double __reflect, __refract;
};
#endif /* Polygon_hpp */
