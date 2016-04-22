//
//  Sun.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 08.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef Sun_hpp
#define Sun_hpp

#include "Point3D.hpp"

class Sun{
public:
    Sun();
    Sun(const Point3D& _S, const double& _intensity);
    Sun(Point3D&& _S, double&& _intensity);
    
    const Point3D& S() const;
    const double& intensity() const;
    
    void S(const Point3D& _S);
    void S(Point3D&& _S);
    void intensity(const double& _intensity);
    void intensity(double&& _intensity);
private:
    Point3D __S;
    double __intensity;
};

#endif /* Sun_hpp */
