//
//  Ray.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 17.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp

#include "Point3D.hpp"

class Ray{
public:
    Ray();
    Ray(const Point3D& _startPoint, const Point3D& _rail);
    Ray(Point3D&& _startPoint, Point3D&& _rail);
    
    void startPoint(const Point3D& _startPoint);
    void rail(const Point3D& _rail);
    
    void startPoint(Point3D&& _startPoint);
    void rail(Point3D&& _rail);
    
    const Point3D& startPoint() const;
    const Point3D& rail() const;
private:
    Point3D __startPoint, __rail;
};

#endif /* Ray_hpp */
