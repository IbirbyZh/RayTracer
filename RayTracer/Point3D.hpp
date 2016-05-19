//
//  Point3D.hpp
//  RayTraser
//
//  Created by Шишкин Евгений on 07.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef Point3D_hpp
#define Point3D_hpp

static const double MAX_DISTANCE = 1E9;

class Point3D{
public:
    typedef double point_t;
    Point3D();
    Point3D(const point_t& _x, const point_t& _y, const point_t& _z);
    Point3D(point_t&& _x, point_t&& _y, point_t&& _z);
    Point3D(const Point3D& p);
    Point3D(Point3D&& p);
    
    const Point3D& operator = (const Point3D& p);
    const Point3D& operator = (Point3D&& p);
    
    const point_t& x() const;
    const point_t& y() const;
    const point_t& z() const;
    
    void x(const point_t& _x);
    void x(point_t&& _x);
    void y(const point_t& _y);
    void y(point_t&& _y);
    void z(const point_t& _z);
    void z(point_t&& _z);
    
    const Point3D& operator += (const Point3D& p);
    const Point3D& operator -= (const Point3D& p);
    const Point3D& operator *= (const point_t& m);
    const Point3D& operator /= (const point_t& m);
    
    Point3D operator + (const Point3D& p) const;
    Point3D& operator + (Point3D&& p) const;

    Point3D operator - (const Point3D& p) const;
    Point3D& operator - (Point3D&& p) const;
    
    point_t operator *(const Point3D& p) const;
    point_t operator *(Point3D&& p) const;
    
    Point3D operator %(const Point3D& p) const;
    Point3D& operator %(Point3D&& p) const;
    
    point_t length2() const;
    point_t length() const;
    const Point3D& normalize();
private:
    point_t __x, __y, __z;
};

#endif /* Point3D_hpp */
