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
};

enum objectType{triangle = 0, quadrangle = 1, sphere = 2};

#endif /* IObject_h */
