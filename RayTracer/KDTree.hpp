//
//  KDTree.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 17.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef KDTree_hpp
#define KDTree_hpp

#include "Polygon.hpp"
#include "Ray.hpp"
#include <vector>
#include "ElementaryPlane.hpp"

static const int MAX_HEIGHT = 10;

struct mySpec{
    mySpec(const Polygon* p, const Box* b);
    const Polygon* object;
    const Box* box;
};

struct mySpec2{
    mySpec2(const double& _value, const mySpec* b);
    double value;
    const mySpec* object;
    bool operator < (const mySpec2& a) const;
};

class Node{
public:
    Node();
    void split(int h);
    std::vector<mySpec> objectsWithBox;
    Box mainBox;
    ElementaryPlane splitPlane;
    Node *left, *right, *parent;
    void init(const std::vector<mySpec2>::iterator& begin, const std::vector<mySpec2>::iterator& end);
    bool crossing(const Ray& ray, Point3D& x, const Polygon* &object) const;
    bool crossInThis(const Ray& ray, Point3D& x, const Polygon* &object) const;
};

class KDTree{
public:
    KDTree(const std::vector<Polygon>& _objects);
    bool crossing(const Ray& ray, Point3D& x, const Polygon* &object) const;
private:
    Node *head;
    const std::vector<Polygon>& objects;
    std::vector<Box> boxes;
};

#endif /* KDTree_hpp */
