//
//  Quadrangle.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 11.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef Quadrangle_hpp
#define Quadrangle_hpp

#include "IObject.hpp"

class Quadrangle : public IObject{
public:
    Quadrangle();
    Quadrangle(const Point3D& _A, const Point3D& _B,
               const Point3D& _C, const Point3D& _D,
               const RGB& _color,
               const double& _reflect, const double& _refract);
    Quadrangle(Point3D&& _A, Point3D&& _B,
               Point3D&& _C, Point3D&& _D,
               RGB&& _color,
               double&& _reflect, double&& _refract);
    virtual ~Quadrangle();
    
    virtual bool crossing(const Ray& ray, Point3D& x) const;
    virtual Point3D normal(const Point3D& x = Point3D()) const;
    virtual Box box() const;
    
    const Point3D& A() const;
    const Point3D& B() const;
    const Point3D& C() const;
    const Point3D& D() const;
    void A(const Point3D& _A);
    void B(const Point3D& _B);
    void C(const Point3D& _C);
    void D(const Point3D& _D);
    void A(Point3D&& _A);
    void B(Point3D&& _B);
    void C(Point3D&& _C);
    void D(Point3D&& _D);
    
private:
    Point3D __A, __B, __C, __D;
};

#endif /* Quadrangle_hpp */
