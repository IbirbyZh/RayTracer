//
//  Triangle.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 07.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include "IObject.hpp"

class Triangle : public IObject{
public:
    Triangle();
    Triangle(const Point3D& _A, const Point3D& _B, const Point3D& _C,
             const RGB& _color,
             const double& _reflect, const double& _refract);
    Triangle(Point3D&& _A, Point3D&& _B, Point3D&& _C,
             RGB&& _color,
             double&& _reflect, double&& _refract);
    virtual ~Triangle();
    
    virtual bool crossing(const Ray& ray, Point3D& x) const;
    virtual Point3D normal(const Point3D& x = Point3D()) const;
    virtual Box box() const;
    
    const Point3D& A() const;
    const Point3D& B() const;
    const Point3D& C() const;
    void A(const Point3D& _A);
    void B(const Point3D& _B);
    void C(const Point3D& _C);
    void A(Point3D&& _A);
    void B(Point3D&& _B);
    void C(Point3D&& _C);
    
private:
    Point3D __A, __B, __C;
};

#endif /* Triangle_hpp */
