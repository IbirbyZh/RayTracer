//
//  Scene.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 18.05.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "Point3D.hpp"


static const int HEIGHT = 800;

static const int ANTI_ALI = 3;
static const int RIGHT_MAX = HEIGHT * 4 / 3 * ANTI_ALI;
static const int DOWN_MAX = HEIGHT * ANTI_ALI;

class Scene{
public:
    Scene();
    Scene(const Point3D& _origin, const Point3D& _topLeft,
          const Point3D& _right, const Point3D& _down);
    Scene(Point3D&& _origin, Point3D&& _topLeft,
          Point3D&& _right, Point3D&& _down);
    
    void operator =(Scene&& s);
    
    void toStart();
    bool next(Point3D& p);
    
    const Point3D& origin() const;
    const Point3D& topLeft() const;
    const Point3D& right() const;
    const Point3D& down() const;
    double normDist, normPower;
private:
    Point3D __origin, __topLeft, __right, __down;
    int i;
};

#endif /* Scene_hpp */
