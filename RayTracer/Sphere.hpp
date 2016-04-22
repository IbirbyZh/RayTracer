//
//  Sphere.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 09.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include "IObject.hpp"

class Sphere : public IObject{
public:
    Sphere();
    Sphere(const Point3D& _S, const double& _radius,
             const RGB& _color,
             const double& _reflect, const double& _refract);
    Sphere(Point3D&& _S, double&& _raduis,
             RGB&& _color,
             double&& _reflect, double&& _refract);
    virtual ~Sphere();
    
    virtual bool crossing(const Ray& ray, Point3D& x) const;
    virtual Point3D normal(const Point3D& x) const;
    virtual Box box() const;
    
    const Point3D& S() const;
    void S(const Point3D& _S);
    void S(Point3D&& _S);
    
    const double& radius() const;
    void radius(const double& _radius);
    void radius(double&& _radius);
    
private:
    Point3D __S;
    double __radius;
};


#endif /* Sphere_hpp */
