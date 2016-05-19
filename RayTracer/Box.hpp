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
#include "Ray.hpp"
#include "ElementaryPlane.hpp"

class Box{
public:
    Box();
    Box(const Point3D& _A, const Point3D& _B);
    Box(Point3D&& _A, Point3D&& _B);
    ~Box();
    bool crossing(const Ray& ray, Point3D& x) const;
    int doubleCrossing(const Ray& ray, Point3D& x, Point3D& y) const;
    bool isIn(const Point3D& S) const;
    
    const Point3D& A() const;
    const Point3D& B() const;
    void A(const Point3D& _A);
    void B(const Point3D& _B);
    void A(Point3D&& _A);
    void B(Point3D&& _B);
private:
    Point3D __A, __B;
    static bool isInTube(const Point3D& S, const Point3D& Min, const Point3D& Max, PlaneType type);
};

#endif /* Box_hpp */
