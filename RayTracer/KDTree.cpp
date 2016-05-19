//
//  KDTree.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 17.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "KDTree.hpp"
#include <algorithm>
#include <iostream>
#include <assert.h>

mySpec::mySpec(const Polygon* p, const Box* b):
object(p), box(b){}


mySpec2::mySpec2(const double& _value, const mySpec* b):
value(_value), object(b){}

bool mySpec2::operator <(const mySpec2& a) const
{
    return value < a.value;
}

const double arg(const Point3D& p, PlaneType axis)
{
    if(axis == 0){
        return p.x();
    }else if(axis == 1){
        return p.y();
    }else{
        return p.z();
    }
}

KDTree::KDTree(const std::vector<Polygon>& _objects):objects(_objects), boxes()
{
    boxes.reserve(_objects.size());
    
    for(auto i = objects.begin(); i < objects.end(); ++i){
        boxes.push_back(i->box());
    }
    double xMin, yMin, zMin, xMax, yMax, zMax;
    head = new Node();
    xMin = boxes[0].A().x();
    xMax = boxes[0].B().x();
    yMin = boxes[0].A().y();
    yMax = boxes[0].B().y();
    zMin = boxes[0].A().z();
    zMax = boxes[0].B().z();
    for(int i = 1; i < boxes.size(); ++i){
        xMin = std::min(xMin, boxes[i].A().x());
        xMax = std::max(xMax, boxes[i].B().x());
        yMin = std::min(yMin, boxes[i].A().y());
        yMax = std::max(yMax, boxes[i].B().y());
        zMin = std::min(zMin, boxes[i].A().z());
        zMax = std::max(zMax, boxes[i].B().z());
    }
    head->mainBox = Box(Point3D(std::move(xMin), std::move(yMin), std::move(zMin)),
                          Point3D(std::move(xMax), std::move(yMax), std::move(zMax)));
    
    head->objectsWithBox.reserve(boxes.size());
    for(int i = 0; i < boxes.size(); ++i){
        head->objectsWithBox.push_back(mySpec(&(objects[i]), &(boxes[i])));
    }
    head->split(0);
}

Node::Node():left(NULL), right(NULL), parent(NULL), splitPlane(), mainBox(), objectsWithBox()
{}

void Node::split(int h)
{
    if (h > MAX_HEIGHT){
        //std::cerr << static_cast<int>(objectsWithBox.size()) << '\n';
        return;
    }
    PlaneType axis = xType;
    Point3D P(mainBox.B() - mainBox.A());
    double dist = P.x();
    double max, min;
    max = mainBox.B().x();
    min = mainBox.A().x();
    if(P.y() > dist){
        dist = P.y();
        axis = yType;
        max = mainBox.B().y();
        min = mainBox.A().y();
    }
    if(P.z() > dist){
        axis = zType;
        max = mainBox.B().z();
        min = mainBox.A().z();
    }
    std::vector<mySpec2> leftBorder, rightBorder;
    leftBorder.reserve(objectsWithBox.size());
    rightBorder.reserve(objectsWithBox.size());
    for(int i = 0; i < objectsWithBox.size(); ++i){
        leftBorder.push_back(mySpec2(arg(objectsWithBox[i].box->A(), axis), &(objectsWithBox[i])));
        rightBorder.push_back(mySpec2(arg(objectsWithBox[i].box->B(), axis), &(objectsWithBox[i])));
    }
    std::sort(leftBorder.begin(), leftBorder.end());
    std::sort(rightBorder.begin(), rightBorder.end());
    int uk1, uk2, n;
    uk1 = 0;
    uk2 = -1;
    n = static_cast<int>(objectsWithBox.size());
    double value = min;
    int levee = 0;
    int pravee = n;
    int bestLevee = levee;
    int bestPravee = pravee;
    bool predIsLeft = true;
    double sax = (n) * (max - value) + (uk2 + 1) * (value - min);
    double bestValue = min, bestSah = sax;
    while(uk1 + 1 < n || uk2 + 1 < n){
        if (predIsLeft == true){
            ++levee;
            predIsLeft = false;
        }
        if(uk1 + 1 >= n){
            ++uk2;
            value = rightBorder[uk2].value;
            --pravee;
            predIsLeft = false;
        }else if(uk2 + 1 >= n){
            ++uk1;
            value = leftBorder[uk1].value;
            predIsLeft = true;
        }else{
            if(rightBorder[uk2 + 1].value < leftBorder[uk1 + 1].value){
                ++uk2;
                value = rightBorder[uk2].value;
                --pravee;
                predIsLeft = false;
            }else{
                ++uk1;
                value = leftBorder[uk1].value;
                predIsLeft = true;
            }
        }
        double newSax = pravee * (max - value) + levee * (value - min);
        if (newSax < bestSah){
            bestSah = newSax;
            bestValue = value;
            bestLevee = levee;
            bestPravee = pravee;
        }
    }
    if(bestSah >= (n - 3) * (max - min)){
        //std::cerr << static_cast<int>(objectsWithBox.size()) << '\n';
        return;
    }
    value = bestValue;
    splitPlane = ElementaryPlane(axis, value);
    
    for(levee = 0; levee + 1 < n && leftBorder[levee + 1].value < bestValue; ++levee);
    //assert(levee + 1 == bestLevee);
    
    for(pravee = 0; pravee + 1 < n && bestValue < rightBorder[n - pravee - 1].value; ++pravee);
    //assert(pravee + 1 == bestPravee);
    assert(levee + pravee + 2 >= n);
    left = new Node();
    left -> parent = this;
    left -> init(leftBorder.begin(), leftBorder.begin() + (levee + 1));
    Point3D norm = splitPlane.normal();
    
    norm *= max - value;
    left->mainBox = Box(mainBox.A(), mainBox.B() - norm);
    norm /= max - value;
    
    right = new Node();
    right -> parent = this;
    right ->init(rightBorder.end() - (pravee + 1), rightBorder.end());
    
    norm *= value - min;
    right->mainBox = Box(mainBox.A() + norm, mainBox.B());
    
    objectsWithBox.clear();
    left ->split(h + 1);
    right -> split(h + 1);
}

