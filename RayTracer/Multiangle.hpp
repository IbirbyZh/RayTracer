//
//  Multiangle.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 07.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef Multiangle_hpp
#define Multiangle_hpp

#include "IObject.hpp"
#include <vector>

class Multiangle : public IObject{
public:
    Multiangle();
    Multiangle(const std::vector<Point3D>& _points);
    Multiangle(std::vector<Point3D>&& _points);
    virtual ~Multiangle();
    
    virtual bool crossing(const Ray& ray, Point3D& x) const;
    virtual Point3D normal(const Point3D& x = Point3D()) const;
    virtual Box box() const;
    
    const std::vector<Point3D>& points() const;
    void points(const std::vector<Point3D>& _points);
    void points(std::vector<Point3D>&& _points);
    
private:
    std::vector<Point3D> __points;
};

#endif /* Multiangle_hpp */
