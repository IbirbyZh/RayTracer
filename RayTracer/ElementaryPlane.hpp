//
//  ElementaryPlane.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 22.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef ElementaryPlane_hpp
#define ElementaryPlane_hpp

#include "Ray.hpp"

enum PlaneType{xType = 0, yType = 1, zType = 2};

class ElementaryPlane{
public:
    ElementaryPlane();
    ElementaryPlane(const PlaneType& _type, const double& _value);
    ElementaryPlane(PlaneType&& _type, double&& _value);
    
    const PlaneType& type() const;
    const double& value() const;
    void type(const PlaneType& _type);
    void value(const double& _value);
    void type(PlaneType&& _type);
    void value(double&& _value);
    
    double put(const Point3D& p) const;
    bool crossing(const Ray& ray, Point3D& x) const;
    Point3D normal() const;
    
private:
    PlaneType __type;
    double __value;
};

#endif /* ElementaryPlane_hpp */
