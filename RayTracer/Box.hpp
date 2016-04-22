//
//  Box.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 17.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef Box_hpp
#define Box_hpp

#include "Point3D.hpp"

class Box{
public:
    Box();
    Box(const Point3D& _A, const Point3D& _B);
    Box(Point3D&& _A, Point3D&& _B);
    virtual ~Box();
    
    virtual bool crossing(const Point3D& x0, const Point3D& a, Point3D& x) const;
    
    const Point3D& A() const;
    const Point3D& B() const;
    void A(const Point3D& _A);
    void B(const Point3D& _B);
    void A(Point3D&& _A);
    void B(Point3D&& _B);
private:
    Point3D __A, __B;
};

#endif /* Box_hpp */
