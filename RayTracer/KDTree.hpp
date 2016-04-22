//
//  KDTree.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 17.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef KDTree_hpp
#define KDTree_hpp

#include "IObject.hpp"
#include "Ray.hpp"
#include <vector>

class Node{
public:
    Node(const std::vector<const IObject * const> _objects);
private:
    const std::vector<const IObject* const>& objects;
    const std::vector<const Box> boxes;
    Node *left, *right;
};

class KRTree{
public:
    KRTree(const std::vector<const IObject * const> _objects);
private:
    Node *head;
};

#endif /* KDTree_hpp */
