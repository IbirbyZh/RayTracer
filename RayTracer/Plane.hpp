//
//  Plane.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 07.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef Plane_hpp
#define Plane_hpp

#include "Point3D.hpp"
#include "Ray.hpp"

class Plane{
public:
    Plane();
    Plane(const double& _A, const double& _B, const double& _C, const double& _D);
    Plane(double&& _A, double&& _B, double&& _C, double&& _D);
    Plane(Point3D&& normal, const Point3D& X);
    
    const double& A() const;
    const double& B() const;
    const double& C() const;
    const double& D() const;
    void A(const double& _A);
    void B(const double& _B);
    void C(const double& _C);
    void D(const double& _D);
    void A(double&& _A);
    void B(double&& _B);
    void C(double&& _C);
    void D(double&& _D);
    
    double put(const Point3D& p) const;
    bool crossing(const Ray& ray, Point3D& x) const;
    Point3D normal() const;
private:
    double __A, __B, __C, __D;
};

#endif /* Plane_hpp */