void Node::init(const std::vector<mySpec2>::iterator& begin,
                const std::vector<mySpec2>::iterator& end)
{
    objectsWithBox.reserve(end - begin);
    for(auto i = begin; i < end; ++i){
        objectsWithBox.push_back(*(i->object));
    }

}

bool KDTree::crossing(const Ray &ray, Point3D &x, const Polygon* &object)const
{
    return head->crossing(ray, x, object);
}

bool Node::crossing(const Ray &ray, Point3D &x, const Polygon* &object)const
{
    if(left == NULL || right == NULL){
        if (static_cast<int>(objectsWithBox.size()) > 0){
            return crossInThis(ray, x, object);
        }else{
            return false;
        }
    }
    Point3D fst, snd;
    int count = mainBox.doubleCrossing(ray, fst, snd);
    if (count == 0){
        return false;
    }
    if (count == 1){
        snd = std::move(fst);
        fst = ray.startPoint();
    }
    bool leftVisited = false, rightVisited = false;
    if(splitPlane.put(fst) <= 0){
        leftVisited = true;
        if(left->crossing(ray, x, object)){
            return true;
        }
    }else{
        rightVisited = true;
        if(right->crossing(ray, x, object)){
            return true;
        }
    }
    if(!leftVisited && splitPlane.put(snd) <= 0){
        leftVisited = true;
        if(left->crossing(ray, x, object)){
            return true;
        }
    }
    if(!rightVisited && splitPlane.put(snd) > 0){
        rightVisited = true;
        if(right->crossing(ray, x, object)){
            return true;
        }
    }
    return false;
}

bool Node::crossInThis(const Ray& ray, Point3D& x, const Polygon* &object) const
{
    //std::cerr << static_cast<int>(objectsWithBox.size()) << '\n';
    double dist = MAX_DISTANCE;
    bool ans = false;
    for(auto i = objectsWithBox.begin(); i < objectsWithBox.end(); ++i){
        Point3D xtemp;
        if(i->object->crossing(ray, xtemp)){
            if(mainBox.isIn(xtemp)){
                double temp;
                if(dist > (temp =(ray.startPoint() - xtemp).length())){
                    dist = std::move(temp);
                    object = i->object;
                    x = std::move(xtemp);
                    ans = true;
                }
            }
        }
    }
    return ans;
}





