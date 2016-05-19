//
//  LAB.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 08.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef LAB_hpp
#define LAB_hpp

#include "Color.hpp"

class LAB{
public:
    LAB();
    LAB(const double& _l, const double& _a, const double& _b);
    LAB(double&& _l, double&& _a, double&& _b);
    LAB(const LAB& _color);
    LAB(LAB&& _color);
    LAB(const XYZ& _color);
    
    LAB& operator = (const LAB& _color);
    LAB& operator = (LAB&& _color);
    
    const double& l() const;
    const double& a() const;
    const double& b() const;
    const Point3D& lab() const;
    
    void l(const double& _l);
    void a(const double& _a);
    void b(const double& _b);
    void lab(const Point3D& _lab);
    void l(double&& _l);
    void a(double&& _a);
    void b(double&& _b);
    void lab(Point3D&& _lab);
    
    void increaseLight(const double& intensity);
    void decreaseLight(const double& intensity);
private:
    Point3D __lab;
    static void helper(double& f);
};

#endif /* LAB_hpp */
