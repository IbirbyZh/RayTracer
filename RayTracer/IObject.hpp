//
//  IObject.h
//  RayTracer
//
//  Created by Шишкин Евгений on 07.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef IObject_h
#define IObject_h

#include "Point3D.hpp"
#include "Color.hpp"
#include "Box.hpp"
#include "Ray.hpp"

class IObject{
public:
    virtual ~IObject(){}
    virtual bool crossing(const Ray& ray, Point3D& x) const = 0;
    virtual Point3D normal(const Point3D& x) const = 0;
    virtual Box box() const = 0;
    
    const double& reflect() const;
    const double& refract() const;
    const RGB& color() const;
    
    void reflect(const double& _reflect);
    void refract(const double& _refract);
    void color(const RGB& _color);
    
    void reflect(double&& _reflect);
    void refract(double&& _refract);
    void color(RGB&& _color);
    
protected:
    double __reflect, __refract;
    RGB __color;
};

enum objectType{triangle = 0, sphere = 1, quadrangle = 2};

IObject* createObject(objectType type, double r, double g, double b,
                      double reflect, double refract, ...);

#endif /* IObject_h */
